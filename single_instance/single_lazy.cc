#include <iostream>

// 非线程安全
class SingleClass {
public:
    static SingleClass* get_instance() {
        if (instance == nullptr) {
            instance = new SingleClass();
        }
        return instance;
    }

private:
    static SingleClass* instance;
    SingleClass() {};
};

// 类的静态成员变量需要在类外分配内存空间
SingleClass* SingleClass::instance = nullptr;

int main() {
    SingleClass *instance1 = SingleClass::get_instance();
    SingleClass *instance2 = SingleClass::get_instance();
    std::cout << instance1 << std::endl;
    std::cout << instance2 << std::endl;
    return 0;
}