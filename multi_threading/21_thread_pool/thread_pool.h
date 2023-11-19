#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>

class ThreadPool {
public:
  explicit ThreadPool(size_t thread_count);
  ~ThreadPool();
  ThreadPool(const ThreadPool &) = delete;
  ThreadPool &operator=(const ThreadPool &) = delete;

  using Task = std::function<void(void)>;

  void Enqueue(Task &&task);

  size_t Size() { return workers_.size(); }

private:
  std::queue<Task> task_queue_;
  std::vector<std::thread> workers_;
  std::condition_variable cv_;
  std::mutex queue_mutex_;

  bool stop_;
};