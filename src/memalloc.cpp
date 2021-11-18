#include "memalloc.hpp"
#include "core/memalloc_core.hpp"
// Custom Compile: object file of core
using namespace mm_core;

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
}
