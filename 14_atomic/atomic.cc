#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> counter(0);
int counter1 = 0;

void func() {
    for (int i = 0; i < 10000; ++i) {
        ++counter;
        ++counter1;
    }
}

int main() {
    std::thread t1(func);
    std::thread t2(func);

    t1.join();
    t2.join();

    std::cout << "counter: " << counter << std::endl;
    std::cout << "counter1: " << counter1 << std::endl; // 错误答案

    return 0;
}