#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <queue>
#include <exception>
#include <memory>

class empty_queue: std::exception {
public:
    const char* what() const throw() {
        return "empty queue!";
    }
};

template<typename T>
class threadsafe_queue {
public:
    threadsafe_queue() {}
    threadsafe_queue(const threadsafe_queue& other) {
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data;
    }

    threadsafe_queue& operator=(const threadsafe_queue&) = delete;

    void push(T new_value) {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "push " << new_value << std::endl;
        data.push(std::move(new_value));
        data_cond.notify_one();
    }

    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lock(m);
        data_cond.wait(lock, [this] {return !data.empty();});
        std::cout << "wait_and_pop " << value << std::endl;
        value = data.front();
        data.pop();
    }

    std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<std::mutex> lock(m); 
        // 不止一个线程等待对队列进行推送操作时，只会有一个线程因 data_cond.notify_one() 而继续工作。
        // 但是，如果工作线程在 wait_and_pop() 中抛出一个异常，例如，构造新的 std::shared_ptr<> 对象时抛出异常，那么其他线程则会永远休眠。
        // 解决方案：
        // 1. 调用函数需要改成 data_cond.notify_all()，这个函数将唤醒所有的工作线程，不过当大多线程发现队列依旧是空时，又会耗费资源让线程重新进入睡眠
        // 2. 当有异常抛出时，让 wait_and_pop() 函数调用 notify_one()，从而让个另一个线程去索引存储的值
        // 3. 将 std::shared_ptr<> 的初始化过程移到 push() 中，并且存储 std::shared_ptr<> 实例，而不是直接使用数据值，将 std::shared_ptr<> 拷贝到内部 std::queue<> 中就不会抛出异常了，这样wait_and_pop() 又是安全的了
        data_cond.wait(lock, [this] {return !data.empty();});
        std::shared_ptr<T> const res(std::make_shared<T>(std::move(data.front())));
        std::cout << "wait_and_pop " << *res << std::endl;
        data.pop();
        return res;
    }

    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty()) return false;
        value = data.front();
        std::cout << "try_pop " << value << std::endl;
        data.pop();
        return true;
    }

    std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty()) return std::shared_ptr<T>();
        std::shared_ptr<T> const res(std::make_shared<T>(std::move(data.front())));
        std::cout << "try_pop " << *res << std::endl;
        data.pop();
        return res;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "empty" << std::endl;
        return data.empty();
    }
private:
    std::queue<T> data;
    mutable std::mutex m;
    std::condition_variable data_cond;
};

int main() {
    threadsafe_queue<int> q;
    q.push(12);
    std::thread t1([&q] {
        q.push(42);
    });
    std::thread t2([&q] {
        int value;
        q.try_pop(value);
    });

    std::future<int> f1 = std::async([&q] {
        return *(q.wait_and_pop());
    });


    t1.join();
    t2.join();

    return 0;
}