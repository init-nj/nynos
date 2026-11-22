
#ifndef NYNOS_FONT_H
#define NYNOS_FONT_H

#include <stdint.h>

#define FONT_WIDTH  5
#define FONT_HEIGHT 7

/*
 * Returns a pointer to seven rows of bitmap data.
 * Each row uses its lowest five bits for the glyph.
 */
const uint8_t *font_get_glyph(char c);

#endif
