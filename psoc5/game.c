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

#include "project.h"
#include "constants.h"
#include "stdlib.h"

/********************
 * HELPER FUNCTIONS *
 ********************/

void rotate(uint16* board) {
    int tmp;
    for (int i = 0; i < BOARD_SIZE / 2; i++) {
        for (int j = 0; j < BOARD_SIZE / 2; j++) {
            tmp = board[BOARD_SIZE * j + i];
            board[BOARD_SIZE * j + i] = board[BOARD_SIZE * (BOARD_SIZE - i - 1) + j];
			board[BOARD_SIZE * (BOARD_SIZE - i - 1) + j] = board[BOARD_SIZE * (BOARD_SIZE - j - 1) + BOARD_SIZE - i - 1];
            board[BOARD_SIZE * (BOARD_SIZE - j - 1) + BOARD_SIZE - i - 1] = board[BOARD_SIZE * i + BOARD_SIZE - j - 1];
            board[BOARD_SIZE * i + BOARD_SIZE - j - 1] = tmp;
        }
    }
}

void addRandomTile(uint16* board) {
    int numEmpty = 0;
    for (int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++) numEmpty += (board[i] == 0);
    int idx = randomFloat() * numEmpty;
    int count = 0;
    for (int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++) {
        if (board[i] != 0) continue;
        if (count == idx) {
            board[i] = (randomFloat() < 0.9) ? 1 : 2;
            return;
        }
        count++;
    }
}

/******************
 * MOVEMENT LOGIC *
 ******************/

void slideArray(uint16* array, int* isMoved)
{
    int p = 0; int q = 0;
    // everything up to p-1 is frozen
    // trying to move element at q;
    while (q < BOARD_SIZE) {
        if (array[q] == 0) { q++; }
        else if (p == q) { q++; }
        else if (array[p] == 0) { array[p] = array[q]; array[q] = 0; q++; *isMoved = 1; }
        else if (array[p] == array[q]) { array[p] += 1; array[q] = 0; q++; p++; *isMoved = 1; }
        else { p++; }
    }
}

void moveLeftInplace(uint16* board) {
    int isMoved = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        slideArray(board + i*BOARD_SIZE, &isMoved);
    }
    if (isMoved) { addRandomTile(board); }
}

void moveLeft(uint16* board, uint16* newBoard) {
    memcpy(newBoard, board, sizeof(uint16) * BOARD_SIZE * BOARD_SIZE);
    moveLeftInplace(newBoard);
}

void moveUp(uint16* board, uint16* newBoard) {
    memcpy(newBoard, board, sizeof(uint16) * BOARD_SIZE * BOARD_SIZE);
    rotate(newBoard);
    rotate(newBoard);
    rotate(newBoard);
    moveLeftInplace(newBoard);
    rotate(newBoard);
}
void moveRight(uint16* board, uint16* newBoard) {
    memcpy(newBoard, board, sizeof(uint16) * BOARD_SIZE * BOARD_SIZE);
    rotate(newBoard);
    rotate(newBoard);
    moveLeftInplace(newBoard);
    rotate(newBoard);
    rotate(newBoard);
}

void moveDown(uint16* board, uint16* newBoard) {
    memcpy(newBoard, board, sizeof(uint16) * BOARD_SIZE * BOARD_SIZE);
    rotate(newBoard);
    moveLeftInplace(newBoard);
    rotate(newBoard);
    rotate(newBoard);
    rotate(newBoard);
}

/************************
 * GAME TERMINATE LOGIC *
 ************************/

uint8 gameWon(uint16* board) {
    uint16 i;
    for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        if (board[i] >= TARGET_SQUARE) return 1;
    }
    return 0;
}

uint8 boardUnchanged(uint16* board, uint16* oldBoard) {
    uint16 i;
    for (i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        if (board[i] != oldBoard[i]) return 0;
    }
    return 1;
}