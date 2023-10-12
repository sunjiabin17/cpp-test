#include <thread>
#include <iostream>
#include <mutex>


class ojbect {
public:
    int a;
    int b;
    ojbect(int aa, int bb) : a(aa), b(bb) {}
    ojbect(const ojbect& o) : a(o.a), b(o.b) {}
    ojbect& operator=(const ojbect& o) {
        a = o.a;
        b = o.b;
        return *this;
    }
};

class A {
public:
    ojbect obj;
    std::mutex m;

public:
    A(const ojbect& o) : obj(o) {}
    
    void swap(A& a, A& b) {
        if (&a == &b) return;
        std::lock(a.m, b.m);
        std::lock_guard<std::mutex> lock_a(a.m, std::adopt_lock);
        std::lock_guard<std::mutex> lock_b(b.m, std::adopt_lock);
        std::swap(a.obj, b.obj);
    }
};

int main() {
    ojbect o1(1, 2);
    ojbect o2(3, 4);
    A a1(o1);
    A a2(o2);
    std::cout << "a1: " << a1.obj.a << " " << a1.obj.b << std::endl;
    std::cout << "a2: " << a2.obj.a << " " << a2.obj.b << std::endl;
    std::thread t1(&A::swap, &a1, std::ref(a1), std::ref(a2));
    // std::thread t2(&A::swap, &a2, std::ref(a2), std::ref(a1));
    t1.join();
    // t2.join();
    std::cout << "a1: " << a1.obj.a << " " << a1.obj.b << std::endl;
    std::cout << "a2: " << a2.obj.a << " " << a2.obj.b << std::endl;
    return 0;
}