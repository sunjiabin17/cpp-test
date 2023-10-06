all: bin
PHONY: all clean

CC = g++
CXXFLAGS=-std=c++11 -Wall -g -pthread

bin: lock_free_stack.o
	$(CC) $(CXXFLAGS) -o $@ $^

lock_free_stack.o: lock_free_stack.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -f lock_free_stack.o bin
