#include "game.h"
#include "constants.h"
#include "cells.h"

#include "stdio.h"
#include "stdlib.h"


/****************
 * GAME DISPLAY *
 ****************/

static void setPixel(color_t* buf, int x, int y, color_t color) {
    if (0 <= x && 0 <= y && x < DISPLAY_WIDTH && y < DISPLAY_HEIGHT) {
        buf[y * DISPLAY_WIDTH + x] = color;
    }
}

static color_t* getCell(int number) {
    if (number == 2) return CELL_2;
    if (number == 4) return CELL_4;
    if (number == 8) return CELL_8;
    if (number == 16) return CELL_16;
    if (number == 32) return CELL_32;
    if (number == 64) return CELL_64;
    if (number == 128) return CELL_128;
    if (number == 256) return CELL_256;
    if (number == 512) return CELL_512;
    if (number == 1024) return CELL_1024;
    if (number == 2048) return CELL_2048;
    return 0;
}


void copyCellBuffer(color_t* buf, int number, int px, int py) {
    color_t* cell = getCell(number);
    if (cell == 0) return;

    int x = (DISPLAY_WIDTH - DISPLAY_HEIGHT) / 2 + px * CELL_SIZE;
    int y = py * CELL_SIZE;

    for (int j = 0; j < CELL_SIZE; j++) {
        for (int i = 0; i < CELL_SIZE; i++) {
            buf[(y+j) * DISPLAY_WIDTH + (x+i)] = cell[j * CELL_SIZE + i];
        }
    }
}

void drawRect(color_t* buf, int x, int y, int dx, int dy, color_t color) {
    for (int j = y; j < y + dy; j++) {
        for (int i = x; i < x + dx; i++) {
            setPixel(buf, i, j, color);
        }
    }
}


void drawBoard (color_t* buf, int* board) {
    // set background to black
    drawRect(buf, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, -1);
    drawRect(buf, (DISPLAY_WIDTH-DISPLAY_HEIGHT) / 2, 0, DISPLAY_HEIGHT, DISPLAY_HEIGHT, color565(143,122,102));

    for (int j = 0; j < BOARD_SIZE; j++) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            copyCellBuffer(buf, board[BOARD_SIZE*j+i], i, j);
        }
    }

    // draw grid
    for (int i = 0; i <= BOARD_SIZE; i++) {
        drawRect(buf, (DISPLAY_WIDTH - DISPLAY_HEIGHT) / 2, i * DISPLAY_HEIGHT / BOARD_SIZE, DISPLAY_HEIGHT, BORDER_WIDTH, -1 );
        drawRect(buf, (DISPLAY_WIDTH - DISPLAY_HEIGHT) / 2 + i * DISPLAY_HEIGHT / BOARD_SIZE, 0, BORDER_WIDTH, DISPLAY_HEIGHT, -1);
    }

}


/******************
 * GAME MECHANICS *
 ******************/

 void rotate(int* board) {
    int tmp;
    for (int i = 0; i < BOARD_SIZE / 2; i++) {
        for (int j = 0; j < BOARD_SIZE / 2; j++) {
            printf("access: %d\n", BOARD_SIZE * j + i);
            tmp = board[BOARD_SIZE * j + i];
            board[BOARD_SIZE * j + i] = board[BOARD_SIZE * (BOARD_SIZE - i - 1) + j];
			board[BOARD_SIZE * (BOARD_SIZE - i - 1) + j] = board[BOARD_SIZE * (BOARD_SIZE - j - 1) + BOARD_SIZE - i - 1];
            board[BOARD_SIZE * (BOARD_SIZE - j - 1) + BOARD_SIZE - i - 1] = board[BOARD_SIZE * i + BOARD_SIZE - j - 1];
            board[BOARD_SIZE * i + BOARD_SIZE - j - 1] = tmp;
        }
    }
}


void slideArray(int* array, int* isMoved)
{
    printf("slideArray!\n");
    int p = 0; int q = 0;
    // everything up to p-1 is frozen
    // trying to move element at q;
    while (q < BOARD_SIZE) {
        if (array[q] == 0) { q++; }
        else if (p == q) { q++; }
        else if (array[p] == 0) { array[p] = array[q]; array[q] = 0; q++; *isMoved = 1; }
        else if (array[p] == array[q]) { array[p] *= 2; array[q] = 0; q++; p++; *isMoved = 1; }
        else { p++; }
    }
}

float randomFloat () {
    return (float) rand() / RAND_MAX;
}

void addRandomTile(int* board) {
    int numEmpty = 0;
    for (int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++) numEmpty += (board[i] == 0);
    int idx = randomFloat() * numEmpty;
    int count = 0;
    for (int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++) {
        if (board[i] != 0) continue;
        if (count == idx) {
            board[i] = (randomFloat() < 0.9) ? 2 : 4;
            return;
        }
        count++;
    }
}

void moveLeft(int* board) {
    int isMoved = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        slideArray(board + i*BOARD_SIZE, &isMoved);
    }
    if (isMoved) { addRandomTile(board); }
}

void moveUp(int* board) {
    rotate(board);
    rotate(board);
    rotate(board);
    moveLeft(board);
    rotate(board);
}
void moveRight(int* board) {
    rotate(board);
    rotate(board);
    moveLeft(board);
    rotate(board);
    rotate(board);
}

void moveDown(int* board) {
    rotate(board);
    moveLeft(board);
    rotate(board);
    rotate(board);
    rotate(board);
}