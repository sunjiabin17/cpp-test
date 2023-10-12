all: bin
PHONY: all clean

CC = g++
CXXFLAGS=-std=c++11 -Wall -g -pthread

shared_future.o: shared_future.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^

bin: shared_future.o
	$(CC) $(CXXFLAGS) -o $@ $^

clean:
	rm -f shared_future.o bin

