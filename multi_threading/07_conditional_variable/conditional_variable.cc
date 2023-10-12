#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <chrono>
#include <memory>
#include <queue>

template<typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() {}
    ThreadSafeQueue(const ThreadSafeQueue& other) = delete;
    ThreadSafeQueue& operator=(const ThreadSafeQueue& other) = delete;

    void push(const T& value);
    // try_pop(): 立即返回一个值，如果没有返回nullptr
    bool try_pop(T& value);
    std::shared_ptr<T> try_pop();
    // wait_and_pop(): 等待直到有一个值可以被弹出
    void wait_and_pop(T& value);
    std::shared_ptr<T> wait_and_pop();
    bool empty() const;

private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable cond_;

};

template<typename T>
void ThreadSafeQueue<T>::push(const T& value) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(value);
    cond_.notify_one();
};

template<typename T>
bool ThreadSafeQueue<T>::try_pop(T& value) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (queue_.empty()) {
        return false;
    }
    value = queue_.front();
    queue_.pop();
    return true;
}

template<typename T>
std::shared_ptr<T> ThreadSafeQueue<T>::try_pop() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (queue_.empty()) {
        return std::shared_ptr<T>();
    }
    std::shared_ptr<T> res(std::make_shared<T>(queue_.front()));
    queue_.pop();
    return res;
}

template<typename T>
void ThreadSafeQueue<T>::wait_and_pop(T& value) {
    std::unique_lock<std::mutex> lock(mutex_);
    cond_.wait(lock, [this] { return !queue_.empty(); });
    value = queue_.front();
    queue_.pop();
}

template<typename T>
std::shared_ptr<T> ThreadSafeQueue<T>::wait_and_pop() {
    std::unique_lock<std::mutex> lock(mutex_);
    cond_.wait(lock, [this] { return !queue_.empty(); });
    std::shared_ptr<T> res(std::make_shared<T>(queue_.front()));
    queue_.pop();
    return res;
}

template<typename T>
bool ThreadSafeQueue<T>::empty() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.empty();
}

int main() {
    ThreadSafeQueue<int> queue;
    // 启动一个线程往队列中push数据
    std::thread t1([&queue] {
        for (int i = 0; i < 10; ++i) {
            queue.push(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    // // 测试wait_and_pop: 启动一个线程从队列中pop数据
    // std::thread t2([&queue] {
    //     int value;
    //     for (int i = 0; i < 10; ++i) {
    //         queue.wait_and_pop(value);
    //         std::cout << "value: " << value << std::endl;
    //     }
    // });

    // 测试try_pop: 启动一个线程从队列中pop数据
    std::thread t3([&queue] {
        int value;
        for (int i = 0; i < 10; ++i) {
            if (queue.try_pop(value)) {
                std::cout << "value: " << value << std::endl;
            } else {
                std::cout << "queue is empty" << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(60));
        }
    });

    t1.join();
    // t2.join();
    t3.join();

    return 0;
}