all: bin
PHONY: all clean

CC = g++
CXXFLAGS=-std=c++11 -Wall -g -pthread

conditional_variable.o: conditional_variable.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^

bin: conditional_variable.o
	$(CC) $(CXXFLAGS) -o $@ $^

clean:
	rm -f conditional_variable.o bin

