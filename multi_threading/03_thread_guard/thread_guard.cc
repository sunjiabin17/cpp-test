// `thread_guard` 是一个 C++ 类，用于管理线程的生命周期。它的作用类似于 `std::lock_guard`，
// 用于自动化线程的加入和分离操作，从而避免线程泄漏和程序崩溃。

// `thread_guard` 类的实现通常是在构造函数中接收一个 `std::thread` 对象，
// 并将它保存在一个成员变量中。在析构函数中，它会检查这个线程是否可连接，如果它是可连接的，
// 就调用 `join` 函数将它加入到主线程中。这样，当 `thread_guard` 对象被销毁时，
// 它会自动将线程加入到主线程中，从而避免线程泄漏和程序崩溃。

// 下面是一个简单的 `thread_guard` 类的实现：

#include <thread>
#include <iostream>

class thread_guard {
public:
    explicit thread_guard(std::thread& t_): 
        t(t_) {}
    ~thread_guard() {
        if (t.joinable())
            t.join();
    }
    thread_guard(thread_guard const&) = delete;
    thread_guard& operator=(thread_guard const&) = delete;

private:
    std::thread& t;
};

void hello() {
    std::cout << "Hello Concurrent World\n";
}

void test() {
    std::thread t(hello);
    // t 线程会在 g 对象被销毁时自动加入到主线程中
    thread_guard g(t);  // 注释掉这一行，程序会崩溃

}

int main() {
    test();
    std::cout << "Hello Main Thread\n";
    
    return 0;
}