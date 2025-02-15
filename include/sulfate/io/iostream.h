#ifndef IOSTREAM_H
#define IOSTREAM_H

#include "string.h"
#include "stdint.h"
#include "type_traits.h"

namespace io {
    /// 初始化 vga
    void init_vga(uint32_t *FB, uint64_t width, uint64_t height);

    size_t getCursorX();
    size_t getCursorY();

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
    void print(const char *format, T &&value, Args &&... args) {
        using BaseType = sulfate::decay_t<T>;
        const size_t length = sulfate::strlen(format);
        for (size_t i = 0; i < length; i++) {
            if (format[i] == '{' && length - i - 1 >= 2 && format[i + 1] == '}') {
                if constexpr (sulfate::is_same_v<BaseType, char *> || sulfate::is_same_v<BaseType, const char *>) {
                    print(value);
                } else if constexpr (sulfate::is_same_v<BaseType, int>) {
                    char buf[12];
                    print(sulfate::itoa(value, buf, 10));
                } else if constexpr (sulfate::is_same_v<BaseType, long long>) {
                    char buf[24];
                    print(sulfate::ltoa(value, buf, 10));
                }
                i++;
                print(format + i + 1, args...);
                return;
            }
            putchar(format[i]);
        }
    }
}

#endif //IOSTREAM_H
