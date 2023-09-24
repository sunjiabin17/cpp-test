#include <thread>
#include <mutex>
#include <future>
#include <chrono>

#include <iostream>
#include <vector>
#include <string>

void test1() {
    for (int i = 0; i < 10; ++i) {
        std::cout << "test1: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int test2() {
    for (int i = 0; i < 10; ++i) {
        std::cout << "test2: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 1;
}

int main() {
    // std::future<int> f2 = std::async(std::launch::async, test2);    // 启动时就开始执行
    // int value = f2.get();   // 等待异步操作的结果
    // std::future<void> f1 = std::async(std::launch::async, test1);

    // std::cout << "value: " << value << std::endl;

    std::future<int> f2 = std::async(std::launch::deferred, test2);    // 调用get()时才开始执行
    std::future<void> f1 = std::async(std::launch::async, test1);

    int value = f2.get();   // 等待异步操作的结果
    f1.get();
    std::cout << "value: " << value << std::endl;

    return 0;
}