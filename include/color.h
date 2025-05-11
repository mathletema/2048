#ifndef COLOR_H
#define COLOR_H

#include "stdint.h"

typedef uint16_t color_t;

static color_t color565(uint8_t red, uint8_t green, uint8_t blue) {
    return ((red & 0xF8) << 8) | ((green & 0xFC) << 3) | (blue >> 3);
}
#endif // COLOR_H