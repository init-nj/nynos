#ifndef NYNOS_FRAMEBUFFER_H
#define NYNOS_FRAMEBUFFER_H

#include <limine.h>
#include <stdint.h>

int framebuffer_init(struct limine_framebuffer *fb);

void framebuffer_clear(uint8_t r, uint8_t g, uint8_t b);

void framebuffer_draw_rect(
    uint64_t x,
    uint64_t y,
    uint64_t width,
    uint64_t height,
    uint8_t r,
    uint8_t g,
    uint8_t b
);

#endif
