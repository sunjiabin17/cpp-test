all: build
build: bin

CC=g++
# -std=c++11: 使用C++11标准进行编译。
# -Wall: 开启所有警告信息。
# -pthread: 启用POSIX线程支持。
# -g: 生成调试信息。
# -Wextra: 开启额外的警告信息。
# -Wpedantic: 开启符合ISO C++标准的警告信息。
# -Werror: 将所有警告信息视为错误。
CXXFLAGS=-std=c++11 -Wall -g -pthread
# LDFLAGS=-lpthread

hello_ref.o: hello_ref.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^

bin: hello_ref.o
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f hello_ref.o bin