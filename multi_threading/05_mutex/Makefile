all: bin
PHONY: all bin clean

CC=g++
CXXFLAGS=-std=c++11 -Wall -g -pthread

bin: lock_guard.o
	$(CC) $(CXXFLAGS) -o $@ $^

lock_guard.o: lock_guard.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -f lock_guard.o bin