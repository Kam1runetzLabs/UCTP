// Copyright 2021 Kam1runetzLabs notsoserious2017@gmail.com

#ifndef INCLUDE_THREADPOOL_HPP_
#define INCLUDE_THREADPOOL_HPP_

#include <memory>
#include <utility>

#include "ThreadPoolImpl.hpp"

class ThreadPool {
 public:
  static size_t HardwareConcurrency();

  template <typename TaskType, typename... Args>
  static constexpr decltype(auto) Task(TaskType &&task, Args &&...args) {
    return ThreadPoolImpl::Task(std::forward<TaskType>(task),
                                std::forward<Args>(args)...);
  }

  template <typename CallbackType, typename... Args>
  static constexpr decltype(auto) Callback(CallbackType &&callback,
                                           Args &&...args) {
    return ThreadPoolImpl::Task(std::forward<CallbackType>(callback),
                                std::forward<Args>(args)...);
  }

  template <typename CallbackType>
  static constexpr decltype(auto) Callback(CallbackType &&callback) {
    return ThreadPoolImpl::Callback(std::forward<CallbackType>(callback));
  }

  enum DeletePolicy { DeleteByCancelWorkers, DeleteByWaitWorkers };

  explicit ThreadPool(size_t workersCount = HardwareConcurrency(),
                      DeletePolicy deletePolicy = DeleteByWaitWorkers);

  template <typename Task, typename Callback>
  void Execute(Task &&task, Callback &&callback) {
    m_Impl->Execute(std::forward<Task>(task), std::forward<Callback>(callback));
  }

 private:
  std::shared_ptr<ThreadPoolImpl> m_Impl;
};

#endif  // INCLUDE_THREADPOOL_HPP_