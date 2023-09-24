all: bin
PHONY: all clean

CC = g++
CXXFLAGS=-std=c++11 -Wall -g -pthread

package_task.o: package_task.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^

bin: package_task.o
	$(CC) $(CXXFLAGS) -o $@ $^

clean:
	rm -f package_task.o bin

