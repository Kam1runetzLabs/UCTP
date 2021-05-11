// Copyright 2021 Kam1runetzLabs notsoserious2017@gmail.com

#ifndef INCLUDE_THREADPOOLIMPL_HPP_
#define INCLUDE_THREADPOOLIMPL_HPP_

#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>

class ThreadPoolImpl {
 public:
  static size_t HardwareConcurrency() {
    return std::thread::hardware_concurrency();
  }

  static void DeleteByCancel(ThreadPoolImpl *tpImpl) {
    tpImpl->m_CancelWorkers();
    delete tpImpl;
  }

  static void DeleteByWait(ThreadPoolImpl *tpImpl) {
    tpImpl->m_WaitWorkers();
    delete tpImpl;
  }

  template <typename TaskType, typename... Args>
  static constexpr decltype(auto) Task(TaskType &&task, Args &&...args) {
    return std::bind(std::forward<TaskType>(task), std::forward<Args>(args)...);
  }

  template <typename CallbackType, typename... Args>
  static constexpr decltype(auto) Callback(CallbackType &&callback,
                                           Args &&...args) {
    return std::bind(std::forward<CallbackType>(callback),
                     std::placeholders::_1, std::forward<Args>(args)...);
  }

  template <typename CallbackType>
  static constexpr decltype(auto) Callback(CallbackType &&callback) {
    return std::bind(std::forward<CallbackType>(callback),
                     std::placeholders::_1);
  }

  explicit ThreadPoolImpl(size_t workersCount)
      : m_Mutex(),
        m_WorkCV(),
        m_WaitCV(),
        m_EndCV(),
        m_TasksQueue(),
        m_Flag(Flags::Work),
        m_WorkersCount(workersCount) {
    if (!workersCount)
      throw std::runtime_error("workers count must be more than 0");

    for (size_t i = 0; i != workersCount; ++i) {
      auto worker = std::thread([this] {
        for (;;) {
          std::function<void()> task;
          {
            std::unique_lock<std::mutex> lock(m_Mutex);
            m_WorkCV.wait(lock, [this] {
              return !m_TasksQueue.empty() || m_Flag != Flags::Work;
            });

            if (m_Flag == Flags::Cancel) break;
            if (!m_TasksQueue.empty()) {
              task = m_TasksQueue.front();
              m_TasksQueue.pop();
            }
          }
          if (task) task();
          {
            std::unique_lock<std::mutex> lock(m_Mutex);
            if (m_Flag == Flags::Wait && m_TasksQueue.empty()) {
              m_WaitCV.notify_all();
              break;
            }
          }
        }

        {
          std::unique_lock<std::mutex> lock(m_Mutex);
          if (--m_WorkersCount == 0) m_EndCV.notify_all();
        }
      });
      worker.detach();
    }
  }

  ThreadPoolImpl(const ThreadPoolImpl &) = delete;
  ThreadPoolImpl(ThreadPoolImpl &&) = delete;
  ThreadPoolImpl &operator=(const ThreadPoolImpl &) = delete;
  ThreadPoolImpl &operator=(ThreadPoolImpl &&) = delete;

  template <typename Task, typename Callback>
  void Execute(Task &&task, Callback &&callback) {
    auto workerTask = std::make_shared<std::packaged_task<void()>>(
        std::bind(std::forward<Callback>(callback), std::forward<Task>(task)));
    {
      std::unique_lock<std::mutex> lock(m_Mutex);
      m_TasksQueue.emplace([workerTask] { (*workerTask)(); });
      m_WorkCV.notify_one();
    }
  }

 private:
  enum Flags { Work, Wait, Cancel };
  std::mutex m_Mutex;
  std::condition_variable m_WorkCV;
  std::condition_variable m_WaitCV;
  std::condition_variable m_EndCV;
  std::queue<std::function<void()>> m_TasksQueue;
  Flags m_Flag;
  size_t m_WorkersCount;

  void m_CancelWorkers() {
    std::unique_lock<std::mutex> lock(m_Mutex);
    m_Flag = Flags::Cancel;
    m_WorkCV.notify_all();
    m_EndCV.wait(lock, [this] { return m_WorkersCount == 0; });
  }

  void m_WaitWorkers() {
    std::unique_lock<std::mutex> lock(m_Mutex);
    m_Flag = Flags::Wait;
    m_WorkCV.notify_all();
    m_WaitCV.wait(lock, [this] { return m_TasksQueue.empty(); });
    m_EndCV.wait(lock, [this] { return m_WorkersCount == 0; });
  }
};

#endif  // INCLUDE_THREADPOOLIMPL_HPP_
