// Copyright 2021 Kam1runetzLabs notsoserious2017@gmail.com

#include "ThreadPool.hpp"

#include <memory>

#include "ThreadPoolImpl.hpp"

size_t ThreadPool::HardwareConcurrency() {
  return ThreadPoolImpl::HardwareConcurrency();
}

ThreadPool::ThreadPool(size_t workersCount, DeletePolicy deletePolicy) {
  if (deletePolicy == DeleteByWaitWorkers) {
    m_Impl = std::shared_ptr<ThreadPoolImpl>(new ThreadPoolImpl(workersCount),
                                             ThreadPoolImpl::DeleteByWait);
  } else if (deletePolicy == DeleteByCancelWorkers) {
    m_Impl = std::shared_ptr<ThreadPoolImpl>(new ThreadPoolImpl(workersCount),
                                             ThreadPoolImpl::DeleteByCancel);
  }
}
