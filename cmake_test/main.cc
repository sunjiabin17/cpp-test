#include <iostream>
#include "my_add.h"


int main(int argc, char** argv) {
    std::cout << "Hello, world!" << std::endl;
    int c = my_add(1, 2);
    
    std::cout << c << std::endl;
    return 0;
}