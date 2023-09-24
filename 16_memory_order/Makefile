all: bin bin.1 bin.2
PHONY: all clean

CC = g++
CXXFLAGS=-std=c++11 -Wall -g -pthread

memory_order.o: memory_order.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^

bin: memory_order.o
	$(CC) $(CXXFLAGS) -o $@ $^


bin.1: memory_order_1.cc
	$(CC) $(CXXFLAGS) -o $@ $^

bin.2: memory_order_2.cc
	$(CC) $(CXXFLAGS) -o $@ $^

clean:
	rm -f memory_order.o bin bin.1 bin.2