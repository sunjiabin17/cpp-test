#include <iostream>
#include <future>
#include <vector>
#include "thread_pool.h"

int main(int argc, char** argv) {
  
  // ThreadPool pool(4);
  // for (int i = 0; i < 10; ++i) {
  //   pool.Enqueue([i]() {
  //     std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % 100));
  //     std::cout << "executing task in thread " << std::this_thread::get_id()
  //               << " with index " << i << std::endl;
  //   });
  // }
  // // 未进行同步, 该句代码可以执行在pool中的任务之前
  // std::cout << "main thread exits" << std::endl;


  ThreadPool pool(4);
  std::vector<std::shared_ptr<std::promise<void>>> readys;  // promise只能被set一次
  for (int i = 0; i < 10; ++i) {
    auto ready = std::make_shared<std::promise<void>>();
    readys.push_back(ready);
    pool.Enqueue([i, ready]() {
      std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % 100));
      std::cout << "executing task in thread " << std::this_thread::get_id()
                << " with index " << i << std::endl;
      ready->set_value();
    });
  }
  // 同步, 等待pool中的所有任务执行完成
  for (auto& ready : readys) {
    ready->get_future().wait();
    // std::cout << "task is ready" << std::endl;
  }
  std::cout << "main thread exits" << std::endl;
  return 0;
}
