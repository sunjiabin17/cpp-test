#include <thread>
#include <atomic>
#include <cassert>
#include <string>
 
std::atomic<std::string*> ptr;
int data;
 
void producer() {
  std::string* p  = new std::string("Hello");  // L10
  data = 42; // L11
  ptr.store(p, std::memory_order_release); // L12
}
 
void consumer() {
  std::string* p2;
  while (!(p2 = ptr.load(std::memory_order_acquire))); // L17
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
在上述例子中，原子变量ptr的写操作(L12)施加了memory_order_release标记，
根据前面所讲，这意味着在线程producer中，L10和L11不会重排到L12之后；
在consumer线程中，对原子变量ptr的读操作L17施加了memory_order_acquire标记，
也就是说L8和L19不会重排到L17之前，这也就意味着当L17读到的ptr不为null的时候，
producer线程中的L10和L11操作对consumer线程是可见的，因此consumer线程中的assert是成立的。
*/