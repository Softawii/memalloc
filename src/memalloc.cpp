#include "memalloc.hpp"
#include "core/memalloc_core.hpp"
// Custom Compile: object file of core


namespace memalloc {

    void * malloc(size_t size) {
        // Oh no, we're out of memory!
        return (void *) -1;
    }
}
