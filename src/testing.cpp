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
int test_base(void * (*allocator)(size_t), void (*deallocator)(void *), size_t size) {
    int * ptr = (int *) allocator(sizeof(int) * size);
    
    if (ptr == NULL) {
        cout << "Failed to allocate memory" << endl;
        return 1;
    }
    
    deallocator(ptr);
    return 0;
}

/**
 * @brief 
 * 
 * @param allocator 
 * @param deallocator 
 * @param size 
 * @return int 
 */
int test_alloc_and_dealloc(void * (*allocator)(size_t), void (*deallocator)(void *), size_t size) {

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

/**
 * @brief 
 * 
 * @param allocator 
 * @param deallocator 
 * @param size 
 * @return int 
 */
int test_alloc(void * (*allocator)(size_t), void (*deallocator)(void *), size_t size) {

    int *inteiros = (int *) allocator(sizeof(int) * size);
    
    for (size_t i = 0; i < size; i++) {
        inteiros[i] = 10;
    }

    for (size_t i = 0; i < size; i++) {
        assert(inteiros[i] == 10);
    }

    return 0;
}


int main(int argc, char **argv) {
    string type = "memalloc";
    Test_PTR test = test_alloc;
    int count = 100;
    
    Stopwatch stopwatch;
    FREQUENCY(stopwatch);

    /**
     * @brief Command line arguments parsing 
     */
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "--std") == 0) type = "std";
        if(strcmp(argv[i], "-n") == 0) count = atoi(argv[i+1]);

        // Functions to Run
        // Maybe change it to a map ok?
        if(strcmp(argv[i], "--test_base") == 0)         test = test_base;
        if(strcmp(argv[i], "--test_malloc_free") == 0)  test = test_alloc_and_dealloc;
        if(strcmp(argv[i], "--test_alloc") == 0)        test = test_alloc;
    }

    /**
     * @brief Base stats 
     */
    cout << "Running " << type << " tests with " << count << " iterations" << endl;

    /**
     * @brief Just select the allocator to use and run the test
     */
    void * (*allocator)(size_t) = type.compare("std") == 0 ? malloc : mm::malloc;
    void (*deallocator)(void *) = type.compare("std") == 0 ? free : mm::free;


    cout << "Batch of tests in " << type << endl;

    START_STOPWATCH(stopwatch);
    for(int i = 1; i <= count; i += 1) test(allocator, deallocator, i * 5);
    STOP_STOPWATCH(stopwatch);

    cout << "Elapsed Time: " << std::to_string(stopwatch.mElapsedTime) << endl;
}