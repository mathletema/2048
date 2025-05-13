// hello_sdl.c
#include <SDL2/SDL.h>
#include <stdio.h>

#include "display.h"
#include "constants.h"
#include "game.h"

int main() {
    if(displayInit()) return 1;

    color_t arr[DISPLAY_WIDTH * DISPLAY_HEIGHT];

    int board[] = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };
    addRandomTile(board);
    addRandomTile(board);
    

    uint8_t running = 1;
    while (running) {
        drawBoard(arr, board);
        displayBlitzRGB(arr);

        input_t inp = pollInput();
        if (inp == INPUT_QUIT) {
            displayQuit();
            running = 0;
        } else if (inp == INPUT_KEY_UP) moveUp(board);
        else if (inp == INPUT_KEY_DOWN) moveDown(board);
        else if (inp == INPUT_KEY_LEFT) moveLeft(board);
        else if (inp == INPUT_KEY_RIGHT) moveRight(board);

        drawBoard(arr, board);
        displayBlitzRGB(arr);
    }

    return 0;
}
