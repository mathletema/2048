#ifndef DISPLAY_H
#define DISPLAY_H

#include "constants.h"
#include "color.h"


uint8_t displayInit();
void displayBlitzRGB(color_t* buffer, uint8_t width, uint8_t height);
void displayQuit();

typedef enum { INPUT_KEY_UP, INPUT_KEY_DOWN, INPUT_KEY_LEFT, INPUT_KEY_RIGHT, INPUT_QUIT } input_t;
input_t pollInput();

#endif // DISPLAY_H