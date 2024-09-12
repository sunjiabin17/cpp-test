#pragma once
#include <memory>

struct Impl;
class A {
public:
  A();
  ~A();
  void print();
private:
  std::unique_ptr<Impl> impl;
};
