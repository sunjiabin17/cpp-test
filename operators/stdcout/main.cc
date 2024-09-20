#include <iostream>
#include <string>

class MyClass {
private:
    int id;
    std::string name;

public:
    MyClass(int id, const std::string& name) : id(id), name(name) {}

    // 重载 << 运算符，用于自定义打印
    friend std::ostream& operator<<(std::ostream& os, const MyClass& obj) {
        os << "MyClass{id: " << obj.id << ", name: " << obj.name << "}";
        return os;
    }
};

int main() {
    MyClass myObj(1, "Example Object");
    std::cout << myObj << std::endl;
    return 0;
}
