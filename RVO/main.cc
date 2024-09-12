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

A func() {
  A a;
  return a;
}

int main() {
  A a = func();
  return 0;
}
