all: bin
PHONY: all clean

CC = g++
CXXFLAGS=-std=c++11 -Wall -g -pthread

atomic_pointer.o: atomic_pointer.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^

bin: atomic_pointer.o
	$(CC) $(CXXFLAGS) -o $@ $^

clean:
	rm -f atomic_pointer.o bin

