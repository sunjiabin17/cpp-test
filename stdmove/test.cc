#include <iostream>

class Foo {
public:
    Foo(): x(112) {std::cout << "Foo()" << std::endl;}
    ~Foo() {std::cout << "~Foo()" << std::endl;}
    Foo(Foo&& foo) {std::cout << "Foo(Foo&&)" << std::endl;}
    Foo(const Foo& foo) {std::cout << "Foo(Foo&)" << std::endl;}
    Foo& operator=(Foo&& foo) {std::cout << "operator=(Foo&&)" << std::endl;}
    Foo& operator=(Foo& foo) {std::cout << "operator=(Foo&)" << std::endl;}   
    
    int x;
};

class Bar {
public:
    Foo foo;
    Foo func() {
        return foo;     // 1. 调用拷贝构造函数
    }
};



Foo func1() {
    Foo foo;                // 1. 默认构造函数
    return foo;             // 2. 调用移动构造函数转移给临时对象
                            // 3. 函数退出，foo调用析构函数
}

Foo func2() {
    Foo foo;                // 1. 默认构造函数
    return std::move(foo);  // 2. foo先转成右值，然后调用移动构造函数转移给临时对象
                            // 3. 函数退出，foo调用析构函数
}

Foo&& func3() {
    Foo foo;                // 1. 默认构造函数
    return std::move(foo);  // 2. foo先转成右值，临时对象也为右值，直接转移给临时对象
                            // 3. 函数退出，foo调用析构函数
}


int main() {
    Foo a1 = func1();       // 4. 临时对象转移给a1，调用移动构造函数
                            // 5. 临时对象调用析构函数
    std::cout << a1.x << "----------------" << std::endl;

    // Bar bar;
    // Foo foo = bar.func();


    // Foo a2 = func2();       // 4. 临时对象转移给a2，调用移动构造函数
    //                         // 5. 临时对象调用析构函数      
    // std::cout << a2.x << "----------------" << std::endl;
    
    // Foo&& a22 = func2();    // 4. 临时对象为右值，直接转移给a22
    // std::cout << a22.x << "----------------" << std::endl;

    // Foo&& a3 = func3();     // 4. 临时对象为右值，直接转移给a3
    // std::cout << a3.x << std::endl; // 5. a3引用的临时对象已经析构，a3成为悬空引用


    return 0;
                            // 函数退出，全部调用析构函数

}