.PHONY: all clean
all: bin a.so b.so
clean:
	rm -f bin a.so b.so

bin: main.cc a.so b.so
	g++ --std=gnu++20 -g -o $@ $^ -ldl

a.so: lib_a.cc
	g++ --std=gnu++20 -g -shared -fPIC -o $@ $^

b.so: lib_b.cc
	g++ --std=gnu++20 -g -shared -fPIC -o $@ $^
