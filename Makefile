all: objects lib clean_objects
	g++ src/testing.cpp -lmemalloc -L./bin/ -o testing.out -std=c++17

run:
	./testing.out

objects:
	g++ -c -fpic src/memalloc.cpp src/core/memalloc_core.cpp

lib:
	ar -cvq -o bin/libmemalloc.a memalloc_core.o memalloc.o

clean: clean_objects
	rm testing
	rm libmemalloc.so

clean_objects:
	rm memalloc.o
	rm memalloc_core.o