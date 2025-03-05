#pragma once

#include "stdint.h"
#include "stddef.h"

namespace std {
    inline void *memset(void *src, const int val, const size_t size) {
        return __builtin_memset(src, val, size);
    }

    inline void *memcpy(void *dest, const void *src, const size_t size) {
        return __builtin_memcpy(dest, src, size);
    }

    inline void *memmove(void *dest, const void *src, const size_t size) {
        return __builtin_memmove(dest,src,size);
    }
} // namespace std
