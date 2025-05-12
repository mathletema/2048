#ifndef COLOR_H
#define COLOR_H

#include "stdint.h"

typedef uint16_t color_t;

static color_t color565(uint8_t red, uint8_t green, uint8_t blue) {
    return ((red & 0xF8) << 8) | ((green & 0xFC) << 3) | (blue >> 3);
}

extern const color_t COLOR_BG;
extern const color_t COLOR_FG;
extern const color_t COLOR_GRID;
extern const color_t COLOR_ONE;
extern const color_t COLOR_TWO;
extern const color_t COLOR_THREE;
extern const color_t COLOR_FOUR;
extern const color_t COLOR_FIVE;
extern const color_t COLOR_SIX;
extern const color_t COLOR_SEVEN;
extern const color_t COLOR_EIGHT;
extern const color_t COLOR_NINE;
extern const color_t COLOR_TEN;
extern const color_t COLOR_ELEVEN;

#endif // COLOR_H