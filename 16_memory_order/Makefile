all: bin
PHONY: all clean

CC = g++
CXXFLAGS=-std=c++11 -Wall -g -pthread

memory_order.o: memory_order.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^

bin: memory_order.o
	$(CC) $(CXXFLAGS) -o $@ $^

clean:
	rm -f memory_order.o bin

