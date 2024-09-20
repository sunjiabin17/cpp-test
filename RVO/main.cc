#include <iostream>

class A {
public:
  A() {
    std::cout << "constructor" << std::endl;
  }
  ~A() {
    std::cout << "destructor" << std::endl;
  }
  A(const A& a) {
    std::cout << "copy constructor" << std::endl;
  }
  A(A&& a) {
    std::cout << "move constructor" << std::endl;
  }
  A& operator=(const A& a) {
    std::cout << "copy assignment" << std::endl;
    return *this;
  }
  A& operator=(A&& a) {
    std::cout << "move assignment" << std::endl;
    return *this;
  }
};

class B : public A {
};


A func() {
  A a;
  return a;
}

A func2() {
  return func();
}


int main() {
  A a = func2();

  return 0;
}
