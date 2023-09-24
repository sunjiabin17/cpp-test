#include <thread>
#include <atomic>
#include <iostream>

class Foo {
public:
    Foo(int x) : x_(x) {}

    void func() {
        std::cout << "func" << std::endl;
    }

    int x() const {
        return x_;
    }

private:
    int x_;
};

int main() {
    Foo foo[5] = {Foo(1), Foo(20), Foo(33), Foo(44), Foo(555)};
    std::atomic<Foo*> p(foo);
    std::cout << "p: " << p << std::endl;
    std::cout << "p.load(): " << p.load() << std::endl;
    std::cout << "p.load()->x(): " << p.load()->x() << std::endl;
    
    Foo* q = p.fetch_add(2);    // 将p的值加2，返回原来的值
    std::cout << "p: " << p << std::endl;
    std::cout << "p.load(): " << p.load() << std::endl;
    std::cout << "p.load()->x(): " << p.load()->x() << std::endl;
    std::cout << "q: " << q << std::endl;
    std::cout << "q->x(): " << q->x() << std::endl;
    
    return 0;
}