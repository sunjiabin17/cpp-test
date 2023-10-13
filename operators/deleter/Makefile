all: bin
PHONY: all clean

CC := clang++
CXXFLAGS := -std=c++11 -Wall -O0 -g -fno-elide-constructors

bin: deleter.cc
	$(CC) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf *.o bin	