all: bin
PHONY: all clean

CC = g++
CXXFLAGS=-std=c++11 -Wall -g -pthread

future_exception.o: future_exception.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^

bin: future_exception.o
	$(CC) $(CXXFLAGS) -o $@ $^

clean:
	rm -f future_exception.o bin

