#include <iostream>
#include <boost/type_index.hpp>


using boost::typeindex::type_id_with_cvr;


int func(float a, double b) {
  return static_cast<int>(a + b);
}

template <typename T>
decltype(auto) func1(T&& a) {
  std::cout << "func1, T: " << type_id_with_cvr<T>().pretty_name() << std::endl;
  std::cout << "func1: ParamType: " << type_id_with_cvr<decltype(a)>().pretty_name() << std::endl;
  return std::forward<T>(a);
}

template <typename T>
decltype(auto) func2(const T& a) {
  std::cout << "func2, T" << type_id_with_cvr<T>().pretty_name() << std::endl;
  std::cout << "func2: ParamType: " << type_id_with_cvr<decltype(a)>().pretty_name() << std::endl;
  return a;
}

template <typename T>
decltype(auto) func3(const T* a) {
  std::cout << "func3, T" << type_id_with_cvr<T>().pretty_name() << std::endl;
  std::cout << "func3: ParamType: " << type_id_with_cvr<decltype(a)>().pretty_name() << std::endl;
  return a;
}



int main() {
  auto f1 = func;
  auto& f2 = func;

  auto x = {1, 2, 3};

  int a = 1;
  func1(1);
  func1(a);

  func2(1);
  func2(a);

  auto r = func3(&a);

  std::cout << "type f1: " << type_id_with_cvr<decltype(f1)>().pretty_name() << std::endl;
  std::cout << "type f2: " << type_id_with_cvr<decltype(f2)>().pretty_name() << std::endl;
  std::cout << "type x: " << type_id_with_cvr<decltype(x)>().pretty_name() << std::endl;
  std::cout << "nullptr_t: " << type_id_with_cvr<std::nullptr_t>().pretty_name() << std::endl;
  return 0;
}
