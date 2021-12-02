#include <iostream>
#include <stdlib.h>
#include "memalloc.hpp"

#include "core/memalloc_core.hpp"

// Default namespace
using namespace std;
// Memalloc Namespace
namespace mm = memalloc;


int test_allocation(void * (*allocator)(size_t), void (*deallocator)(void *), size_t size) {
    int * ptr = (int *) allocator(sizeof(int) * size);
    
    if (ptr == NULL) {
        cout << "Failed to allocate memory" << endl;
        return 1;
    }
    
    deallocator(ptr);
    return 0;
}


int main(int argc, char **argv) {

    cout << test_allocation(mm::malloc, mm::free, 10) << endl; 
    cout << test_allocation(malloc, free, 10) << endl; 

}