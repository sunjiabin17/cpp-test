#include <iostream>
#include <thread>
#include <mutex>

class SingleClass {
public:
    static SingleClass* get_instance() {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mutex);
            // 再判断一次，确保不会因为加锁期间多个线程进入
            if (instance == nullptr) {
                instance = new SingleClass();
            }
        }
        return instance;
    }
private:
    static SingleClass* instance;
    static std::mutex mutex;
    SingleClass() {};
};

SingleClass* SingleClass::instance = nullptr;
std::mutex SingleClass::mutex;

int main() {
    std::thread t1([]() {
        SingleClass *instance1 = SingleClass::get_instance();
        std::cout << instance1 << std::endl;
    });

    std::thread t2([]() {
        SingleClass *instance2 = SingleClass::get_instance();
        std::cout << instance2 << std::endl;
    });
    t1.join();
    t2.join();
    return 0;
}

