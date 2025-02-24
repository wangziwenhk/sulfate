#pragma once
#include <stddef.h>
#include <stdint.h>
#include "sulfate/driver/pci.h"

namespace sulfate::driver {
    class TTYDevice {
    public:
        explicit TTYDevice(const size_t buffer_size) : bufferSize(buffer_size) {}

        void init(uint32_t *buffer, size_t width, size_t height);

    private:
        size_t bufferSize = 0;
    };
} // namespace sulfate::driver
