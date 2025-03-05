#include "sulfate/driver/tty.h"
using namespace sulfate;

void driver::TTYDevice::init(uint32_t *buffer, const size_t width, const size_t height) {
    this->buffer = buffer;
    this->width = width;
    this->height = height;
}
