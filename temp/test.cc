#include <iostream>

class Foo {
public:
    Foo(): x(112) {std::cout << "Foo()" << std::endl;}
    ~Foo() {std::cout << "~Foo()" << std::endl;}

    Foo(Foo&& Foo) {std::cout << "Foo(Foo&&)" << std::endl;}
    Foo(const Foo& Foo) {std::cout << "Foo(Foo&)" << std::endl;}

    Foo& operator=(Foo&& Foo) {std::cout << "operator=(Foo&&)" << std::endl;}
    Foo& operator=(Foo& Foo) {std::cout << "operator=(Foo&)" << std::endl;}
    
    int x;
};


Foo func1() {
    Foo foo;
    // std::cout << "func1" << std::endl;
    return foo;
}

Foo func2() {
    Foo foo;
    // std::cout << "func2" << std::endl;
    return std::move(foo);
}

Foo&& func3() {
    Foo foo;
    // std::cout << "func3" << std::endl;
    return std::move(foo);
}

int main() {
    // Foo a1 = func1();
    // std::cout << &a1 << std::endl;
    // std::cout << a1.x << std::endl;
    // std::cout << "----------------" << std::endl;
    // Foo a2 = func2();
    // std::cout << &a2 << std::endl;
    // std::cout << a2.x << std::endl;
    // std::cout << "----------------" << std::endl;
    // Foo&& a3 = func3();
    // std::cout << &a3 << std::endl;
    // std::cout << a3.x << std::endl;

    int x = 123;
    int&& y = std::move(x);
    std::cout << x << std::endl;
    std::cout << y << std::endl;
    return 0;
}