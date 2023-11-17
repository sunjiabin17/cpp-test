#include <iostream>
#include <string>
#include <functional>

int main() {
  std::hash<std::string> hash_str;
  std::hash<int> hash_int;

  int n = 222;
  std::string str = "hello world";
  std::cout << hash_str(str) << std::endl;
  std::cout << hash_int(n) << std::endl;
  return 0;
}