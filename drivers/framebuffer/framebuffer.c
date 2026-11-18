#include <stdint.h>
#include <limine.h>

#include "framebuffer/framebuffer.h"

static struct limine_framebuffer *active_fb = 0;

static uint32_t pack_channel(
    uint8_t value,
    uint8_t mask_size,
    uint8_t mask_shift
)
{
    if (mask_size == 0)
        return 0;

    uint32_t maximum = (1U << mask_size) - 1U;

    uint32_t scaled =
        ((uint32_t)value * maximum + 127U) / 255U;

    return scaled << mask_shift;
}

static uint32_t pack_color(
    uint8_t r,
    uint8_t g,
    uint8_t b
)
{
    return
        pack_channel(r, active_fb->red_mask_size,
                        active_fb->red_mask_shift) |
        pack_channel(g, active_fb->green_mask_size,
                        active_fb->green_mask_shift) |
        pack_channel(b, active_fb->blue_mask_size,
                        active_fb->blue_mask_shift);
}

int framebuffer_init(struct limine_framebuffer *fb)
{
    if (fb == 0 || fb->address == 0)
        return 0;

    if (fb->memory_model != LIMINE_FRAMEBUFFER_RGB)
        return 0;

    if (fb->bpp != 32)
        return 0;

    if (fb->width == 0 || fb->height == 0)
        return 0;

    if (fb->width > UINT64_MAX / 4 ||
        fb->pitch < fb->width * 4)
        return 0;

    if (fb->red_mask_size == 0 ||
        fb->green_mask_size == 0 ||
        fb->blue_mask_size == 0 ||
        fb->red_mask_size > 8 ||
        fb->green_mask_size > 8 ||
        fb->blue_mask_size > 8 ||
        fb->red_mask_shift + fb->red_mask_size > 32 ||
        fb->green_mask_shift + fb->green_mask_size > 32 ||
        fb->blue_mask_shift + fb->blue_mask_size > 32)
    {
        return 0;
    }

    active_fb = fb;

    return 1;
}

static void put_pixel(
    uint64_t x,
    uint64_t y,
    uint8_t r,
    uint8_t g,
    uint8_t b
)
{
    if (active_fb == 0)
        return;

    if (x >= active_fb->width || y >= active_fb->height)
        return;

    volatile uint32_t *pixel =
        (volatile uint32_t *)(
            (volatile uint8_t *)active_fb->address +
            y * active_fb->pitch +
            x * 4
        );

    *pixel = pack_color(r, g, b);
}

void framebuffer_clear(uint8_t r, uint8_t g, uint8_t b)
{
    if (active_fb == 0)
        return;

    for (uint64_t y = 0; y < active_fb->height; y++)
    {
        for (uint64_t x = 0; x < active_fb->width; x++)
        {
            put_pixel(x, y, r, g, b);
        }
    }
}

void framebuffer_draw_rect(
    uint64_t x,
    uint64_t y,
    uint64_t width,
    uint64_t height,
    uint8_t r,
    uint8_t g,
    uint8_t b
)
{
    if (active_fb == 0)
        return;

    if (x >= active_fb->width || y >= active_fb->height)
        return;

    if (width > active_fb->width - x)
        width = active_fb->width - x;

    if (height > active_fb->height - y)
        height = active_fb->height - y;

    for (uint64_t row = 0; row < height; row++)
    {
        for (uint64_t col = 0; col < width; col++)
        {
            put_pixel(x + col, y + row, r, g, b);
        }
    }
}
