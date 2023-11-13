#include <iostream>
#include <barrier>
#include <thread>
#include <vector>

void work(std::barrier<>& sync_point, int thread_id) {
    std::cout << "Thread " << thread_id << " is doing the first part of work\n";
    auto wait_time = std::rand() % 1000;
    std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));
    sync_point.arrive_and_wait();
    std::cout << "Thread " << thread_id << " is doing the second part of work\n";
}

int main() {
    const int num_threads = 5;
    std::barrier sync_point(num_threads);
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(work, std::ref(sync_point), i);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
