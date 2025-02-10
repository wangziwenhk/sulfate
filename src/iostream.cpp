#include "io/iostream.h"
#include "io/color.h"
#include "stdarg.h"
using namespace io;

/// 帧缓冲区
static uint32_t *framebuffer;

void io::init(uint32_t *FB) {
    framebuffer = FB;
}

void printCharToScreen(const int Xsize, const int x, const int y, const uint32_t FRcolor, const uint32_t BKcolor, const unsigned char font) {
    int i = 0,j = 0;
    unsigned int * addr = nullptr;
    const unsigned char * fontP = nullptr;
    int testVal = 0;
    fontP = font_ascii[font];

    for(i = 0; i< 16;i++)
    {
        addr = framebuffer + Xsize * ( y + i ) + x;
        testVal = 0x100;
        for(j = 0;j < 8;j ++)
        {
            testVal = testVal >> 1;
            if(*fontP & testVal)
                *addr = FRcolor;
            else
                *addr = BKcolor;
            addr++;
        }
        fontP++;
    }
}

void io::putchar(const char c) {
    printCharToScreen(16,0,0,BLACK,WHITE,c);
}
