all: bin
PHONY: all clean

CC = g++
CXXFLAGS=-std=c++11 -Wall -g -pthread

future.o: future.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^

bin: future.o
	$(CC) $(CXXFLAGS) -o $@ $^

clean:
	rm -f future.o bin

