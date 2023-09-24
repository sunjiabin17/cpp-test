#include <iostream>
#include <future>

void async_func(std::promise<int>& p, int value) {
    std::cout << "async_func" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    p.set_value(value);
}

int main() {
    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::thread t(async_func, std::ref(p), 10);

    int value = f.get();
    std::cout << "value: " << value << std::endl;

    t.join();

    return 0;
}