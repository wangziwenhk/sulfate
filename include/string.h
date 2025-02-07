#ifndef STRING_H
#define STRING_H

#include "stddef.h"

constexpr size_t strlen(const char *s) {
    return __builtin_strlen(s);
}

char* strcpy(const char *dest, const char *src);

char* strncpy(char *dest, const char *src, size_t count);

char* strcat(const char *dest, const char *src);

int strcmp(const char *left, const char *right);

#endif //STRING_H
