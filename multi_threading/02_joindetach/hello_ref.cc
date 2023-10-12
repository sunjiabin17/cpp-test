#include <iostream>
#include <thread>

void hello(std::string& message) {
    std::cout << message << "\n";
    message = "Hello Concurrent World (updated)";
}

int main() {
    std::string message = "Hello Concurrent World";
    std::thread t(hello, std::ref(message));
    t.detach();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // t.join();

    std::cout << message << "\n";
}