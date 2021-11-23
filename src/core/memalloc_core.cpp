// Default
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

// Memory allocation
#include "memalloc_core.hpp"


/**
 * @brief The namespace mm_core contains the core of the memory manager. 
 * @details The core is responsible for allocating and freeing memory in a low level, using sbrk.
 */
namespace mm_core {

    void* base = NULL;

    
    /**
     * @brief splitting a block into two blocks, the second one will be free. 
     * 
     * @param b The block that will be splited
     * @param size The location where the block will be splited
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
     * @param last Last block of the heap.
     * @param size The size that the function will look for.
     * @return block_t 
     */
    block_t find(block_t * last, size_t size) {
        
        block_t b = (block_t) base;

        while (b && ! (b->free && b->size >= size)) {
            *last = b;
            b = b->next;
        }
        return (b);
    }

    /**
     * @brief This function will extend the heap with the given size.
     * 
     * @param last Last block of the heap.
     * @param size How much the heap will be extended.
     * @return block_t 
     */
    block_t extend_heap(block_t last, size_t size) {
        // TODO: Verificar se o bloco atual está livre, se estiver expandir de acordo com o size.

        int *sb; block_t b;

        // Dei cast aqui
        b = (block_t) sbrk(0);
        sb = (int*) sbrk(BLOCK_SIZE + size);

        // Something Wrong :(
        if(*sb < 0) return (NULL);

        b->size = size;
        b->next = NULL;
        b->prev = last;
        b->ptr = b->data;

        if(last)
            last->next = b;
        
        b->free = false;

        return b;
    }


    /**
     * @brief Fusion of two released blocks
     * 
     * @param b 
     * @return block_t 
     */
    block_t fusion(block_t b){
        if (b->next && b->next->free){
            b->size += BLOCK_SIZE + b->next->size;
            b->next = b->next->next;
            if (b->next) {
                b->next->prev = b;
            }
        }
        return b;
    }

    /**
     * @brief Get the block object of a given pointer.
     * 
     * @param ptr 
     * @return block_t 
     */
    block_t get_block(void * ptr) {

        // Free in the middle of a block may broke that shit
        char *tmp = (char*) ptr;
        return (block_t) (ptr = tmp - BLOCK_SIZE);
    }

    bool valid_address(void * ptr) {
        
        printf("Valid Address Test\n");
        if (base) {
            printf("Base\n");
            if(ptr > base && ptr < sbrk(0)) {
                // Here we aren't allowing the user to free a block in the middle
                block_t blk = get_block(ptr);
                
                printf("Ok\n");
                printf("PTR: %p\n", ptr);
                printf("GetBlock\n");
                printf("SIZE: %ld\n", blk->size);
                printf("PTR: %p\n", blk->ptr);


        
                return ptr == (get_block(ptr))->ptr;
            }
        }
        return false;
    }
}