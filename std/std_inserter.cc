#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

int main() {
  std::vector<int> a{1, 2, 3, 4, 5};
  std::vector<int> b;
  b.reserve(a.size());
  std::copy(a.begin(), a.end(), std::back_inserter(b));
  std::copy(b.begin(), b.end(), std::ostream_iterator<int>(std::cout, " "));

  std::vector<int> c;
  c.reserve(a.size());
  std::copy(a.begin(), a.end(), std::inserter(c, c.begin()));
  for (auto i : c) {
    std::cout << i << " ";
  }
  return 0;
}