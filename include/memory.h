#ifndef MEMORY_H
#define MEMORY_H

#include "stddef.h"

inline void memcpy(void* dest, const void* src, const size_t n) {
    __builtin_memcpy(dest, src, n);
}

inline void *memset(void *s, const int c, const size_t n) {
    return __builtin_memset(s, c, n);
}

#endif //MEMORY_H
