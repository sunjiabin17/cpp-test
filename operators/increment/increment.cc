#include <iostream>
#include <memory>

class A {
public:
    A(int _x): x(_x) {std::cout << "A(int)" << std::endl;}
    ~A() {std::cout << "~A()" << std::endl;}
    int x;

    A& operator++() {
        ++x;
        return *this;
    }

    A operator++(int) {
        A tmp(*this);
        ++x;
        return tmp;
    }
};

int main() {
    A a(1), b(1);
    std::cout << "++a: " << (++a).x << "-" << a.x << std::endl;
    std::cout << "b++: " << (b++).x << "-" << b.x << std::endl;
    return 0;
}