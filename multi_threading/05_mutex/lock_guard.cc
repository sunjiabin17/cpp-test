#include <thread>
#include <mutex>
#include <iostream>
#include <vector>

std::vector<int> data;
std::mutex mutex;

void add_data(int value) {
    std::lock_guard<std::mutex> guard(mutex);
    data.push_back(value);
}

void add_data2(int value) {
    mutex.lock();
    data.push_back(value);
    mutex.unlock();
}

bool find_value(int value) {
    std::lock_guard<std::mutex> guard(mutex);
    return std::find(data.begin(), data.end(), value) != data.end();
}

int main() {
    std::cout << find_value(1) << std::endl;
    std::thread t1(add_data, 1);
    std::thread t2(add_data, 2);
    std::thread t3(add_data2, 3);

    // find value
    std::cout << find_value(1) << std::endl;
    std::cout << find_value(2) << std::endl;
    std::cout << find_value(3) << std::endl;
    t1.join();
    t2.join();
    t3.join();

    return 0;
}