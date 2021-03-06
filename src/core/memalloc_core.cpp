// Default
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>


#include <iostream>
using namespace std;

// Memory allocation
#include "memalloc_core.hpp"

/**
 * @brief The namespace mm_core contains the core of the memory manager. 
 * @details The core is responsible for allocating and freeing memory in a low level, using sbrk.
 */
namespace mm_core {
    
    void* base = NULL;                                              // Pointer to the first element of the list of memory blocks.
    block_t (* selected_find) (block_t *, size_t) = find_first_fit; // A selected block of memory. Default: first_fit.
    string selected_find_name = "first_fit";                         // Name of the selected block of memory. Default: first_fit.


    /**
     * @brief splitting a block into two blocks, the second one will be free. 
     * 
     * @param b The block that will be splited
     * @param size The location where the block will be splited
     */
    void split(block_t b, size_t size) {
        block_t new_b = (block_t) (b->data + size);
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
     * @brief Function to select an algorithm to find a block of memory.
     * 
     * @param s 
     * @return true 
     * @return false 
     */
	bool select_find(string s) {
	
		if (s.compare("--find_first_fit") == 0) {
            
            #ifdef MEMALLOC_CORE_DEBUG
                cout << "Selected find: first_fit" << endl;
            #endif

			selected_find = find_first_fit;
            selected_find_name = "first_fit";
			return true;
		}
		else if (s.compare("--find_worst_fit") == 0) {
            #ifdef MEMALLOC_CORE_DEBUG
                cout << "Selected find: worst_fit" << endl;
            #endif

			selected_find = find_worst_fit;
            selected_find_name = "worst_fit";
			
            return true;

		}
        else if (s.compare("--find_null") == 0) {
            #ifdef MEMALLOC_CORE_DEBUG
                cout << "Selected find: null" << endl;
            #endif

			selected_find = find_null;
            selected_find_name = "null";
			
            return true;

		}
		return false;
	}


    string get_find() {
        return selected_find_name;
    }


    /**
     * @brief This function is trying to find some block that fit the size.
     * 
     * @param last Last block of the heap.
     * @param size The size that the function will look for.
     * @return block_t 
     */
    block_t find(block_t * last, size_t size) {
        return selected_find(last, size);
    }

    /**
     * @brief Find function that will find the first block that fit the size.
     * 
     * @param last 
     * @param size 
     * @return block_t The first block that fit the size or NULL if there is no block that fit the size.
     */
    block_t find_first_fit(block_t * last, size_t size) {
        block_t b = (block_t) base;

        while (b && ! (b->free && b->size >= size)) {
            *last = b;
            b = b->next;
        }
        return (b);
    }
    
    /**
     * @brief Find function that will find the biggest block that fit the size.
     * 
     * @param last 
     * @param size 
     * @return block_t the biggest block or NULL if there is no block that fit the size.
     */
    block_t find_worst_fit(block_t * last, size_t size) {
        
        block_t b = (block_t) base;
        block_t bigger = NULL;
        while (b && ! (b->free && b->size == size)) {
            if(b->size >= size && 
                ((b->free && bigger && b->size > bigger->size) || 
                (b->free && !bigger)) ) 
            {
                bigger = b;
            }
            
            *last = b;
            b = b->next;
        }
        if(b && b->size == size) {
            return b;
        }

        return (bigger);
    }

    /**
     * @brief just NULL
     * 
     * @param last 
     * @param size 
     * @return NULL
     */
    block_t find_null(block_t * last, size_t size) {
        return NULL;
    }


    /**
     * @brief This function will extend the heap with the given size.
     * 
     * @param last Last block of the heap.
     * @param size How much the heap will be extended.
     * @return block_t 
     */
    block_t extend_heap(block_t last, size_t size) {
        // TODO: Verificar se o bloco atual est?? livre, se estiver expandir de acordo com o size.

        block_t b;

        // Dei cast aqui
        b = (block_t) sbrk(0);

        // Something Wrong :(
        if(sbrk(BLOCK_SIZE + size) == (void *) -1) return (NULL);

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
        
        if (base) {
            if(ptr > base && ptr < sbrk(0)) {        
                return ptr == (get_block(ptr))->ptr;
            }
        }
        return false;
    }

 
    void * malloc(size_t size) {
        
        block_t b;
        // TODO: Aplicar fun????o align para deixar os valores arredondados para pot??ncia de 2.
        size_t s = size;

        if(base) {
            block_t last = (block_t) base;
            b = find(&last, size);

            if(b) {
                if((b->size - s) >= (BLOCK_SIZE + 1 /*TODO: O n??mero 1 deve ser trocado pelo valor do align*/))
                    split(b, s);
                b->free = false;
            } else {
                // Verificar se o last est?? livre antes de extender?
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
                b = fusion(b->prev);
            if(b->next)
                fusion(b);
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