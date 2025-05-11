#include "display.h"
#include "stdio.h"
#include "constants.h"

#include "SDL2/SDL.h"


SDL_Window *win; 
SDL_Renderer *ren;
SDL_Texture *tex;

SDL_Event event;

uint8_t displayInit() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    win = SDL_CreateWindow("Hello SDL2", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        DISPLAY_WIDTH, DISPLAY_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_SetWindowAlwaysOnTop(win, SDL_TRUE);
    printf("Display initialized!\n");
    return 0;
}


void displayBlitzRGB(color_t* buffer, uint8_t width, uint8_t height) {
    // Create the texture once
    if (tex == NULL) {
        tex = SDL_CreateTexture(ren,
            SDL_PIXELFORMAT_RGB565,    // Our buffer format (5-6-5)
            SDL_TEXTUREACCESS_STREAMING,
            width, height);

        if (!tex) {
            printf("SDL_CreateTexture Error: %s\n", SDL_GetError());
            return;
        }
    }

    void *pixels;
    int pitch = width;

    if (SDL_LockTexture(tex, NULL, &pixels, &pitch) != 0) {
        // Lock failed
        SDL_Log("SDL_LockTexture failed: %s", SDL_GetError());
        return;
    }

    // memcpy(pixels, buf, width*height);
    for (int i = 0; i < width * height; i++) {
        ((color_t*) pixels)[i] = buffer[i];
    }

    SDL_UnlockTexture(tex);

    // Clear the screen
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);

    // Copy texture to renderer and present
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);
}




void displayQuit() {
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}



input_t pollInput() {
    for (;;) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) return INPUT_QUIT;
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP) return INPUT_KEY_UP;
                if (event.key.keysym.sym == SDLK_DOWN) return INPUT_KEY_DOWN;
                if (event.key.keysym.sym == SDLK_RIGHT) return INPUT_KEY_RIGHT;
                if (event.key.keysym.sym == SDLK_LEFT) return INPUT_KEY_LEFT;
            }
        }
    }
}
