all: objects lib clean_objects
	g++ src/testing.cpp -lmemalloc -L./bin/ -o testing.out  -O3 -std=c++17

run:
	./testing.out

objects:
	g++ -c -fpic src/memalloc.cpp src/core/memalloc_core.cpp -O3

lib:
	-mkdir bin
	ar -cvq -o bin/libmemalloc.a memalloc_core.o memalloc.o

clean: clean_objects
	rm testing.out
	rm ./bin/libmemalloc.a

clean_objects:
	-rm memalloc.o
	-rm memalloc_core.o