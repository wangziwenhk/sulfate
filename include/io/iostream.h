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
    void print(const char *fmt);

    /// 在屏幕上打印出
    void print_char_on_screen(uint64_t Xsize, uint64_t x, uint64_t y, uint32_t FRcolor, uint32_t BKcolor,
                              const unsigned char *fontP);

    /// 在屏幕上打印出格式化的字符串
    ///
    /// 下面是一个示例
    /// @code
    /// print("hello {}! {}","world",233);
    /// @endcode
    template<typename T, typename... Args>
    void print(const char *format, T&& value, Args&&... args) {
        using BaseType = std::decay_t<T>;
        while (*format) {
            if (*format == '{' && *(format + 1) == '}') {
                if constexpr (std::is_same_v<BaseType, char *> || std::is_same_v<BaseType,const char *>) {
                    print(value);
                } else if constexpr (std::is_same_v<BaseType, int>) {
                    char buf[12];
                    print(std::itoa(value, buf, 10));
                } else if constexpr (std::is_same_v<BaseType, long long>) {
                    char buf[24];
                    print(std::ltoa(value, buf, 10));
                }
                format++;
                print(format + 1, args...);
                return;
            } else {
                putchar(*format);
                ++format;
            }
        }
    }
}

#endif //IOSTREAM_H
