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
}
