
#include <stdint.h>

#include "graphics/font.h"
#include "graphics/text.h"
#include "framebuffer/framebuffer.h"

#define CHARACTER_SPACING 1

void text_draw_char(
    uint64_t x,
    uint64_t y,
    char c,
    uint8_t fg_r,
    uint8_t fg_g,
    uint8_t fg_b,
    uint8_t bg_r,
    uint8_t bg_g,
    uint8_t bg_b,
    uint8_t scale
)
{
    if (scale == 0)
        return;

    const uint8_t *glyph = font_get_glyph(c);

    /*
     * Draw the character background.
     * Each character occupies a 6x8 cell:
     * 5x7 glyph + spacing.
     */
    framebuffer_draw_rect(
        x, y,
        (FONT_WIDTH + CHARACTER_SPACING) * scale,
        (FONT_HEIGHT + 1) * scale,
        bg_r, bg_g, bg_b
    );

    for (uint8_t row = 0; row < FONT_HEIGHT; row++)
    {
        for (uint8_t col = 0; col < FONT_WIDTH; col++)
        {
            uint8_t mask = 1U << (FONT_WIDTH - 1 - col);

            if (glyph[row] & mask)
            {
                framebuffer_draw_rect(
                    x + col * scale,
                    y + row * scale,
                    scale,
                    scale,
                    fg_r, fg_g, fg_b
                );
            }
        }
    }
}

void text_draw_string(
    uint64_t x,
    uint64_t y,
    const char *string,
    uint8_t fg_r,
    uint8_t fg_g,
    uint8_t fg_b,
    uint8_t bg_r,
    uint8_t bg_g,
    uint8_t bg_b,
    uint8_t scale
)
{
    if (string == 0 || scale == 0)
        return;

    uint64_t cursor_x = x;

    while (*string)
    {
        if (*string == '\n')
        {
            cursor_x = x;
            y += (FONT_HEIGHT + 1) * scale;
            string++;
            continue;
        }

        text_draw_char(
            cursor_x, y, *string,
            fg_r, fg_g, fg_b,
            bg_r, bg_g, bg_b,
            scale
        );

        cursor_x += (FONT_WIDTH + CHARACTER_SPACING) * scale;
        string++;
    }
}
