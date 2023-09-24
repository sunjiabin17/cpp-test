all: bin
PHONY: all clean

CC = g++
CXXFLAGS=-std=c++11 -Wall -g -pthread

promise.o: promise.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^

bin: promise.o
	$(CC) $(CXXFLAGS) -o $@ $^

clean:
	rm -f promise.o bin

