all: bin

PHONY: all clean

CC=g++
CXXFLAGS=-std=c++11 -Wall -g -pthread

bin: thread_safe_stack.o
	$(CC) $(CXXFLAGS) -o $@ $^

thread_safe_stack.o: thread_safe_stack.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -f thread_safe_stack.o bin