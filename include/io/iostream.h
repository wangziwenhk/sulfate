#ifndef IOSTREAM_H
#define IOSTREAM_H

#include "stdint.h"

namespace io {
    /// 初始化 vga
    void init_vga(uint32_t *FB, uint64_t width, uint64_t height);

    /// 在屏幕上打印出一个字符
    void putchar(char c);

    /// 在屏幕上打印出字符串
    void print(const char *c);

    /// 在屏幕上打印出格式化的字符串
    void printf(const char *fmt, ...);

    /// 在屏幕上打印出
    void print_char_on_screen(uint64_t Xsize, uint64_t x, uint64_t y, uint32_t FRcolor, uint32_t BKcolor,
                           const unsigned char *fontP);
}

#endif //IOSTREAM_H
