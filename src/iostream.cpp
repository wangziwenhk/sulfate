#include "io/iostream.h"
#include "stdarg.h"
using namespace io;

/// 帧缓冲区
static uint32_t *framebuffer;

void io::init(uint32_t *FB) {
    framebuffer = FB;
}

void io::putchar(char c) {
}
