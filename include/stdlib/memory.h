#ifndef MEMORY_H
#define MEMORY_H

#include "stddef.h"

inline void memcpy(void *dest, const void *src, const size_t n) {
    __builtin_memcpy(dest, src, n);
}

inline void *memset(void *s, const int c, const size_t n) {
    return __builtin_memset(s, c, n);
}

inline void *memmove(void *dest, const void *src, const size_t n) {
    //如果你看到了报错，不用管，这是 llvm 的内建函数
    return __builtin_memmove(dest,src,n);
}

inline void *memchr(const void *s, const int c, const size_t n) {
    return __builtin_memchr(s,c,n);
}

inline int memcmp(const void *dest, const void *src, const size_t n) {
    return __builtin_memcmp(dest,src,n);
}

#endif //MEMORY_H
