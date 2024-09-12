#include "test.h"
#include <string>
#include <vector>
#include <iostream>
#include <utility>


struct Impl {
  int a = 10;
  std::string b{"hello"};
  std::vector<int> c{1, 2, 3};
};

A::A() : impl(std::make_unique<Impl>()) {}

void A::print() {
  std::cout << "a = " << impl->a << std::endl;
  std::cout << "b = " << impl->b << std::endl;
  std::cout << "c = ";
  for (auto i : impl->c) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}
