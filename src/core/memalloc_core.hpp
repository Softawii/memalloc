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


#include <iostream>
using namespace std;

#define BLOCK_SIZE (sizeof(struct s_block) - 1)

/**
 * @brief That Namespace is the core of the library.
 * @details It contains the functions to allocate memory and to free memory in a low level
 */

namespace mm_core {

    /* Linked List of Blocks */
    typedef struct s_block * block_t;
    
    /**
     * @brief Block structure, contains the size of the block and the next block
     */
    struct s_block {
        size_t size;            /* Size of the block */
        struct s_block * next;  /* Next Block */
        struct s_block * prev;  /* Previous Block */
        void * ptr;             /* Pointer to the data */
        bool free;              /* Free */
        char data[1];           /* Data */
    } __attribute__((packed)); // Precisa disso aq, by EduardoFerro
    // O Compilador ta alinhando isso ai, ent~ao tem que remover o alinhamentog

    /**
     * Basic functions to the memory allocation.
     */
    void split(block_t b, size_t size);


    /**
     * @brief Find collection
     */
    bool select_find(string s);
    block_t find(block_t * last, size_t size);
    block_t find_first_fit(block_t * last, size_t size);
    block_t find_worst_fit(block_t * last, size_t size);


    /**
     * @brief Allocate memory
     */
    block_t extend_heap(block_t last, size_t size);


    /**
     * Function to help to free memory. 
     * 
     */
    block_t fusion(block_t b);

    block_t get_block(void * ptr);

    bool valid_address(void * ptr);

    void * malloc(size_t size);

    void free(void * ptr);

    

} // end namespace mm_core

#endif