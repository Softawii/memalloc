#include <unistd.h> 

#include "memalloc.hpp"
#include "core/memalloc_core.hpp"

#include <iostream>

// Custom Compile: object file of core
using namespace mm_core;
using namespace std;

namespace memalloc {
    void * malloc(size_t size) {
        return mm_core::malloc(size);
    }

    void free(void * ptr) {
        mm_core::free(ptr);
    }

    bool select_find(string method) {
        return mm_core::select_find(method); 
    }

    string get_find() {
        return mm_core::get_find();
    }
}
