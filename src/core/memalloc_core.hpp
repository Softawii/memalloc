/*
This file is part of a C++ library for handle with memory allocation.
Every function of this library is inspired in the standard C allocation library.
*/
#ifndef __MEMALLOC_CORE_HPP__
#define __MEMALLOC_CORE_HPP__

/**
 * @brief That Namespace is the core of the library.
 * @details It contains the functions to allocate memory and to free memory in a low level
 */

namespace mm_core {

    /**
     * Basic functions to the memory allocation.
     */
    int init_memory_manager(int size);

    void * malloc(size_t size);

    int free(void * id);


} // end namespace mm_core

#endif