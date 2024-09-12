#include <memory>
#include <iostream>

class A {
public:
  int a = 20;
};

struct del1 {
  void operator()(A* a) {
    std::cout << "del1 deleting A" << std::endl;
    delete a;
  }
};

void del2(A* a) {
  std::cout << "del2 deleting A" << std::endl;
  delete a;
}


int main() {
  double b = 2.222;
  auto p = std::make_unique<A>();
  auto p1 = std::unique_ptr<A, del1>(new A());
  std::cout << "sizeof(p1) = " << sizeof(p1) << std::endl;

  using del2_ptr = void(*)(A*);
  auto p2 = std::unique_ptr<A, del2_ptr>(new A(), del2);
  std::cout << "sizeof(p2) = " << sizeof(p2) << std::endl;

  auto del3 = [](A* a) {
    std::cout << "del3 deleting A" << std::endl;
    delete a;
  };
  auto p3 = std::unique_ptr<A, decltype(del3)>(new A(), del3);
  std::cout << "sizeof(p3) = " << sizeof(p3) << std::endl;
  std::cout << "sizeof(lambda) = " << sizeof(del3) << std::endl;

  std::shared_ptr<A> p4(new A());
  std::weak_ptr<A> wp = p4;
}
