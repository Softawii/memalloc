// Default
#include <unistd.h>
#include <sys/types.h>

// Memory allocation
#include "memalloc_core.hpp"

#define BLOCK_SIZE sizeof(struct s_block)

/**
 * @brief The namespace mm_core contains the core of the memory manager. 
 * @details The core is responsible for allocating and freeing memory in a low level, using sbrk.
 */
namespace mm_core {
    /* Base Pointer */
    void * base = NULL;
    
    /**
     * @brief splitting a block into two blocks, the second one will be free. 
     * 
     * @param b 
     * @param size 
     */
    void split(block_t b, size_t size) {
        block_t new_b = (block_t) b->data + size;
        new_b->size = b->size - size - BLOCK_SIZE;
        
        new_b->next = b->next;
        new_b->prev = b;
        
        new_b->free = true;

        new_b->ptr = new_b->data;
        b->size = size;
        b->next = new_b;

        if (new_b->next != NULL) {
            new_b->next->prev = new_b;
        }
    }


    /**
     * @brief This function is trying to find some block that fit the size.
     * 
     * @param last 
     * @param size 
     * @return block_t 
     */
    block_t find(block_t * last, size_t size) {
        
        block_t b = base;
        
        while (b && ! (b->free && b->size >= size)) {
            *last = b;
            b = b->next;
        }
        return (b);
    }

    /**
     * @brief This function will extend the heap with the given size.
     * 
     * @param last 
     * @param size 
     * @return block_t 
     */
    block_t extend_heap(block_t last, size_t size) {
        int sb; block_t b;

        b = sbrk(0);
        sb = (int) sbrk(BLOCK_SIZE + size);

        // Something Wrong :(
        if(sb < 0) return (NULL);

        b->size = s;
        b->next = NULL;
        b->prev = last;
        b->prtr = b->data;

        if(last)
            last->next = b;
        
        b->free = false;

        return b;
    }
}


