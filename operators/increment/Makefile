all: bin
PHONY: all clean

CC := clang++
CXXFLAGS := -std=c++11 -Wall -O3 -g

bin: increment.cc
	$(CC) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf *.o bin	