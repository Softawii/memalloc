CXXFLAGS = -O3 -Wall -std=c++11
CXX = g++


all: objects lib clean_objects
	$(CXX) src/testing.cpp -o bin/testing.out $(CXXFLAGS) -std=c++17 -Lbin/ -lmemalloc

run:
	./testing.out

objects:
	$(CXX) -c src/memalloc.cpp -o memalloc.o $(CXXFLAGS)
	$(CXX) -c src/core/memalloc_core.cpp -o memalloc_core.o $(CXXFLAGS)

lib:
	-mkdir bin
	ar rvs bin/libmemalloc.a memalloc_core.o memalloc.o

clean: clean_objects
	rm testing.out
	rm ./bin/libmemalloc.a

clean_objects:
	-rm memalloc.o
	-rm memalloc_core.o