all: bin
PHONY: all bin
CXXFLAGS=-std=c++11 -Wall -g -pthread
CC=g++

thread_guard.o: thread_guard.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^

bin: thread_guard.o
	$(CC) $(CXXFLAGS) -o $@ $^

clean:
	rm -f thread_guard.o bin