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
        std::lock_guard<std::mutex> lock(other.m);  // 保证在拷贝other的数据时，不会有其他线程同时修改other的数据，从而导致数据不一致的问题。
        data = other.data;
    }

    threadsafe_stack& operator=(const threadsafe_stack&) = delete;

    void push(T new_value) {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "push " << new_value << std::endl;
        data.push(std::move(new_value));    // 可能会抛出一个异常，原因是拷贝/移动数据或者内存不足, 但是不管哪种情况，std::stack<> 都能保证其安全性
    }

    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "pop" << std::endl;
        if (data.empty()) throw empty_stack();          // 可能会抛出 empty_stack 异常，数据没有修改，是安全的

        std::shared_ptr<T> const res(                   // 创建 res 时，也可能会抛出异常，
            std::make_shared<T>(std::move(data.top()))  // 两个原因：std::make_shared 无法分配出足够的内存去创建新对象，并且内部数据需要引用新对象，
            );                                          // 或者在拷贝或移动构造到新分配的内存中时抛出异常
                                                                                    
                                                                                    
        data.pop();     // 当调用data.pop() 时能保证不抛出异常并返回结果（这个成员函数保证不会抛出异常），所以这个重载的 pop() 是“异常安全”的
        return res;
    }

    void pop(T& value) {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "pop " << value << std::endl;
        if (data.empty()) throw empty_stack();  // 可能会抛出 empty_stack 异常，数据没有修改，是安全的
        value = std::move(data.top());          // 第二个重载 pop() 除了在拷贝赋值或移动赋值时会抛出异常 5，当构造新对象和 std::shared_ptr 实例时都不会抛出异常。
        data.pop();                             // 同样，调用data.pop() 之前，没有对数据结构进行修改，所以这个函数也是“异常安全”的
    }


    bool empty() const {                        // empty() 不会修改任何数据，所以也是“异常安全”函数
        std::lock_guard<std::mutex> lock(m);
        std::cout << "empty" << std::endl;
        return data.empty();
    }

private:
    std::stack<T> data;
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