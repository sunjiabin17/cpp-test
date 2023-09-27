#include <iostream>

class Foo {
public:
    Foo(): x(112) {std::cout << "Foo()" << std::endl;}
    ~Foo() {std::cout << "~Foo()" << std::endl;}
    Foo(Foo&& foo): x(123) {std::cout << "Foo(Foo&&)" << std::endl;}
    Foo(const Foo& foo):x(456) {std::cout << "Foo(Foo&)" << std::endl;}
    Foo& operator=(Foo&& foo) {std::cout << "operator=(Foo&&)" << std::endl;}
    Foo& operator=(Foo& foo) {std::cout << "operator=(Foo&)" << std::endl;}   
    int x;
};

Foo func2() {
    Foo foo;                // 1. 默认构造函数
    return std::move(foo);  // 2. foo先转成右值，然后调用移动构造函数转移给临时对象
                            // 3. 函数退出，foo调用析构函数
}

int main() {
    Foo a2 = func2();       // 4. 临时对象转移给a2，调用移动构造函数
                            // 5. 临时对象调用析构函数      
    std::cout << a2.x << "----------------" << std::endl;
    
    Foo&& a22 = func2();    // 4. 临时对象为右值，直接转移给a22

    std::cout << a22.x << "----------------" << std::endl;
    return 0;
                            // 函数退出，a2析构，a22析构

}