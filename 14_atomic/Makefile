all: bin
PHONY: all clean

CC = g++
CXXFLAGS=-std=c++11 -Wall -g -pthread

atomic.o: atomic.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^

bin: atomic.o
	$(CC) $(CXXFLAGS) -o $@ $^

clean:
	rm -f atomic.o bin

