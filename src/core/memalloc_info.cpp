#include "memalloc_info.hpp"
#include "memalloc_core.hpp"
#include "memalloc_core.cpp"

namespace mm_info {

    int get_ordblks(mm_core::block_t b) {
        if (b->free)
            return 1;
        
        return 0;
    }

    int get_uordblks(mm_core::block_t b) {
        if (!b->free)
            return b->size;

        return 0;
    }

    int get_fordblks(mm_core::block_t b) {
        if (b->free)
            return b->size;
        
        return 0;
    }

    int get_keepcost(mm_core::block_t b) {
        if(b->free)
            return b->size;
        
        return -1;
    }

    void get_values(struct mallinfo * info) {
        mm_core::block_t b = (mm_core::block_t) mm_core::base;
        info->ordblks = 0;
        info->uordblks = 0;
        info->fordblks = 0;
        info->keepcost = 0;
        while (b)
        {
            info->ordblks += get_ordblks(b);
            info->uordblks += get_uordblks(b);
            info->fordblks += get_fordblks(b);
            info->keepcost = get_keepcost(b) == -1? 0 : get_keepcost(b) + info->keepcost;
            b = b->next;
        }        
    }

    struct mallinfo mallinfo() {
        struct mallinfo info;

        get_values(&info);
        
        return info;
    }
}