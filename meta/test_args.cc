#include "iter_args.h"
#include <sstream>
#include <iostream>

namespace iter {

struct MultiArgs: public IterArgs<MultiArgs> {
public:
  std::stringstream ss;
  MultiArgs() = default;

  template <typename T>
  void operator()(T&& arg) {
    ss << arg << " ";
  }

  std::string str() {
    ss << std::endl;
    return ss.str();
  }
};

namespace detail {
template <typename... Args>
void print_multi_args(const Args&... args) {
  std::cout << MultiArgs().apply(args...).str();
}

} // namespace detail

} // namespace iter


int main() {
  iter::detail::print_multi_args(1, 2, 3, "hello", 4.5);
  return 0;
}
