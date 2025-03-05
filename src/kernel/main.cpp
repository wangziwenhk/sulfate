#include <limine.h>
#include "stddef.h"
#include "sulfate/driver/tty.h"
#include "sulfate/memory/kalloc.h"

#pragma region limine
// clang-format off
__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3)

__attribute__((used, section(".limine_requests")))
static volatile limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER

__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER

#pragma endregion

void check() {

}
// clang-format on

extern "C" [[noreturn]] void kmain(void) {

    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        while (true)
            __asm__("hlt");
    }

    if (framebuffer_request.response == nullptr || framebuffer_request.response->framebuffer_count < 1) {
        while (true)
            __asm__("hlt");
    }

    limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    uint64_t width = framebuffer->width;
    uint64_t height = framebuffer->height;

    uint64_t stride = framebuffer->pitch / 4;
    auto buffer = static_cast<uint32_t *>(framebuffer->address);

    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            buffer[y * stride + x] = (x * 255 / width) << 16 | (y * 255 / height) << 8;
        }
    }

    sulfate::pci::read_pci_config_word(1,1,1,0);

    while (true)
        __asm__("hlt");
}
