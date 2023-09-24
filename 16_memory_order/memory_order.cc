#include <iostream>
#include <atomic>
#include <thread>

struct Node {
    int value;
    Node* next;
};

std::atomic<Node*> head(nullptr);

void producer() {
    Node* node1 = new Node{1, nullptr};
    Node* node2 = new Node{2, nullptr};
    node1->next = node2;
    // 假设有一个原子变量A，对其进行写操作X的时候施加了memory_order_release约束符，
    // 则在当前线程T1中，该操作X之前的任何读写操作指令都不能放在操作X之后。
    // 当另外一个线程T2对原子变量A进行读操作的时候，施加了memory_order_acquire约束符，
    // 则当前线程T1中写操作之前的任何读写操作都对线程T2可见
    head.store(node1, std::memory_order_release);
}

void consumer() {
    // 一个对原子变量的load操作时，使用memory_order_acquire约束符： 在当前线程中，该load之后读和写操作都不能被重排到当前指令前。
    // 如果其他线程使用memory_order_release约束符，则对此原子变量进行store操作，在当前线程中是可见的。
    Node* node = head.load(std::memory_order_acquire);
    if (node != nullptr) {
        std::cout << "node->value = " << node->value << std::endl;
        node = node->next;
    }
    if (node != nullptr) {
        std::cout << "node->value = " << node->value << std::endl;
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}