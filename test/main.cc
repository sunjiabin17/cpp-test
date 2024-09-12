#include <functional>
#include <iostream>
#include <memory>

class A {
public:
  A() = default;
  int a = 123;
};

class B {
public:
  int b = 456;
  ~B() {
    std::cout << "B destructor" << std::endl;
  }
};

int main() {
  A a;
  std::cout << a.a << std::endl;
  std::cout << __GXX_ABI_VERSION << std::endl;

  B b;
  B c;
  c = std::move(b);
  std::cout << b.b << std::endl;
  return 0;
}
