#include <iostream>

namespace a {

__attribute__((visibility("default")))
void print1() {
  std::cout << "lib_a" << std::endl;
}

__attribute__((visibility("hidden")))
void print2() {
  std::cout << "lib_a" << std::endl;
}

} // namespace a
