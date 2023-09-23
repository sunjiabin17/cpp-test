all: bin
PHONY: all bin clean

CC=g++
CXXFLAGS=-std=c++11 -Wall -g -pthread

bin: scoped_thread.o
	$(CC) $(CXXFLAGS) -o $@ $^

scoped_thread.o: scoped_thread.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -f scoped_thread.o bin