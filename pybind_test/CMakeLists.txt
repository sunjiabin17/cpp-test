project("test")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(pybind11)

pybind11_add_module(test_add test.cc)
