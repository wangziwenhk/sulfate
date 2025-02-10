#ifndef STRING_H
#define STRING_H

#include "stddef.h"

constexpr size_t strlen(const char *s) {
    return __builtin_strlen(s);
}

inline char *strcpy(char *dest, const char *src) {
    return __builtin_strcpy(dest,src);
}

inline char *strncpy(char *dest, const char *src, size_t count) {
    return __builtin_strncpy(dest, src, count);
}

inline char *strcat(char *dest, const char *src) {
    return __builtin_strcat(dest, src);
}

inline int strcmp(const char *left, const char *right) {
    return __builtin_strcmp(left,right);
}

#endif //STRING_H
