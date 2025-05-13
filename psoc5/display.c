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

#include "display.h"
#include "constants.h"
#include "tft.h"
#include "cells.h"

#define KEY_UP      0b1000
#define KEY_DOWN    0b1001
#define KEY_LEFT    0b1101
#define KEY_RIGHT   0b0101


#define KNOWN_LEFT  15
#define KNOWN_RIGHT 45
#define KNOWN_SIZE  30

const color_t* bg[] = { &BG_2, &BG_4, &BG_8, &BG_16, &BG_32, &BG_64, &BG_128, &BG_256, &BG_512, &BG_1024, &BG_2048 };
const color_t* cell[] = { CELL_2, CELL_4, CELL_8, CELL_16, CELL_32, CELL_64, CELL_128, CELL_256, CELL_512, CELL_1024, CELL_2048 };


/*****************
 * DISPLAY UTILS *
 *****************/

void setWritingBounds(uint16 x, uint16 y, uint16 dx, uint16 dy) {
    uint16 SC = x;
    uint16 SP = y;
    uint16 EC = x + dx - 1;
    uint16 EP = y + dy - 1;

    write8_a0(0x2A);                 	// send Column Address Set command
    write8_a1(SC >> 8);                  // set SC[15:0]
    write8_a1(SC & 0x00FF);
    write8_a1(EC >> 8);                 // set EC[15:0]
    write8_a1(EC & 0x00FF);
    write8_a0(0x2B);                 	// send Page Address Set command
    write8_a1(SP >> 8);                  // set SP[15:0]
    write8_a1(SP & 0x00FF);
    write8_a1(EP >> 8);                 // set EP[15:0]
    write8_a1(EP & 0x00FF);
}

void drawNumberedCell(uint16 px, uint16 py, uint16 idx) {
    const color_t* bg_ref = bg[idx];
    const color_t* cell_ref = cell[idx];
    
    setWritingBounds(
        DISPLAY_HEIGHT - (py + 1) * CELL_SIZE,
        (DISPLAY_WIDTH - DISPLAY_HEIGHT) / 2 + (px) * CELL_SIZE,
        CELL_SIZE, CELL_SIZE
    );

    write8_a0(0x2C);                    // send Memory Write command
    uint16 i, j;
    for (j = 0; j < CELL_SIZE; j++) {
        for (i = 0; i < CELL_SIZE; i++) {
            uint16 qx = j;
            uint16 qy = CELL_SIZE - 1 - i;
            color_t color = (
                (qx < KNOWN_LEFT || qx >= KNOWN_RIGHT || qy < KNOWN_LEFT || qy >= KNOWN_RIGHT) ?
                *bg_ref :
                cell_ref[qy * KNOWN_SIZE + qx - KNOWN_LEFT * KNOWN_SIZE - KNOWN_LEFT]
            );
            write8_a1(color >> 8);
            write8_a1(color & 0x00ff);
        }
    }
     write8_a0(0x00); 
};

void drawEmptyCell(uint16 px, uint16 py) {
    const color_t color = color565(143, 122, 102);
    
    setWritingBounds(
        DISPLAY_HEIGHT - (py + 1) * CELL_SIZE,
        (DISPLAY_WIDTH - DISPLAY_HEIGHT) / 2 + (px) * CELL_SIZE,
        CELL_SIZE, CELL_SIZE
    );
    
    write8_a0(0x2C);                    // send Memory Write command
    uint16 i;
    for (i = 0; i < CELL_SIZE * CELL_SIZE; i++) {
        write8_a1(color >> 8);
        write8_a1(color & 0x00ff);
    }
    write8_a0(0x00); 
}


void drawRect(uint16 y, uint16 x, uint16 dy, uint16 dx, color_t color) {
    setWritingBounds(x, y, dx, dy);

    write8_a0(0x2C);                    // send Memory Write command
    int i;
    for (i=0; i<(dx*dy); i++)           // fill the square with the color orange
	{
		write8_a1(color >> 8); 			// 0xFF0F is the color orange
		write8_a1(color & 0x00FF); 
	}
     write8_a0(0x00);                   // send NOP command to end writing process
}

/*******************
 * DISPLAY METHODS *
 *******************/

uint8 displayInit() {
    tftStart();                         // initialize the TFT display    
    drawRect(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, color565(250, 248, 240));
    return 0;
}


void drawBoard (uint16* board, uint16* oldBoard) {
    int i, j;
    for (j = 0; j < BOARD_SIZE; j++) {
        for (i = 0; i < BOARD_SIZE; i++) {
            uint16 val = board[j*BOARD_SIZE + i];
            uint16 oldVal = oldBoard[j*BOARD_SIZE + i];
            if (val == oldVal) continue;
            if (val > 0) drawNumberedCell(i, j, val-1);
            else drawEmptyCell(i, j);
        }
    }
}

/***************
 * INPUT UTILS *
 ***************/


input_t pollKeypadInput() {
    for(;;) {
        if (Data_Available_Read()) {
            if (Input_Data_Read() == KEY_UP) return INPUT_KEY_UP;
            if (Input_Data_Read() == KEY_DOWN) return INPUT_KEY_DOWN;
            if (Input_Data_Read() == KEY_LEFT) return INPUT_KEY_LEFT;
            if (Input_Data_Read() == KEY_RIGHT) return INPUT_KEY_RIGHT;
            return INPUT_KEY_UNKNOWN;
        }
    }
}

input_t pollTouchInput() {
    for (;;) {
        if (TouchScreen_TouchDetect()) {
            TouchScreen_ActivateX();
            uint16 x = TouchScreen_Measure();
            TouchScreen_ActivateY();
            uint16 y = TouchScreen_Measure();
            uint8 diag1 = (x > y);
            uint8 diag2 = ((x + y) > TOUCH_CUTOFF);
            if (diag1 && diag2) return INPUT_KEY_RIGHT;
            if (!diag1 && diag2) return INPUT_KEY_UP;
            if (diag1 && !diag2) return INPUT_KEY_DOWN;
            if (!diag1 && !diag2) return INPUT_KEY_LEFT;
        }
    }
}

input_t pollRandomInput() {
    float rand = randomFloat();
    CyDelay(RANDOM_MOVE_DELAY);
    if (rand < 0.25) return INPUT_KEY_UP;
    if (rand < 0.5) return INPUT_KEY_DOWN;
    if (rand < 0.75) return INPUT_KEY_LEFT;
    return INPUT_KEY_UP;
}

input_t pollInput() {
    #if defined(USE_TOUCH)
        return pollTouchInput();
    #elif defined(USE_KEYPAD)
        return pollKeypadInput();
    #else
        return pollRandomInput();
    #endif // USE_TOUCH
}

/***************
 * SOUND UTILS *
 ***************/

void playBeep(uint16 length) {
    Buzzer_Write(1);
    CyDelay(length);
    Buzzer_Write(0);
}

void playWinSound() {
    int i;
    for (i = 0; i < 10; i++) {
        playBeep(100);
        CyDelay(20);
    }
    playBeep(500);
}

void playIllegalMoveSound() {
    playBeep(1000);
}