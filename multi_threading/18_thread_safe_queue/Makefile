all: bin.1 bin.2 bin.3

PHONY: all clean

CC = g++
CXXFLAGS=-std=c++11 -Wall -g -pthread

bin.%: thread_safe_queue%.o
	$(CC) $(CXXFLAGS) -o $@ $^

thread_safe_queue%.o: thread_safe_queue%.cc
	$(CC) $(CXXFLAGS) -c -o $@ $^
# bin.1: thread_safe_queue1.o
# 	$(CC) $(CXXFLAGS) -o $@ $^

# thread_safe_queue1.o: thread_safe_queue1.cc
# 	$(CC) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -f thread_safe_queue*.o bin.*
