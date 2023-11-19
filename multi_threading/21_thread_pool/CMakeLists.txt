project(Test CXX)
cmake_minimum_required(VERSION 2.8)

add_library(thread_pool thread_pool.cc)
target_include_directories(thread_pool PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(bin main.cc)
target_link_libraries(bin PRIVATE thread_pool pthread)

add_executable(bin1 promise_sync.cc)
target_link_libraries(bin1 PRIVATE thread_pool pthread)