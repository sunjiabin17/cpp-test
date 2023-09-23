#include <iostream>
#include <thread>


// 相比于thread_guard，scoped_thread可以避免thread_guard对象在引用他的线程结束后继续存在所造成的不良影响
// 同时意味着，一旦所有权转移到了该对象，其他对象都不可以join 或者detach 该线程
class scoped_thread {
public:
    explicit scoped_thread(std::thread t_):
        t(std::move(t_)) {
            if (!t.joinable()) {
                throw std::logic_error("No thread");
            }
        }
    ~scoped_thread() {
        t.join();
    }
    scoped_thread(scoped_thread const&) = delete;
    scoped_thread& operator=(scoped_thread const&) = delete;
private:
    std::thread t;
};

void hello() {
    std::cout << "Hello Concurrent World\n";
}

void test() {
    // 编译器可能会将 t 的初始化解析为一个函数声明，而不是一个对象的初始化
    // scoped_thread t(std::thread(hello));
    // 解决方法是加额外的括号
    scoped_thread t((std::thread(hello)));
    // 或使用花括号
    // scoped_thread t{std::thread(hello)};
    std::cout << "test" << std::endl;
}

int main() {
    test();
    std::cout << "Hello Main Thread\n";

    return 0;
}