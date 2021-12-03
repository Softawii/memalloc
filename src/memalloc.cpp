#include <unistd.h> 

#include "memalloc.hpp"
#include "core/memalloc_core.hpp"

#include <iostream>

// Custom Compile: object file of core
using namespace mm_core;
using namespace std;


namespace memalloc {

    void * malloc(size_t size) {
        
        block_t b, last;
        // TODO: Aplicar função align para deixar os valores arredondados para potência de 2.
        size_t s = size;

        if(base) {
            last = (block_t) base;
            b = mm_core::find(&last, size);

            if(b) {
                if((b->size - s) >= (BLOCK_SIZE + 1 /*TODO: O número 1 deve ser trocado pelo valor do align*/))
                    mm_core::split(b, s);
                b->free = false;
            } else {
                // Verificar se o last está livre antes de extender?
                b = extend_heap(last, s);
                if(!b)
                    return NULL;
            }
        }
        else {
            b = extend_heap(NULL, s);
            if(!b)
                return NULL;
            base = b;
        }

        // Return allocated space
        return b->data;
    }

    void free(void * ptr) {
        if(valid_address(ptr)) {


            block_t b = get_block(ptr);
            b->free = true;

            if(b->prev && b->prev->free)
                b = mm_core::fusion(b->prev);
            if(b->next)
                mm_core::fusion(b);
            else {
                if(b->prev)
                    b->prev->next = NULL;
                else
                    base = NULL;

                if(brk(b) == -1)
                    return;
            }
            
            return;
        }

        return;
    }
}
