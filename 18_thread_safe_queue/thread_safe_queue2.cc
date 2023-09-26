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
private:
    struct node {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };

    std::mutex head_mutex;
    std::unique_ptr<node> head;
    std::mutex tail_mutex;
    node* tail;

    node* get_tail() {
        std::lock_guard<std::mutex> lock(tail_mutex);
        return tail;
    }

    std::unique_ptr<node> pop_head() {
        std::lock_guard<std::mutex> lock(head_mutex);
        if (head.get() == get_tail()) {
            return nullptr;
        }
        std::unique_ptr<node> old_head = std::move(head);
        head = std::move(old_head->next);
        return old_head;
    }

public:
    threadsafe_queue(): head(new node), tail(head.get()) {}
    threadsafe_queue(const threadsafe_queue& other) = delete;
    threadsafe_queue& operator=(const threadsafe_queue& other) = delete;

    std::shared_ptr<T> try_pop() {
        std::unique_ptr<node> old_head = pop_head();
        return old_head ? old_head->data : std::shared_ptr<T>();
    }

    void push(T new_value) {
        std::shared_ptr<T> new_data(std::make_shared<T>(std::move(new_value)));
        std::unique_ptr<node> p(new node);
        node* const new_tail = p.get();     // 即指针本身是常量，指向的对象可以修改
        std::lock_guard<std::mutex> lock(tail_mutex);
        tail->data = new_data;
        tail->next = std::move(p);
        tail = new_tail;
    }

};

int main() {
    threadsafe_queue<int> q;
    std::thread t1([&q](){
        q.push(1);
        q.push(2);
        q.push(3);
    });
    std::thread t2([&q](){
        std::cout << *q.try_pop() << std::endl;
        std::cout << *q.try_pop() << std::endl;
        std::cout << *q.try_pop() << std::endl;
    });
    
    std::thread t3([&q](){
        std::cout << *q.try_pop() << std::endl;
        std::cout << *q.try_pop() << std::endl;
        std::cout << *q.try_pop() << std::endl;
    });
    t1.join();
    t2.join();
    t3.join();
    return 0;
}