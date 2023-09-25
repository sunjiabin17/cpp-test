#include <stack>
#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <exception>
#include <memory>

class empty_stack: std::exception {
public:
  const char* what() const throw() {
    return "empty stack!";
  }
};

template<typename T>
class threadsafe_stack {
public:
    threadsafe_stack() {}
    threadsafe_stack(const threadsafe_stack& other) {
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data;
    }

    threadsafe_stack& operator=(const threadsafe_stack&) = delete;

    void push(T new_value) {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "push " << new_value << std::endl;
        data.push(new_value);
    }

    void pop(T& value) {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "pop " << value << std::endl;
        if (data.empty()) throw empty_stack();
        value = data.top();
        data.pop();
    }

    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "pop" << std::endl;
        if (data.empty()) throw empty_stack();
        std::shared_ptr<T> const res(std::make_shared<T>(std::move(data.top())));
        data.pop();
        return res;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "empty" << std::endl;
        return data.empty();
    }

private:
    std::stack<int> data;
    mutable std::mutex m;
};


int main() {
    threadsafe_stack<int> st;
    st.push(5);
    std::thread t1([&st] {
        st.push(1);
    });
    std::thread t2([&st] {
        st.push(2);
    });
    std::future<int> f1 = std::async([&st] {
        return *(st.pop());
    });
    std::future<int> f2 = std::async([&st] {
        return *(st.pop());
    });
    st.pop();
    std::cout << f1.get() << std::endl;
    std::cout << f2.get() << std::endl;
    std::cout << std::boolalpha << st.empty() << std::endl;
    t1.join();
    t2.join();
    return 0;
}