#include <iostream>
#include <thread>
#include <chrono>

#define LOG_INFO(x) \
    do {\
        std::cout << "[INFO] " << __FILE__ << ":" << __LINE__ << "\t" << x << std::endl;\
    } while (0)

#define LOG_ERROR(x) \
    do {\
        std::cout << "[ERROR] " << __FILE__ << ":" << __LINE__ << "\t" << x << std::endl;\
    } while (0)

void func1(int a, int b) {
    int c = a * b;
    LOG_INFO("func 1 c = " << c);
    while(1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        c += 1;
    }
}

void func2(int a, int b) {
    int c = a + b;
    LOG_INFO("func 2 c = " << c);
    while(1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        c += 1;
    }
}

int main(int argc, char** argv) {
    std::thread t1(func1, 1, 2);
    std::thread t2(func2, 1, 2);

    if (t1.joinable()) {
        t1.join();
    }
    if (t2.joinable()) {
        t2.join();
    }
    return 0;
}