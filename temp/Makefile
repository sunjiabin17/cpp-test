all: bin
PHONY: all clean

CC=g++
CXXFLAGS=-std=c++11 -Wall -g -fno-elide-constructors -pthread

bin: test.o
	$(CC) $(CXXFLAGS) -o $@ $^

test.o: test.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -f *.o bin