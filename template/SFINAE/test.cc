#include <type_traits>
#include <iostream>

template <class T>
class ArrayRef {
public:
  ArrayRef() {
    std::cout << "ArrayRef()" << std::endl;
  }

  explicit ArrayRef(int) {
    std::cout << "ArrayRef(int)" << std::endl;
  }

  /// Disallow accidental assignment from a temporary.
  ///
  /// The declaration here is extra complicated so that "arrayRef = {}"
  /// continues to select the move assignment operator.
  template <class U>
  std::enable_if_t<std::is_same<T, U>::value, ArrayRef>& operator=(
      U&& t) = delete;

  template <class U>
  std::enable_if_t<std::is_same<T, U>::value, ArrayRef>& operator=(
      std::initializer_list<U>) = delete;
};

int main() {
  ArrayRef<float> a;
  a = static_cast<decltype(a)>(1);
}
