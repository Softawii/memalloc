CXXFLAGS = -O3 -Wall -std=c++11 -lstdc++fs
CXX = g++


all: objects lib clean_objects compile
	rm ./res/results.csv

debug: CXXFLAGS += -DMEMALLOC_CORE_DEBUG -g
debug: all

minimum: CXXFLAGS += -DTESTING_MINIMUM -g
minimum: objects lib clean_objects compile
	rm ./res/minimum_results.csv

run:
	./testing.out

objects:
	$(CXX) -c src/memalloc.cpp -o memalloc.o $(CXXFLAGS)
	$(CXX) -c src/core/memalloc_core.cpp -o memalloc_core.o $(CXXFLAGS)

lib:
	-mkdir bin
	ar rvs bin/libmemalloc.a memalloc_core.o memalloc.o

compile: 
	$(CXX) src/testing.cpp -o bin/testing.out $(CXXFLAGS) -std=c++17 -Lbin/ -lmemalloc

clean: clean_objects
	rm ./bin/testing.out
	rm ./bin/libmemalloc.a

clean_objects:
	-rm memalloc.o
	-rm memalloc_core.o