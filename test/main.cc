#include <functional>
#include <iostream>
#include <memory>
#include <type_traits>
#include <array>


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

void test1(int a, std::false_type) {
  std::cout << a << std::endl;
}

void test1(int a, std::true_type) {
  std::cout << a << std::endl;
}

template <typename V, typename... T>
constexpr auto make_array(T&&... t)-> std::array<V, sizeof...(T)> {
  return {{std::forward<T>(t)...}};
}


int main() {
  A a;
  std::cout << a.a << std::endl;
  std::cout << __GXX_ABI_VERSION << std::endl;

  B b;
  B c;
  c = std::move(b);
  std::cout << b.b << std::endl;

  test1(1, std::is_integral<int>());
  auto arr = make_array<int>(1,2,3);
  for (auto i : arr) {
    std::cout << i << std::endl;
  }
  return 0;
}
