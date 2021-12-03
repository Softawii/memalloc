#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <filesystem>

#include <string>
#include <string.h>

#include <assert.h>

#include "memalloc.hpp"
#include "core/memalloc_core.hpp"
#include "lib/App.h"

#define GREEN "\033[0;32m"
#define COLOR_RESET "\033[0m"
#define RED "\033[0;31m" 
#define YELLOW "\033[0;33m"

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
    
    assert(ptr != NULL);
    
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


/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int test_overlap(void * (*allocator)(size_t), void (*deallocator)(void *), size_t size) {
    
        int *integers1 = (int *) allocator(sizeof(int) * size);
        
        for (size_t i = 0; i < size; i++) {
            integers1[i] = 10;
        }

        int *integers2 = (int *) allocator(sizeof(int) * size);

        for (size_t i = 0; i < size; i++) {
            integers2[i] = 5;
        }

        for (size_t i = 0; i < size; i++) {
            assert(integers1[i] == 10);
            assert(integers2[i] == 5);

        }

        deallocator(integers1);
        deallocator(integers2);

        return 0;
}

int main(int argc, char **argv) {
    string type = "memalloc";
    Test_PTR test = test_alloc;
    string test_name;
    int count = 100;
    
    Stopwatch stopwatch;
    FREQUENCY(stopwatch);

    /**
     * @brief Command line arguments parsing 
     */
    for(int i = 1; i < argc; i++) {
        if  (strcmp(argv[i], "--std") == 0) type = "std";
        else if(strcmp(argv[i], "-n") == 0) count = atoi(argv[i+1]);

        // Functions to Run
        // Maybe change it to a map ok?
        else if(strcmp(argv[i], "--test_base") == 0)         { test = test_base; test_name = "test_base"; }
        else if(strcmp(argv[i], "--test_malloc_free") == 0)  { test = test_alloc_and_dealloc; test_name = "test_alloc_and_dealloc"; }
        else if(strcmp(argv[i], "--test_alloc") == 0)        { test = test_alloc; test_name = "test_alloc"; }
        else if(strcmp(argv[i], "--test_overlap") == 0)      { test = test_overlap; test_name = "test_overlap"; }
    }

    std::ofstream myfile;

    if(std::filesystem::exists("./res/results.csv")) {
        myfile.open("./res/results.csv", std::ofstream::app);
    }
    else {
        myfile.open("./res/results.csv", std::ofstream::app);
        myfile << "test" << "," << "type" << "," << "interactions" << "," << "elapsed_time" << endl;
        
    }
    /**
     * @brief Base stats 
     */
    cout << "Running " << YELLOW << type << COLOR_RESET << " tests with " << YELLOW << count << COLOR_RESET << " iterations" << endl;
    myfile << test_name << "," << type << "," << count << ",";

    /**
     * @brief Just select the allocator to use and run the test
     */
    void * (*allocator)(size_t) = type.compare("std") == 0 ? malloc : mm::malloc;
    void (*deallocator)(void *) = type.compare("std") == 0 ? free : mm::free;


    cout << "Batch of tests in " << type << endl;
    
    cout << RED;
    START_STOPWATCH(stopwatch);
    for(int i = 1; i <= count; i += 1) test(allocator, deallocator, i * 5);
    STOP_STOPWATCH(stopwatch);
    cout << COLOR_RESET;  

    cout << GREEN << "Elapsed Time: " << std::to_string(stopwatch.mElapsedTime) << COLOR_RESET << endl;
    myfile << std::to_string(stopwatch.mElapsedTime) << endl;
}