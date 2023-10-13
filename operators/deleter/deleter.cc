#include <algorithm>
#include <iostream>
#include <memory>

class Foo {
public:    
    int x;
    Foo(int _x): x(_x) {
        std::cout << "Foo(int)" << std::endl;
        }
    ~Foo() {
        std::cout << "~Foo()" << std::endl;
        }
    Foo(Foo&& foo) {
        x = foo.x;
        std::cout << "move" << std::endl;
        }
    Foo(const Foo& foo) {
        x = foo.x;
        std::cout << "copy" << std::endl;
        }
    Foo operator=(Foo&& foo) {
        x = foo.x;
        std::cout << "operator=(Foo&&)" << std::endl;
        return *this;
        }
    Foo operator=(Foo& foo) {
        x = foo.x;
        std::cout << "operator=(Foo&)" << std::endl;
        return *this;
        }
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

void print_address(void* a) {
    std::cout << "address a: " << a << std::endl;
    std::cout << "address &a: " << &a << std::endl;
    std::cout << "-----------" << std::endl;
}


int main() {
    // std::unique_ptr<Foo, deleter> a(new Foo(1));
    // std::unique_ptr<Foo, void(*)(Foo*)> a(new Foo(1), func_deleter);
    // int* a = new int(1);
    // deleter()(a);
    // std::unique_ptr<Foo, decltype(func_deleter)*> a(new Foo(255), func_deleter);
    // a.reset();

    // Foo* a = new Foo(1);
    // func_deleter(a);

    return 0;
}