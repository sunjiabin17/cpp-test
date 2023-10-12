#include <future>
#include <iostream>

int async_func(int x, int y) {
    std::cout << "async_func" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    return x + y;
}

void shared_future_test(std::shared_future<int> f) {
    std::cout << "shared_future_test\n";
    int result = f.get();
    std::cout << "test thread result: " << result << std::endl;
}


int main() {
    std::shared_future<int> f = std::async(std::launch::async, async_func, 10, 20);
    std::thread t1(shared_future_test, f);
    std::thread t2(shared_future_test, f);

    int result = f.get();
    std::cout << "main thread result: " << result << std::endl;

    t1.join();
    t2.join();
    
    return 0;
}