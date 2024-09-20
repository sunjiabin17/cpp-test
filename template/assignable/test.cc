#include <type_traits>
#include <iostream>

class A final {
public:
  ~A() {
    std::cout << "A destructor" << std::endl;
  }
};

int main() {
  std::cout << std::is_move_assignable<A>::value << std::endl;
}
