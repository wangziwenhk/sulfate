#include "string.h"
#include "memory.h"
using namespace std;

size_t std::strlen(const char *s) {
    size_t len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

char *std::strcpy(char *dest, const char *src) {
    const size_t len = strlen(src) + 1;
    memcpy(dest, src, len);
    return dest;
}

char *std::strncpy(char *dest, const char *src, const size_t count) {
    if (const size_t len = std::strlen(src); len < count) {
        std::memcpy(dest, src, len + 1);
        std::memset(dest + len + 1, '\0', count - len - 1);
    } else {
        std::memcpy(dest, src, count);
    }

    return dest;
}

char *std::strcat(char *dest, const char *src) {
    const size_t dest_len = std::strlen(dest);
    const size_t src_len = std::strlen(src) + 1;
    std::memcpy(dest + dest_len, src, src_len);
    return dest;
}

int std::strcmp(const char *left, const char *right) {
    while (*left != '\0' && *left == *right) {
        ++left;
        ++right;
    }
    return static_cast<unsigned char>(*left) - static_cast<unsigned char>(*right);
}

char *std::itoa(int value, char *str, const int base) {
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
