#include <functional>
#include <iostream>
#include <memory>

std::unique_ptr<int> f() {
  return std::make_unique<int>(10);
}

double f() {
  return 1.23333;
}

double f2() {
  int* a = new int(20);
  [[maybe_unused]] &a;
}

int main() {
  std::cout << f2() << std::endl;
  return 0;
}
