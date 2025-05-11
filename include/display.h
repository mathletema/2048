#ifndef DISPLAY_H
#define DISPLAY_H

#include "constants.h"
#include "color.h"


uint8_t displayInit();
void displayBlitzRGB(color_t* buffer, uint8_t width, uint8_t height);
void displayQuit();

#endif // DISPLAY_H