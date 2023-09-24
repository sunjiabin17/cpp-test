all: bin
PHONY: all clean

CC = g++
CXXFLAGS=-std=c++11 -Wall -g -pthread

quick_sort.o: quick_sort.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^

bin: quick_sort.o
	$(CC) $(CXXFLAGS) -o $@ $^

clean:
	rm -f quick_sort.o bin

