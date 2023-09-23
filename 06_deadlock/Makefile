all: bin
PHONY: all clean

CC = g++
CXXFLAGS=-std=c++11 -Wall -g -pthread

deadlock.o: deadlock.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^

bin: deadlock.o
	$(CC) $(CXXFLAGS) -o $@ $^

clean:
	rm -f deadlock.o bin