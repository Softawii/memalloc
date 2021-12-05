#include "memalloc_info.hpp"
#include "memalloc_core.hpp"
#include "memalloc_core.cpp"

namespace mm_info {

    int get_ordblks() {
        mm_core::block_t b = (mm_core::block_t) mm_core::base;
        int count = 0;
        while (b)
        {
            if (b->free)
                count++;
            b = b->next;
        }
        
        return count;
    }

    int get_uordblks() {
        mm_core::block_t b = (mm_core::block_t) mm_core::base;
        int count = 0;
        while (b)
        {
            if (!b->free)
                count += b->size;
            b = b->next;
        }
        
        return count;
    }

    int get_fordblks() {
        mm_core::block_t b = (mm_core::block_t) mm_core::base;
        int count = 0;
        while (b)
        {
            if (b->free)
                count += b->size;
            b = b->next;
        }
        
        return count;
    }

    int get_keepcost() {
        mm_core::block_t b = (mm_core::block_t) mm_core::base;
        int count = 0;
        while (b)
        {
            if(b->free)
                count += b->size;
            else
                count = 0;
        }
        
        return count;
    }

    struct mallinfo mallinfo() {
        struct mallinfo info;

        info.ordblks = get_ordblks();
        info.uordblks = get_uordblks();
        info.fordblks = get_fordblks();
        info.keepcost = get_keepcost();

        return info;
    }
}