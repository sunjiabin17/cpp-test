#include <iostream>
#include <future>
#include <chrono>
#include <thread>

void longRunningTask() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Task Completed" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

int main() {
    {
        // Launching a non-deferred asynchronous task
        std::future<void> fut = std::async(std::launch::async, longRunningTask);
        // Exiting the scope without calling fut.get() or fut.wait()
        // The destructor of 'fut' will block until 'longRunningTask' completes
    } // Destructor called here, blocks for 5 seconds

    std::cout << "After future destruction" << std::endl;
    return 0;
}
