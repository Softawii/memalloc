CXXFLAGS = -O3 -Wall -std=c++11 -lstdc++fs
CXX = g++


all: objects lib clean_objects compile
	rm ./res/results.csv

debug: CXXFLAGS += -DMEMALLOC_CORE_DEBUG -g
debug: all

minimum: CXXFLAGS += -DTESTING_MINIMUM -g
minimum: objects lib clean_objects compile
	rm ./res/minimum_results.csv
	
mallinfo: CXXFLAGS += -DTESTING_MALLINFO -DTESTING_MINIMUM -g 
mallinfo: objects lib clean_objects compile
	rm ./res/minimum_mallinfo_results.csv

run:
	./testing.out

objects:
	$(CXX) -c src/memalloc.cpp -o memalloc.o $(CXXFLAGS)
	$(CXX) -c src/core/memalloc_core.cpp -o memalloc_core.o $(CXXFLAGS)
	$(CXX) -c src/info/memalloc_info.cpp -o memalloc_info.o $(CXXFLAGS)


lib:
	-mkdir bin
	ar rvs bin/libmemalloc.a memalloc_core.o memalloc.o memalloc_info.o
	ar rvs bin/libmemalloc_info.a memalloc_core.o memalloc_info.o

compile: 
	$(CXX) src/testing.cpp -o bin/testing.out $(CXXFLAGS) -std=c++17 -Lbin/ -lmemalloc  -Lbin/ -lmemalloc_info

clean: clean_objects
	rm ./bin/testing.out
	rm ./bin/libmemalloc.a
	rm ./bin/libmemalloc_info.a

clean_objects:
	-rm memalloc.o
	-rm memalloc_core.o
	-rm memalloc_info.o