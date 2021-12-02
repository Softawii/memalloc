#include <iostream>
#include <stdlib.h>

#include <string>
#include <string.h>

#include <assert.h>

#include "memalloc.hpp"
#include "core/memalloc_core.hpp"
#include "lib/App.h"



// Default namespace
using namespace std;
// Memalloc Namespace
namespace mm = memalloc;

typedef int (*Test_PTR)(void * (*allocator)(size_t), void (*deallocator)(void *), size_t size);

/**
 * @brief Test function for the memalloc library, it's a trivial test.
 * 
 * @param allocator malloc
 * @param deallocator free
 * @param size size of the memory to allocate
 * @return int 
 */
int test_allocation(void * (*allocator)(size_t), void (*deallocator)(void *), size_t size) {
    int * ptr = (int *) allocator(sizeof(int) * size);
    
    if (ptr == NULL) {
        cout << "Failed to allocate memory" << endl;
        return 1;
    }
    
    deallocator(ptr);
    return 0;
}


int test_edu(void * (*allocator)(size_t), void (*deallocator)(void *), size_t size) {

    int *inteiros = (int *) allocator(sizeof(int) * size);
    
    for (size_t i = 0; i < size; i++) {
        inteiros[i] = 10;
    }

    for (size_t i = 0; i < size; i++) {
        assert(inteiros[i] == 10);
    }

    deallocator(inteiros);

    return 0;
}


int main(int argc, char **argv) {
    string type = "memalloc";
    
    Stopwatch stopwatch;
    FREQUENCY(stopwatch);

    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "--std") == 0) type = "std";
    }

    void * (*allocator)(size_t) = type.compare("std") == 0 ? malloc : mm::malloc;
    void (*deallocator)(void *) = type.compare("std") == 0 ? free : mm::free;

    Test_PTR test = test_edu;

    cout << "Batch of tests in " << type << endl;

    START_STOPWATCH(stopwatch);
    for(int i = 10; i < 100000; i += 100) test(allocator, deallocator, i);
    STOP_STOPWATCH(stopwatch);

    cout << "Elapsed Time: " << std::to_string(stopwatch.mElapsedTime) << endl;
}