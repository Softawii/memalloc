/**
 * 
 * @file memalloc_core.hpp
 * @authors Yan Figueiredo (yancfm@gmail.com) Sérgio Rezende (sergiorezende2001@gmail.com)
 * @brief This file is part of a C++ library for handle with memory allocation.
 * @details Every function of this library is inspired in the standard C allocation library.
 * @version 0.1
 * @date 2021-11-18
 * @copyright MIT License (c) 2021 Softawii
 * 
 */

#ifndef __MEMALLOC_CORE_HPP__
#define __MEMALLOC_CORE_HPP__


#define BLOCK_SIZE sizeof(struct s_block)

/**
 * @brief That Namespace is the core of the library.
 * @details It contains the functions to allocate memory and to free memory in a low level
 */

namespace mm_core {

    /* Linked List of Blocks */
    typedef struct s_block * block_t;
    
    /* Base Pointer */
    extern void * base;

    /**
     * @brief Block structure, contains the size of the block and the next block
     */
    struct s_block {
        /* Size of the block */
        size_t size;
        /* Next Block */
        block_t next;
        /* Previous Block */
        block_t prev;
        /* Free */
        bool free;
        /* Pointer to the data */
        void * ptr;
        /* Data */
        char data[1];
    };

    /**
     * Basic functions to the memory allocation.
     */
    void split(block_t b, size_t size);

    block_t find(block_t * last, size_t size);

    block_t extend_heap(block_t last, size_t size);

    block_t fusion(block_t b);

} // end namespace mm_core

#endif