#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <queue>
#include <exception>
#include <memory>

template<typename T>
class threadsafe_queue {
private:
    struct node {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };

    std::mutex head_mutex;
    std::mutex tail_mutex;
    std::condition_variable data_cond;
    std::unique_ptr<node> head;
    node* tail;

    node* get_tail() {
        std::lock_guard<std::mutex> lock(tail_mutex);
        return tail;
    }

    std::unique_ptr<node> pop_head() {
        std::unique_ptr<node> old_head = std::move(head);
        head = std::move(old_head->next);
        return old_head;
    }

    std::unique_lock<std::mutex> wait_for_data() {
        std::unique_lock<std::mutex> head_lock(head_mutex);
        data_cond.wait(head_lock, [this] {return head.get() != get_tail();});
        return std::move(head_lock);
    }

    std::unique_ptr<node> wait_pop_head() {
        std::unique_lock<std::mutex> lock(wait_for_data());
        return pop_head();
    }

    std::unique_ptr<node> wait_pop_head(T& value) {
        std::unique_lock<std::mutex> lock(wait_for_data());
        value = std::move(*head->data);
        return pop_head();
    }

    std::unique_ptr<node> try_pop_head() {
        std::lock_guard<std::mutex> lock(head_mutex);
        if (head.get() == get_tail()) {
            return nullptr;
        }
        return pop_head();
    }

    std::unique_ptr<node> try_pop_head(T& value) {
        std::lock_guard<std::mutex> lock(head_mutex);
        if (head.get() == get_tail()) {
            return nullptr;
        }
        value = std::move(*head->data);
        return pop_head();
    }

public:
    threadsafe_queue(): head(new node), tail(head.get()) {}
    threadsafe_queue(const threadsafe_queue& other) = delete;
    threadsafe_queue& operator=(const threadsafe_queue& other) = delete;

    std::shared_ptr<T> try_pop() {
        std::unique_ptr<node> old_head = try_pop_head();
        return old_head ? old_head->data : std::shared_ptr<T>();
    }
    
    bool try_pop(T& value) {
        std::unique_ptr<node> const old_head = try_pop_head(value);
        return old_head;
    }

    void push(T new_value) {
        std::shared_ptr<T> new_data(std::make_shared<T>(std::move(new_value)));
        std::unique_ptr<node> p(new node);
        std::lock_guard<std::mutex> lock(tail_mutex);
        tail->data = new_data;
        node* const new_tail = p.get();     // 即指针本身是常量，指向的对象可以修改
        tail->next = std::move(p);
        tail = new_tail;
        data_cond.notify_one();
    }

    std::shared_ptr<T> wait_and_pop() {
        std::unique_ptr<node> const old_head = wait_pop_head();
        return old_head->data;
    }

    void wait_and_pop(T& value) {
        std::unique_ptr<node> const old_head = wait_pop_head(value);
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(head_mutex);
        return (head.get() == get_tail());
    }
};

int main() {
    threadsafe_queue<int> q;
    std::thread t1([&q](){
        q.push(1);
        q.push(2);
        q.push(3);
        q.push(4);
        q.push(5);
        q.push(6);
    });
    std::thread t2([&q](){
        std::cout << *q.wait_and_pop() << std::endl;
        std::cout << *q.wait_and_pop() << std::endl;
        std::cout << *q.wait_and_pop() << std::endl;
    });
    
    std::thread t3([&q](){
        std::cout << *q.wait_and_pop() << std::endl;
        std::cout << *q.wait_and_pop() << std::endl;
        std::cout << *q.wait_and_pop() << std::endl;
    });
    t1.join();
    t2.join();
    t3.join();
    return 0;
}