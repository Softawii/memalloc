#include <iostream>
#include "memalloc.hpp"

#include "core/memalloc_core.hpp"

// Default namespace
using namespace std;
// Memalloc Namespace
namespace mm = memalloc;


int main(int argc, char **argv) {

    int * arr = (int *) mm::malloc(sizeof(int) * 15);
    int * arr2 = (int *) mm::malloc(sizeof(int) * 15);


    printf("Pointer Address: %p\n", arr);
    printf("Pointer Address: %p\n", arr2);

    
    printf("arr2 - arr = %ld\n", arr2 - arr - sizeof(mm_core::block_t));

    printf("Free Status: %d\n", mm::free(arr2));



}