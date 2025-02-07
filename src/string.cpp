#include "string.h"
#include "memory.h"

char* strncpy(char *dest, const char *src, const size_t count) {
    size_t len = 0;
    while (len < count && src[len] != '\0') {
        len++;
    }
    memcpy(dest, src, len);
    if (len < count) {
        memset(dest + len, '\0', count - len);
    }

    return dest;
}

char* strcat(char *dest, const char *src) {
    char *ret = dest;
    while (*dest != '\0') {
        dest++;
    }
    while (*src != '\0') {
        *dest++ = *src++;
    }
    *dest = '\0';
    return ret;
}

constexpr char *inline_strcpy(char *dest, const char *src) {
    memcpy(dest, src, strlen(src));
    return dest;
}

char *strcpy(char *dest, const char *src) {
    return inline_strcpy(dest, src);
}

template<typename Comp>
constexpr int inline_strcmp(const char *left, const char *right,
                            Comp &&comp) {
    for (; *left && !(*left - *right); ++left, ++right){}
    return comp(*reinterpret_cast<const unsigned char *>(left),
                *reinterpret_cast<const unsigned char *>(right));
}

int strcmp(const char *left, const char *right) {
    auto comp = [](const char l, const char r) -> int { return l - r; };
    return inline_strcmp(left, right, comp);
}
