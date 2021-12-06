#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <filesystem>

#include <iomanip>
#include <limits>

#include <string>
#include <string.h>

#include <assert.h>
#include <malloc.h>

#include "memalloc.hpp"
#include "info/memalloc_info.hpp"
#include "lib/App.h"

#define GREEN "\033[0;32m"
#define COLOR_RESET "\033[0m"
#define RED "\033[0;31m" 
#define YELLOW "\033[0;33m"

// Default namespace
using namespace std;
// Memalloc Namespace
namespace mm = memalloc;
std::ofstream myfile;

struct mallinfos {
    struct mm_info::mallinfo info1;
    struct mallinfo info2;
    bool mymalloc;
};

void save_mallinfo(struct mallinfos *infos, string test_name, int count) {
    if(infos->mymalloc){
        infos->info1 = mm_info::mallinfo();
        myfile << test_name << "," << "memmaloc" << "," << count << "," << mm::get_find() << "," << infos->info1.ordblks << "," << infos->info1.uordblks << "," 
        << infos->info1.fordblks << "," << infos->info1.keepcost << endl;
    }
    else{
        infos->info2 = mallinfo();
        myfile << test_name << "," << "std" << "," << count << "," << "std" << "," << infos->info2.ordblks << "," << infos->info2.uordblks << "," 
        << infos->info2.fordblks << "," << infos->info2.keepcost << endl;
    }
}

typedef int (*Test_PTR)(void * (*allocator)(size_t), void (*deallocator)(void *), size_t size, struct mallinfos *infos);

/**
 * @brief Test function for the memalloc library, it's a trivial test.
 * 
 * @param allocator malloc
 * @param deallocator free
 * @param size size of the memory to allocate
 * @return int 
 */
int test_base(void * (*allocator)(size_t), void (*deallocator)(void *), size_t size, struct mallinfos *infos) {
    int * ptr = (int *) allocator(sizeof(int) * size);

    #ifdef TESTING_MALLINFO
        save_mallinfo(infos, "test_base", size);
    #endif
    
    assert(ptr != NULL);
    
    deallocator(ptr);

    #ifdef TESTING_MALLINFO
        save_mallinfo(infos, "test_base", size);
    #endif
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
int test_alloc_and_dealloc(void * (*allocator)(size_t), void (*deallocator)(void *), size_t size, struct mallinfos* infos) {

    int *integers = (int *) allocator(sizeof(int) * size);

    #ifdef TESTING_MALLINFO
        save_mallinfo(infos, "test_alloc_and_dealloc", size);
    #endif
    for (size_t i = 0; i < size; i++) {
        integers[i] = 10;
    }

    for (size_t i = 0; i < size; i++) {
        assert(integers[i] == 10);
    }

    deallocator(integers);

    #ifdef TESTING_MALLINFO
        save_mallinfo(infos, "test_alloc_and_dealloc", size);
    #endif
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
int test_alloc(void * (*allocator)(size_t), void (*deallocator)(void *), size_t size, struct mallinfos* infos) {

    int *integers = (int *) allocator(sizeof(int) * size);
    
    #ifdef TESTING_MALLINFO
        save_mallinfo(infos, "test_alloc", size);
    #endif

    for (size_t i = 0; i < size; i++) {
        integers[i] = 10;
    }
    
    for (size_t i = 0; i < size; i++) {
        assert(integers[i] == 10);
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
int test_overlap(void * (*allocator)(size_t), void (*deallocator)(void *), size_t size, struct mallinfos* infos) {
    
        int *integers1 = (int *) allocator(sizeof(int) * size);
        
        for (size_t i = 0; i < size; i++) {
            integers1[i] = 10;
        }
        #ifdef TESTING_MALLINFO
            save_mallinfo(infos, "test_overlap", size);
        #endif
        int *integers2 = (int *) allocator(sizeof(int) * size);
        #ifdef TESTING_MALLINFO
            save_mallinfo(infos, "test_overlap", size);
        #endif
        for (size_t i = 0; i < size; i++) {
            integers2[i] = 5;
        }

        for (size_t i = 0; i < size; i++) {
            assert(integers1[i] == 10);
            assert(integers2[i] == 5);

        }

        deallocator(integers1);
        deallocator(integers2);
        #ifdef TESTING_MALLINFO
            save_mallinfo(infos, "test_overlap", size);
        #endif
        return 0;
}


int test_intensive_overlap(void * (*allocator)(size_t), void (*deallocator)(void *), size_t size, struct mallinfos* infos) {
        for(size_t n = 1; n < size; n++) {
            int *integers1 = (int *) allocator(sizeof(int) * n);
            #ifdef TESTING_MALLINFO
                save_mallinfo(infos, "test_intensive_overlap", size);
            #endif
            for (size_t i = 0; i < n; i++) {
                integers1[i] = 10;
            }
            
            int *integers2 = (int *) allocator(sizeof(int) * n);
            #ifdef TESTING_MALLINFO
                save_mallinfo(infos, "test_intensive_overlap", size);
            #endif
            for (size_t i = 0; i < n; i++) {
                integers2[i] = 5;
            }

            for (size_t i = 0; i < n; i++) {
                assert(integers1[i] == 10);
                assert(integers2[i] == 5);
            }

            deallocator(integers1);
            deallocator(integers2);
            #ifdef TESTING_MALLINFO
                save_mallinfo(infos, "test_intensive_overlap", size);
            #endif
        }

        return 0;
}

int main(int argc, char **argv) {
    string type = "memalloc";
    string find_type;
    Test_PTR test = test_alloc;
    string test_name;
    struct mallinfos infos;
    infos.mymalloc = true;
    bool print = false;
    int count = 100;

    Stopwatch stopwatch;
    FREQUENCY(stopwatch);

    /**
     * @brief Command line arguments parsing 
     */
    for(int i = 1; i < argc; i++) {
        if  (strcmp(argv[i], "--std") == 0) type = "std";
        else if(strcmp(argv[i], "-n") == 0) count = atoi(argv[i+1]);
        else if(strcmp(argv[i], "--print") == 0) print = true;

        // Functions to Run
        // Maybe change it to a map ok?
        else if(strcmp(argv[i], "--test_base") == 0)         { test = test_base; test_name = "test_base"; }
        else if(strcmp(argv[i], "--test_malloc_free") == 0)  { test = test_alloc_and_dealloc; test_name = "test_alloc_and_dealloc"; }
        else if(strcmp(argv[i], "--test_alloc") == 0)        { test = test_alloc; test_name = "test_alloc"; }
        else if(strcmp(argv[i], "--test_overlap") == 0)      { test = test_overlap; test_name = "test_overlap"; }
        else if(strcmp(argv[i], "--test_intensive_overlap") == 0)      { test = test_intensive_overlap; test_name = "test_intensive_overlap"; }


        // Find
        std::string arg(argv[i]);
        if(arg.find("--find") != std::string::npos) {
            bool found = mm::select_find(arg);
            if(!found) {
                cout << RED << "Error: " << arg << " not found" << COLOR_RESET << endl;
                return 1;
            }
        }
    }

    // Type of the find
    find_type = type.compare("std") == 0 ? "std" : mm::get_find();
    
    string filename = "./res/results.csv";
    #if defined(TESTING_MINIMUM) && defined(TESTING_MALLINFO)
        filename = "./res/minimum_mallinfo_results.csv";
    #elif defined(TESTING_MINIMUM)
        filename = "./res/minimum_results.csv";
    #endif
    if(std::filesystem::exists(filename)) {
        myfile.open(filename, std::ofstream::app);
    }
    else {
        myfile.open(filename, std::ofstream::app);
        #ifdef TESTING_MALLINFO
            myfile << "test" << "," << "type" << "," << "interactions" << "," << "find_type" << "," 
            << "ordblks" << "," << "uordblks" << "," << "fordblks" << "," << "keepcost" << endl;
        #else
            myfile << "test" << "," << "type" << "," << "interactions" << "," << "elapsed_time" << "," << "find_type" << endl;
        #endif
    }
    /**
     * @brief Base stats 
     */
    if (print)
        cout << "Running " << YELLOW << type << COLOR_RESET << " tests with " << YELLOW << count << COLOR_RESET << " iterations" << endl;

    /**
     * @brief Just select the allocator to use and run the test
     */
    void * (*allocator)(size_t) = type.compare("std") == 0 ? malloc : mm::malloc;
    void (*deallocator)(void *) = type.compare("std") == 0 ? free : mm::free;
    infos.mymalloc = type.compare("std") == 0 ? false : true;

    if(print)
        cout << "Batch of tests in " << type << endl;
    
    cout << RED;                
    
    START_STOPWATCH(stopwatch);
    #ifdef TESTING_MINIMUM 
        test(allocator, deallocator, count, &infos);
    #else
        for(int i = 1; i <= count; i += 1)  test(allocator, deallocator, i * 5, &infos);
    #endif
    STOP_STOPWATCH(stopwatch);

    
    cout << COLOR_RESET;  

    if(print)
        cout << GREEN << "Elapsed Time: " << std::to_string(stopwatch.mElapsedTime) << COLOR_RESET << endl;
    #ifndef TESTING_MALLINFO
        myfile << test_name << "," << type << "," << count << "," << std::fixed << std::setprecision(10) << stopwatch.mElapsedTime << "," << find_type << std::endl;
    #endif
}