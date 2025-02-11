#ifndef IOSTREAM_H
#define IOSTREAM_H

#include "string.h"
#include "stdint.h"
#include "type_traits.h"

namespace io {
    /// 初始化 vga
    void init_vga(uint32_t *FB, uint64_t width, uint64_t height);

    /// 在屏幕上打印出一个字符
    void putchar(char c);

    /// 在屏幕上打印出字符串
    void print(const char *c);

    /// 在屏幕上打印出
    void print_char_on_screen(uint64_t Xsize, uint64_t x, uint64_t y, uint32_t FRcolor, uint32_t BKcolor,
                              const unsigned char *fontP);

    /// 在屏幕上打印出格式化的字符串
    inline void printf(const char *fmt) {
        for (int i = 0; fmt[i] != '\0'; i++) {
            if (fmt[i] == '%') {
                putchar(fmt[i + 1]);
                i += 2;
            } else {
                putchar(fmt[i]);
            }
        }
    }

    template<typename T, typename... Args>
    void printf(const char *format, T value, Args... args) {
        while (*format) {
            if (*format == '%' && *(format + 1) == '%') {
                putchar('%');
                format += 2;
            } else if (*format == '{' && *(format + 1) == '}') {
                if constexpr (std::is_same_v<T, const char *>) {
                    print(value);
                } else if constexpr (std::is_same_v<T, int>) {
                    char buf[10];
                    print(std::itoa(value, buf, 10));
                }
                format++;
                printf(format + 1, args...);
                return;
            } else {
                putchar(*format);
                ++format;
            }
        }
    }
}

#endif //IOSTREAM_H
