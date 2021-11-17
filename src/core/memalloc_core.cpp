// Default
#include <unistd.h>
#include <sys/types.h>

// Memory allocation
#include "memalloc_core.hpp"

#define BLOCK_SIZE sizeof(struct s_block)


namespace mm_core {
    /* Base Pointer */
    void * base = NULL;
    /* Linked List of Blocks */
    typedef struct s_block * block_t;

    /**
     * @brief Block structure, contains the size of the block and the next block
     */
    struct s_block {
        /* Size of the block */
        size_t size;
        /* Next Block */
        block_t next;
        /* Free */
        bool free;
        /* Data */
        char data[1];
    };

    /**
     * @brief This function is trying to find some block that fit the size.
     * 
     * @param last 
     * @param size 
     * @return block_t 
     */
    block_t find(block_t last, size_t size) {
        
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
        block_t b = sbrk(0);
        
        if (sbrk(BLOCK_SIZE + size) == (void *) -1)
            return (NULL);
        
        b->size = size;
        b->free = false;
        b->next = NULL;

        if(last)
            last->next = b;
        return (b);

    void * malloc(size_t size) {

        // Break :: The final of the heap
        block_t b = sbrk(0);

        sbrk(sizeof(struct s_block) + size);
        
        b->size = size;

        return ptr;
    }
}


