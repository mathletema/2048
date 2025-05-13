/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "project.h"

typedef uint16 color_t;

static color_t color565(uint8 red, uint8 green, uint8 blue) {
    return ((red & 0xF8) << 8) | ((green & 0xFC) << 3) | (blue >> 3);
}

uint8 displayInit();
void displayBlitzRGB(color_t* buffer);
void displayQuit();

void drawBoard (uint16* board, uint16* oldBoard);

typedef enum { INPUT_KEY_UP, INPUT_KEY_DOWN, INPUT_KEY_LEFT, INPUT_KEY_RIGHT, INPUT_KEY_UNKNOWN, INPUT_QUIT } input_t;
input_t pollInput();

void playWinSound();
void playIllegalMoveSound();

#endif //DISPLAY_H