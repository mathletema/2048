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

#ifndef GAME_H
#define GAME_H

#include "project.h"

void addRandomTile(uint16* board);
void moveLeft(uint16* board, uint16* newBoard);
void moveUp(uint16* board, uint16* newBoard);
void moveRight(uint16* board, uint16* newBoard);
void moveDown(uint16* board, uint16* newBoard);

uint8 gameWon(uint16* board);
uint8 boardUnchanged(uint16* board, uint16* oldBoard);


#endif // GAME_H