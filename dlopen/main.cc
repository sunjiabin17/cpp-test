#include <iostream>
#include <string>
#include <dlfcn.h>

#define LOG_INFO(x) \
    do {\
        std::cout << "[INFO] " << __FILE__ << ":" << __LINE__ << "\t" << x << std::endl;\
    } while (0)

#define LOG_ERROR(x) \
    do {\
        std::cout << "[ERROR] " << __FILE__ << ":" << __LINE__ << "\t" << x << std::endl;\
    } while (0)


int main(int argc, char** argv) {
    std::cout << "Hello, world!" << std::endl;
    if (argc <= 2) {
        LOG_ERROR("Usage: ./main <path_to_lib> symbol_name");
        return 0;
    }
    LOG_INFO("path: " << argv[1] << ", symbol_name: " << argv[2]);
    const char* path = argv[1];
    const char* symbol_name = argv[2];

    void *handle = dlopen(path, RTLD_LAZY);
    if (!handle) {
        LOG_ERROR("Error: " << dlerror());
        return 0;
    }

    typedef int (*my_add_t)(int, int);
    dlerror();    // 清除任何现有的错误
    my_add_t add_func = (my_add_t)dlsym(handle, symbol_name);
    if (!add_func) {
        LOG_ERROR("Error: " << dlerror());
        return 0;
    }
    LOG_INFO("my add function: add_func(1, 2) = "<< add_func(1, 2));
    return 0;
}