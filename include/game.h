#ifndef GAME_H
#define GAME_H

#include "color.h"

void rotate(int* board);

void moveUp(int* board);
void moveDown(int* board);
void moveLeft(int* board);
void moveRight(int* board);

uint8_t isSolved(int* board);
uint8_t isUnsolvable(int* board);
void addRandomTile(int* board);
void drawBoard(color_t* buf, int* board);

#endif // GAME_H