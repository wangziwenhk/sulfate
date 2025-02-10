#include "stdint.h"
#include <limine.h>
#include "string.h"
#include "io/iostream.h"

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

bool check();

extern "C"
[[noreturn]]
void _start() {
    // NOLINT(*-reserved-identifier)
    // 如果 limine 版本过低
    if (!check()) {
        while (true) __asm__ ("hlt");
    }

    limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    uint64_t width = framebuffer->width;
    uint64_t height = framebuffer->height;

    auto *buffer = static_cast<uint32_t *>(framebuffer->address);

    io::init(buffer);

    while (true) __asm__ ("hlt");
}

// 检查相关数据点是否正常
bool check() {
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        return false;
    }

    if (framebuffer_request.response == nullptr
        || framebuffer_request.response->framebuffer_count < 1) {
        return false;
    }
    return true;
}
