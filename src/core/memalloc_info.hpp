/**
 * @file memalloc_info.hpp
 * @author Yan Figueiredo (yancfm@gmail.com) Sérgio Rezende (sergiorezende2001@gmail.com)
 * @brief This file is part of a C++ library for handle with memory allocation.
 * @version 0.1
 * @date 2021-12-05
 * 
 * @copyright MIT License (c) 2021 Softawii
 * 
 */

namespace mm_info {

    /**
     * @brief Estrutura usada para retornar as informações do estado atual da heap.
     */
    struct mallinfo {
        int ordblks;  /* number of free chunks */
        int uordblks; /* total allocated space */
        int fordblks; /* total free space */
        int keepcost; /* top-most, releasable (via malloc_trim) space */
    };

    struct mallinfo mallinfo(void);
}