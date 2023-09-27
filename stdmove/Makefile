all: bin
PHONY: all clean

CC=g++
CXXFLAGS=-std=c++11 -Wall -O0 -g -pthread -fno-elide-constructors

bin: test.o
	$(CC) $(CXXFLAGS) -o $@ $^

test.o: test.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -f *.o bin