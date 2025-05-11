// hello_sdl.c
#include <SDL2/SDL.h>
#include <stdio.h>

#include "display.h"
#include "constants.h"

int main() {
    if(displayInit()) return 1;

    color_t arr[DISPLAY_WIDTH * DISPLAY_HEIGHT];
    uint8_t color = 0;
    color_t BLACK_COLOR = 0, WHITE_COLOR = -1;
    for (int i = 0; i < DISPLAY_HEIGHT; i++) {
        if (i % 5 == 0) color = !color;
        for (int j = 0; j < DISPLAY_WIDTH; j++) {
            arr[i * DISPLAY_WIDTH + j] = (color ? BLACK_COLOR : WHITE_COLOR);
        }
    }
    displayBlitzRGB(arr, DISPLAY_WIDTH, DISPLAY_HEIGHT);

    uint8_t running = 1;
    while (running) {
        input_t inp = pollInput();
        printf("recvd input!!\n");
        if (inp == INPUT_QUIT) {
            printf("input was quit!\n");
            displayQuit();
            running = 0;
        }
    }


    

    return 0;
}
