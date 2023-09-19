all: build
build: hello_bin

CC=g++
CXXFLAGS=-std=c++11 -Wall -pthread
LDFLAGS=-lpthread

hello.o: hello.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^

hello_bin: hello.o
	$(CC) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f hello.o hello_bin