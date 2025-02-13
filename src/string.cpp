#include "string.h"
#include "memory.h"
using namespace sulfate;

size_t sulfate::strlen(const char *s) {
    size_t len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

char *sulfate::strcpy(char *dest, const char *src) {
    const size_t len = strlen(src) + 1;
    memcpy(dest, src, len);
    return dest;
}

char *sulfate::strncpy(char *dest, const char *src, const size_t count) {
    if (const size_t len = strlen(src); len < count) {
        memcpy(dest, src, len + 1);
        memset(dest + len + 1, '\0', count - len - 1);
    } else {
        memcpy(dest, src, count);
    }

    return dest;
}

char *sulfate::strcat(char *dest, const char *src) {
    const size_t dest_len = strlen(dest);
    const size_t src_len = strlen(src) + 1;
    memcpy(dest + dest_len, src, src_len);
    return dest;
}

int sulfate::strcmp(const char *left, const char *right) {
    while (*left != '\0' && *left == *right) {
        ++left;
        ++right;
    }
    return static_cast<unsigned char>(*left) - static_cast<unsigned char>(*right);
}

char *sulfate::itoa(int value, char *str, const int base) {
    if (base < 2 || base > 36) {
        *str = '\0';
        return str;
    }

    char *p = str;
    bool isNegative = false;

    // 对于十进制，负数需要处理负号
    if (value < 0 && base == 10) {
        isNegative = true;
        value = -value;
    }

    do {
        const int remainder = value % base;
        // 根据余数判断是数字还是字母（支持 2~36 进制）
        *p++ = static_cast<char>(remainder < 10
                                     ? '0' + remainder
                                     : 'a' + remainder - 10);
        value /= base;
    } while (value);

    if (isNegative) {
        *p++ = '-';
    }
    *p = '\0';

    const size_t len = p - str;
    for (int i = 0; i < len / 2; i++) {
        const char tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }

    return str;
}

char *sulfate::ltoa(long long value, char *str, const int base) {
    if (base < 2 || base > 36) {
        *str = '\0';
        return str;
    }

    char *p = str;
    bool isNegative = false;

    // 对于十进制，负数需要处理负号
    if (value < 0 && base == 10) {
        isNegative = true;
        value = -value;
    }

    do {
        const long long remainder = value % base;
        // 根据余数判断是数字还是字母（支持 2~36 进制）
        *p++ = static_cast<char>(remainder < 10
                                     ? '0' + remainder
                                     : 'a' + remainder - 10);
        value /= base;
    } while (value);

    if (isNegative) {
        *p++ = '-';
    }
    *p = '\0';

    const size_t len = p - str;
    for (int i = 0; i < len / 2; i++) {
        const char tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }

    return str;
}
