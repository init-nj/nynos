
#ifndef NYNOS_TEXT_H
#define NYNOS_TEXT_H

#include <stdint.h>

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
);

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
);

#endif
