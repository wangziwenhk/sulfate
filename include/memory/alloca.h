#ifndef ALLOCA_H
#define ALLOCA_H

#include "stddef.h"

namespace kernel {
    void* kalloc(size_t size);
    void kfree(void* ptr);
    void heap_init();
}

#endif //ALLOCA_H
