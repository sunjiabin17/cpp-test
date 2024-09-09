#include <type_traits>
#include <string>
#include <iostream>

struct A {
  std::string to_string();
};

struct B {};

template <typename T, typename = std::string>
class has_to_string : public std::false_type {};

template <class T>
class has_to_string<T, decltype(std::declval<T>().to_string())> : public std::true_type {};

template<class T, T t> struct C {};  // primary template
template<> struct C<int, 1> {};    // error: type of the argument 1 is T,
                                     // which depends on the parameter T

void test();
int main() {
  std::cout << has_to_string<A>::value << std::endl;
  std::cout << has_to_string<B>::value << std::endl;
  std::cout << std::is_void<decltype(test())>::value << std::endl;


  return 0;
}
