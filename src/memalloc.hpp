/**
 * @file memalloc.hpp
 * @author Yan Figueiredo (yancfm@gmail.com)
 * @brief This file is responsible for the interface between the user and the library. 
 * @details Functions like malloc, free, realloc, calloc, etc. are implemented here.
 * I recommend to use this library in the same way as the standard C library..
 * @version 0.1
 * @date 2021-11-18
 * 
 * @copyright MIT License (c) 2021 Yan Figueiredo
 * 
 */
#ifndef __MEMALLOC_HPP__
#define __MEMALLOC_HPP__


/**
 * @brief This file is responsible for the interface between the user and the library. 
 * I created it by separating the implementation part from the interacting part, I think it's better that way.
 */
namespace memalloc {

    // I really don't know why it's useful to have this function, but I'm keeping it for now.
    int init(int size);

    void * malloc(size_t size);

    int free(void * ptr);

}

#endif // End of __MEMALLOC_HPP__