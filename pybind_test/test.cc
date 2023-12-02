#include <pybind11/pybind11.h>
#include <string>

int add(int i, int j) {
    return i + j;
}

float add(float i, float j) {
    return i + j;
}

std::string add(std::string i, std::string j) {
    return i + j;
}

PYBIND11_MODULE(test_add, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring
    m.def("add", (int (*)(int, int)) &add, "A function which adds two numbers");
    m.def("add", (float (*)(float, float)) &add, "A function which adds two numbers");
    m.def("add", (std::string (*)(std::string, std::string)) &add, "A function which adds two numbers");
}