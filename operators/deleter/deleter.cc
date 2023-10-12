#include <iostream>
#include <memory>

class Foo {
public:    
    int x;
    Foo(int _x): x(_x) {std::cout << "Foo(int)" << std::endl;}
    ~Foo() {std::cout << "~Foo()" << std::endl;}
};

struct deleter {
    template <typename T>
    void operator()(T* p) {
        std::cout << "struct deleter " << p << std::endl;
        delete p;
    }
};

void func_deleter(Foo* p) {
    std::cout << "func_delete " << p << std::endl;
    delete p;
}

int main() {
    // std::unique_ptr<Foo, deleter> a(new Foo(1));
    // std::unique_ptr<Foo, void(*)(Foo*)> a(new Foo(1), func_deleter);
    std::unique_ptr<Foo, decltype(func_deleter)*> a(new Foo(1), func_deleter);
    return 0;
}