#include <iostream>
#include <atomic>
#include <thread>

template<typename T>
class lock_free_stack {
private:
    struct node {
        std::shared_ptr<T> data;
        node* next;
        node(T const& data_): data(std::make_shared<T>(data_)) {}
    };
    std::atomic<node*> head;
    std::atomic<unsigned> threads_in_pop;
    std::atomic<node*> to_be_deleted;

    static void delete_nodes(node* nodes) {
        while (nodes) {
            node* next = nodes->next;
            delete nodes;
            nodes = next;
        }
    }

    void try_reclaim(node* old_head) {
        if (threads_in_pop == 1) {
            node* nodes_to_delete = to_be_deleted.exchange(nullptr);    // 声明可删除列表，exchange() 允许使用新选的值替换已存储的值，并且返回原始值
            if (--threads_in_pop == 0) {    // 计数器减 1，并且判断是否只有一个线程调用 pop()
                delete_nodes(nodes_to_delete);
            } else if (nodes_to_delete) {
                chain_pending_nodes(nodes_to_delete);   // 将其挂在等待删除链表后
            }
            delete old_head;
        } else {
            chain_pending_node(old_head);
            --threads_in_pop;
        }
    }

    void chain_pending_nodes(node* nodes) {
        node* last = nodes;
        while (node* const next = last->next) {    // 找到最后一个节点
            last = next;
        }
        chain_pending_nodes(nodes, last);
    }

    void chain_pending_nodes(node* first, node* last) {
        last->next = to_be_deleted;     // 将可删除列表的头节点指向 first
        while (!to_be_deleted.compare_exchange_weak(last->next, first));    // 将 first 赋值给 to_be_deleted，如果 to_be_deleted 与 last->next 相等，则表明没人修改，此时将 to_be_deleted 指向 first；否则 last->next 指向 to_be_deleted，回退到上一步
    }

    void chain_pending_node(node* n) {
        chain_pending_nodes(n, n);  // 添加单个节点是一种特殊情况，因为需要将这个节点作为第一个节点进行添加（同时作为最后一个节点）
    }

public:
    void push(T const& data) {
        // 1. 创建新节点 new_node
        node* const new_node = new node(data);
        // 2. new_node->next 指向 head
        new_node->next = head.load();
        // 3. head 与 new_node->next 相等时，表明没人修改，此时将 head 指向 new_node；否则 new_node->next 指向 head，回退到上一步
        while (!head.compare_exchange_weak(new_node->next, new_node));
    }

    // void pop(T& result) {
    //     node* old_head = head.load();
    //     while (old_head && !head.compare_exchange_weak(old_head, old_head->next));
    //     result = old_head->data;
    // }

    std::shared_ptr<T> pop() {
        ++threads_in_pop;
        node* old_head = head.load();
        while (old_head && !head.compare_exchange_weak(old_head, old_head->next));
        std::shared_ptr<T> res;
        if (old_head) {
            res.swap(old_head->data);
        }
        try_reclaim(old_head);
        return res;
    }
};


int main(int argc, char** argv) {
    lock_free_stack<int> stack;
    // stack.push(1);
    // stack.push(2);
    std::thread t([&stack]() {
        for (int i = 0; i < 100; ++i) {
            stack.push(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    });
    // std::thread t1([&stack]() {
    //     int result;
    //     stack.pop(result);
    //     std::cout << result << std::endl;
    // });
    // std::thread t2([&stack]() {
    //     int result;
    //     stack.pop(result);
    //     std::cout << result << std::endl;
    // });
    std::thread t3([&stack]() {
        for (int i = 0; i < 100; ++i) {
            auto result = stack.pop();
            if (result)
                std::cout << *result << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    });

    t.join();
    // t1.join();
    // t2.join();
    t3.join();

    return 0;
}