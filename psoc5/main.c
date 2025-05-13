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
#include <project.h>
#include "tft.h"
#include "display.h"
#include "constants.h"
#include "game.h"
#include "stdlib.h"
#include "time.h"

#define swapBoards tmp = board; board = scratchBoard; scratchBoard = tmp

uint16 board1[16] = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
};

uint16 board2[16] = {
    -1, -1, -1, -1,
    -1, -1, -1, -1,
    -1, -1, -1, -1,
    -1, -1, -1, -1
};

int main()
{
    srand(time(NULL));
    CyGlobalIntEnable;                  // Enable global interrupts
    SPIM_1_Start();                     // initialize SPIM component
    TouchScreen_Start();
    
    uint16* board = board1; uint16* scratchBoard = board2; uint16* tmp;
    
    addRandomTile(board);
    addRandomTile(board);  
    
    displayInit();
    drawBoard(board, scratchBoard);
    
    uint8 running = 1;

    while (running) {        
        input_t input = pollInput();
        if (input == INPUT_KEY_UNKNOWN) continue;
        
        if (input == INPUT_KEY_UP) { moveUp(board, scratchBoard); swapBoards; }
        if (input == INPUT_KEY_DOWN) { moveDown(board, scratchBoard); swapBoards; }
        if (input == INPUT_KEY_LEFT) { moveLeft(board, scratchBoard); swapBoards; }
        if (input == INPUT_KEY_RIGHT) { moveRight(board, scratchBoard); swapBoards; }

        drawBoard(board, scratchBoard);
        
        if (boardUnchanged(board, scratchBoard)) {
            playIllegalMoveSound();
        }
        
        if (gameWon(board)) {
            playWinSound();
            running = 0;
        }
        
        CyDelay(30);
    }
    
    for (;;) {};

}

/* [] END OF FILE */

