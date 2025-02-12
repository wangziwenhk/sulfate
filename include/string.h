#ifndef STRING_H
#define STRING_H

#include "stddef.h"

namespace std {
    size_t strlen(const char *s);

    char *strcpy(char *dest, const char *src);

    char *strncpy(char *dest, const char *src, size_t count);

    char *strcat(char *dest, const char *src);

    int strcmp(const char *left, const char *right);

    char *itoa(int value, char *str, int base);
}

#endif //STRING_H
