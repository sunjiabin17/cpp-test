#include <iostream>

// class Base {
// public:
//     Base(): a(1) {}
//     virtual void func() { std::cout << "Base" << std::endl; }
//     int a;
// };
// class Derived: public Base {
// public:
//     Derived(): b(2) {}
//     virtual void func() override {std::cout << "Derived" << std::endl;}
//     int a;
//     int b;
// };

// int main() {

//     Base* base = new Base();
//     Base* derived = new Derived();

//     Base* p_base = nullptr;
//     Derived* p_derived1 = nullptr;
//     Derived* p_derived2 = nullptr;

//     p_derived1 = dynamic_cast<Derived*>(base);
//     if (p_derived1 == nullptr) {
//         std::cout << "p_derived is nullptr" << std::endl;
//     } else {
//         std::cout << "p_derived is not nullptr" << std::endl;
//         p_derived1->func();
//         std::cout << p_derived1->a << std::endl;
//     }

//     p_derived2 = dynamic_cast<Derived*>(derived);
//     if (p_derived2 == nullptr) {
//         std::cout << "p_derived is nullptr" << std::endl;
//     } else {
//         std::cout << "p_derived is not nullptr" << std::endl;
//         p_derived2->func();
//         std::cout << p_derived1->a << std::endl;
//     }

//     return 0;
// }

int main() {
    // 浮点数表示法测试
    std::string S("0");
    std::string E(8, '1');
    std::string M(23, '0');
    std::string str = S + E + M;
    std::cout << str << std::endl;
    int dec = 0;
    for (int i = 0; i < str.size(); ++i) {
        dec |= ((str[i] - '0') << (31 - i));
    }

    float b = *(reinterpret_cast<float*>(&dec));
    std::cout << b << std::endl;

    return 0;
}