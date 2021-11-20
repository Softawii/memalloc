all: objects lib
	g++ src/testing.cpp -L. -lmemalloc -o testing.out -std=c++17

run:
	./testing.out

objects:
	g++ -c -fpic src/core/memalloc_core.cpp src/memalloc.cpp

lib:
	g++ -shared -o libmemalloc.so memalloc_core.o memalloc.o

clean: clean_objects
	rm testing
	rm libmemalloc.so

clean_objects:
	rm memalloc.o
	rm memalloc_core.o