#include "sulfate/io/iostream.h"
#include "sulfate/io/color.h"
#include "sulfate/io/font.h"
#include "string.h"
using namespace io;

namespace io {
    /// 帧缓冲区
    static uint32_t *vga_framebuffer;
    /// 屏幕大小
    static uint64_t screen_width, screen_height;
    /// 光标位置
    static uint64_t cursorX, cursorY;
}


void io::init_vga(uint32_t *FB, const uint64_t width, const uint64_t height) {
    vga_framebuffer = FB;
    screen_width = width;
    screen_height = height;
    cursorX = 0;
    cursorY = 0;
}

size_t io::getCursorX() {
    return cursorX;
}

size_t io::getCursorY() {
    return cursorY;
}

void io::print_char_on_screen(const uint64_t Xsize, const uint64_t x, const uint64_t y, const uint32_t FRcolor,
                              const uint32_t BKcolor,
                              const unsigned char *fontP) {
    int i = 0, j = 0;
    unsigned int *addr = nullptr;
    int testVal = 0;
    for (i = 0; i < 16; i++) {
        addr = vga_framebuffer + Xsize * (y + i) + x;
        testVal = 0x100;
        for (j = 0; j < 8; j++) {
            testVal = testVal >> 1;
            if (*fontP & testVal)
                *addr = FRcolor;
            else
                *addr = BKcolor;
            addr++;
        }
        fontP++;
    }
}

void io::putchar(const char c) {
    if (c == '\n') {
        cursorX = 0;
        cursorY += 16;
        return;
    }
    print_char_on_screen(screen_width, cursorX, cursorY, WHITE, BLACK, font_ascii[c]);
    cursorX += 8;
    if (cursorX >= screen_width) {
        cursorX = 0;
        cursorY += 16;
    }
}

void io::print(const char *fmt) {
    for (int i = 0; i < sulfate::strlen(fmt); i++) {
        if (fmt[i] == '{' && fmt[i + 1] == '}') {
            i+=1;
            continue;
        }
        putchar(fmt[i]);
    }
}