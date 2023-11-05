#include "thread_pool.h"
#include <stdexcept>
#include <iostream>

ThreadPool::ThreadPool(size_t thread_count) : stop_(false) {
  if (thread_count == 0) {
    throw std::invalid_argument("thread_count cannot be zero.");
  }
  std::cout << "creating thread pool" << std::endl;

  const auto worker_loop = [this]() {
    while (true) {
      Task task;
      {
        std::unique_lock<std::mutex> lk(queue_mutex_);
        cv_.wait(lk, [this]() { return stop_ or !task_queue_.empty(); });
        if (stop_ and task_queue_.empty()) {
          std::cout << "thread " << std::this_thread::get_id()
                    << " is exiting" << std::endl;
          break;
        }
        task = std::move(task_queue_.front());
        task_queue_.pop();

        if (task) {
          task();
        }
      }
    }
  };

  workers_.reserve(thread_count);
  for (int i = 0; i < thread_count; ++i) {
    workers_.emplace_back(worker_loop);
  }
}

ThreadPool::~ThreadPool() {
  {
    std::lock_guard<std::mutex> lk(queue_mutex_);
    stop_ = true;
  }
  cv_.notify_all();
  for (auto& t : workers_) {
    t.join();
  }
}

// 将一个临时的 Task 对象传递给 Enqueue 函数，而不需要创建临时对象的副本。
void ThreadPool::Enqueue(Task&& task) {
  {
    std::lock_guard<std::mutex> lk(queue_mutex_);
    if (stop_) {
      return;
    }
    task_queue_.push(std::move(task));
  }

  cv_.notify_one();

}