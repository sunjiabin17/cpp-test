all: bin
PHONY: all clean

CC=g++
CXXFLAGS=-Wall -std=c++11 -g

bin: main.o
	$(CC) $(CXXFLAGS) $^ -o $@

main.o: main.cpp
	$(CC) $(CXXFLAGS) -c $^ -o $@

clean:
	rm -rf *.o bin