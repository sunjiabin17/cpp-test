#include <iostream>
#include <memory>

class Test {
public:
    Test() {
        std::cout << "Test()" << std::endl;
    }
    ~Test() {
        std::cout << "~Test()" << std::endl;
    }
    static void Create(int x, std::unique_ptr<Test>& model) {
        model.reset(new Test());
        model->x_ = x;
        std::cout << "model: " << model.get() << std::endl;
        std::cout << "model->x_: " << model->x_ << std::endl;
    }

private:
    int x_;
};

int main(int argc, char** argv) {
  std::unique_ptr<Test> model;
  int x = 1;
  Test::Create(1, model);
  return 0;
}