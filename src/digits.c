#include "digits.h"
#include "constants.h"
#include "cells.h"
#include "stdio.h"

typedef struct {
    uint32_t bitmask;
    uint8_t width;
} digit_t;

const int MAX_DIGIT_WIDTH = 4;
const int DIGIT_HEIGHT = 7;

digit_t DIGIT_ZERO  = { .bitmask = 0b0110100110011001100110010110, .width = 4 };
digit_t DIGIT_ONE   = { .bitmask = 0b0001001100010001000100010001, .width = 2 };
digit_t DIGIT_TWO   = { .bitmask = 0b0110000100010010010001000111, .width = 3 };
digit_t DIGIT_THREE = { .bitmask = 0b0110000100010110000100010110, .width = 3 };
digit_t DIGIT_FOUR  = { .bitmask = 0b1000100010101010111100100010, .width = 4 };
digit_t DIGIT_FIVE  = { .bitmask = 0b0111010001000110000100010110, .width = 3 };
digit_t DIGIT_SIX   = { .bitmask = 0b0110100010001110100110010110, .width = 4 };
digit_t DIGIT_SEVEN = { .bitmask = 0b0111000100010010001001000100, .width = 3 };
digit_t DIGIT_EIGHT = { .bitmask = 0b0110100110010110100110010110, .width = 4 };
digit_t DIGIT_NINE  = { .bitmask = 0b0110100110010111000100010110, .width = 4 };

static digit_t getDigit(uint8_t digit) {
    if (digit == 1) return DIGIT_ONE;
    if (digit == 2) return DIGIT_TWO;
    if (digit == 3) return DIGIT_THREE;
    if (digit == 4) return DIGIT_FOUR;
    if (digit == 5) return DIGIT_FIVE;
    if (digit == 6) return DIGIT_SIX;
    if (digit == 7) return DIGIT_SEVEN;
    if (digit == 8) return DIGIT_EIGHT;
    if (digit == 9) return DIGIT_NINE;
    return DIGIT_ZERO;
}

static void setPixel(color_t* buf, int x, int y, color_t color) {
    if (0 <= x && 0 <= y && x < DISPLAY_WIDTH && y < DISPLAY_HEIGHT) {
        buf[y * DISPLAY_WIDTH + x] = color;
    }
}

void drawRect(color_t* buf, int x, int y, int dx, int dy, color_t color) {
    for (int j = y; j < y + dy; j++) {
        for (int i = x; i < x + dx; i++) {
            setPixel(buf, i, j, color);
        }
    }
}

void drawDigit(color_t* buf, digit_t digit, int x, int y, color_t color) {
    for (int j = 0; j < DIGIT_HEIGHT; j++) {
        for (int i = 0; i < digit.width; i++) {
            for (int jj = 0; jj < FONT_SCALE; jj++) {
                for (int ii = 0; ii < FONT_SCALE; ii++) {
                    if ((digit.bitmask >> (MAX_DIGIT_WIDTH * j + MAX_DIGIT_WIDTH - 1 - i)) & 1) {
                        setPixel(buf, x + i * FONT_SCALE + ii, y + j * FONT_SCALE + jj, color);
                    }
                }
            }
        }
    }
}

void drawNumber(color_t* buf, int num, int x, int y, int m) {
    digit_t digits[4];
    for (int i = 0; i < 4; i++) { digits[i] = getDigit(num % 10); num /= 10; }

    int total_height = DIGIT_HEIGHT * m;
    int total_width = 0;
    for (int i = 0; i < 4; i++) total_width += digits[i].width;
}


color_t* getCell(int number) {
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



void createBoard (color_t* buf, int* board) {
    // set background to black
    drawRect(buf, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, -1);
    drawRect(buf, (DISPLAY_WIDTH-DISPLAY_HEIGHT) / 2, 0, DISPLAY_HEIGHT, DISPLAY_HEIGHT, color565(143,122,102));

    for (int j = 0; j < BOARD_SIZE; j++) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            int val = board[BOARD_SIZE*j + i];
            printf("Val[%d][%d] = %d\n", i, j, val);
            copyCellBuffer(buf, board[BOARD_SIZE*j + i], i, j);
        }
    }

    // draw grid
    for (int i = 0; i <= BOARD_SIZE; i++) {
        drawRect(
            buf,
            (DISPLAY_WIDTH - DISPLAY_HEIGHT) / 2,
            i * DISPLAY_HEIGHT / BOARD_SIZE,
            DISPLAY_HEIGHT,
            BORDER_WIDTH,
            -1
        );
        drawRect(
            buf,
            (DISPLAY_WIDTH - DISPLAY_HEIGHT) / 2 + i * DISPLAY_HEIGHT / BOARD_SIZE,
            0,
            BORDER_WIDTH,
            DISPLAY_HEIGHT,
            -1
        );
    }

}