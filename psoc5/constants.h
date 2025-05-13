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

#ifndef CONSTANTS_H
#define CONSTANTS_H
    
#include "stdlib.h"

#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 240
#define BOARD_SIZE 4
#define CELL_SIZE 60
#define BORDER_WIDTH 2

#define TARGET_SQUARE 11
    
#define TOUCH_CUTOFF 4096
    
#define RANDOM_MOVE_DELAY 500
    
    
// #define USE_TOUCH
// #define USE_KEYPAD

static float randomFloat () { return (float) rand() / RAND_MAX; }    
    
#endif // CONSTANTS_H