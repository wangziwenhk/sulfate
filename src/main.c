#include "stdint.h"
#include "stddef.h"
#include <limine.h>
#include "stdbool.h"
#include "font.h"
#include "printk.h"

__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3)

__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER

__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER

bool check(void);

void _start(void) { // NOLINT(*-reserved-identifier)
    // 如果 limine 版本过低
    if (!check()) {
        for (;;) __asm__ ("hlt");
    }

    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    uint64_t width = framebuffer->width;
    uint64_t height = framebuffer->height;

    uint32_t *buffer = framebuffer->address;

    Pos.XResolution = width;
    Pos.YResolution = height;
    Pos.XPosition = 0;
    Pos.YPosition = 0;
    Pos.XCharSize = 8;
    Pos.YCharSize = 16;

    Pos.FB_addr = buffer;
    Pos.FB_length = framebuffer->pitch * height * width;

    color_printk(YELLOW,BLACK, "System initialized, CPU speed: %dMHz\n", 2400);

    for (;;) __asm__ ("hlt");
}

// 检查相关数据点是否正常
bool check(void) {
    if (LIMINE_BASE_REVISION_SUPPORTED == false) {
        return false;
    }

    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        return false;
     }
    return true;
}
