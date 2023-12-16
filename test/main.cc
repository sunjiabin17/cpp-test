#include <iostream>

int main() {
  int a = 1;
  int* b = &a;
  std::cout << "sizeof(b)=" << sizeof(b) << std::endl;
  return 0;
}