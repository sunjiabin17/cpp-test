#include <thread>
#include <atomic>
#include <cassert>
#include <string>
 
std::atomic<std::string*> ptr;
int data;
 
void producer() {
  std::string* p  = new std::string("Hello"); // L10
  data = 42; // L11
  ptr.store(p, std::memory_order_release); // L12
}
 
void consumer() {
  std::string* p2;
  while (!(p2 = ptr.load(std::memory_order_consume))); // L17
  assert(*p2 == "Hello"); // L18
  assert(data == 42); // L19
}
 
int main() {
  std::thread t1(producer);
  std::thread t2(consumer);
  t1.join(); 
  t2.join();
  
  return 0;
}

/*
与memory_order_acquire一节中示例相比较，producer()没有变化，
consumer()函数中将load操作的标记符从memory_order_acquire变成了memory_order_consume。
而这个变动会引起如下变化：producer()中，ptr与p有依赖 关系，则p不会重排到store()操作L12之后，
而data因为与ptr没有依赖关系，则可能重排到L12之后，所以可能导致L19的assert()失败。
*/