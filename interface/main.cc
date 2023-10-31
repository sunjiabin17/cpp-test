#include <iostream>
#include <string>

struct I_info;

class INFO_A {
public:
    INFO_A(int x): x_(x) {}
    int x_;

};

int main() {
    INFO_A* a = new INFO_A(1);
    I_info* i = reinterpret_cast<I_info*>(a);

    INFO_A* a1 = reinterpret_cast<INFO_A*>(i);
    std::cout << a1->x_ << std::endl;

    return 0;
}