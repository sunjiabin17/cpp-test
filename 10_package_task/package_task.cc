#include <future>
#include <iostream>

int async_func(int x, int y) {
    std::cout << "async_func" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    return x + y;
}

int main() {
    std::packaged_task<int(int, int)> task(async_func);
    std::future<int> f = task.get_future();

    std::thread t(std::move(task), 10, 20);

    int result = f.get();
    std::cout << "result: " << result << std::endl;

    t.join();
    return 0;
}