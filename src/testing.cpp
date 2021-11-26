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

    printf("arr: %p\n", arr);
    printf("arr2: %p\n", arr2);


    printf("Free Status: %d\n", mm::free(arr2));

    int * arr3 = (int *) mm::malloc(sizeof(int) * 25);

    printf("arr3: %p\n", arr3);









}