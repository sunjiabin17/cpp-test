#include <iostream>

#include "thread_pool.h"

int main(int argc, char** argv) {
  ThreadPool pool(4);

  for (int i = 0; i < 10; ++i) {
    pool.Enqueue([i]() {
      std::cout << "executing task in thread " << std::this_thread::get_id()
                << " with index " << i << std::endl;
      
    });
  }

  return 0;
}
