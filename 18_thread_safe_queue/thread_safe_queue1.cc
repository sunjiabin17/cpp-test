#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <queue>
#include <exception>
#include <memory>

class empty_queue: std::exception {
public:
    const char* what() const throw() {
        return "empty queue!";
    }
};

template<typename T>
class threadsafe_queue {
public:
    threadsafe_queue() {}
    threadsafe_queue(const threadsafe_queue& other) {
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data;
    }

    threadsafe_queue& operator=(const threadsafe_queue&) = delete;

    void push(T new_value) {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "push " << new_value << std::endl;
        data.push(new_value);
    }

    void wait_and_pop(T& value) {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "wait_and_pop " << value << std::endl;
        if (data.empty()) throw empty_queue();
        value = data.front();
        data.pop();
    }

    std::shared_ptr<T> wait_and_pop() {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "wait_and_pop" << std::endl;
        if (data.empty()) throw empty_queue();
        std::shared_ptr<T> const res(std::make_shared<T>(std::move(data.front())));
        data.pop();
        return res;
    }

    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "try_pop " << value << std::endl;
        if (data.empty()) return false;
        value = data.front();
        data.pop();
        return true;
    }

    std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "try_pop" << std::endl;
        if (data.empty()) return std::shared_ptr<T>();
        std::shared_ptr<T> const res(std::make_shared<T>(std::move(data.front())));
        data.pop();
        return res;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "empty" << std::endl;
        return data.empty();
    }
private:
    std::queue<T> data;
    mutable std::mutex m;
};

int main() {
    threadsafe_queue<int> q;
    q.push(12);
    std::thread t1([&q] {
        q.push(42);
    });
    std::thread t2([&q] {
        int value;
        q.try_pop(value);
        std::cout << "value: " << value << std::endl;
    });

    std::future<int> f1 = std::async([&q] {
        return *(q.wait_and_pop());
    });


    t1.join();
    t2.join();

    return 0;
}