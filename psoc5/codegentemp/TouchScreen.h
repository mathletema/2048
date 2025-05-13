/*******************************************************************************
* File Name: TouchScreen.h
* Version 2.0
*
* Description:
*  This file provides the constants and parameter values for the ResistiveTouch
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_RESISTIVE_TOUCH_TouchScreen_H)
#define CY_RESISTIVE_TOUCH_TouchScreen_H

#include "cytypes.h"
#include "TouchScreen_ADC.h"
#include "TouchScreen_AMux.h"


/***************************************
*        Function Prototypes
****************************************/

void TouchScreen_Start(void) ;
void TouchScreen_Stop(void) ;
void TouchScreen_Init(void) ; 
void TouchScreen_Enable(void) ;
void TouchScreen_ActivateX(void) ;
void TouchScreen_ActivateY(void);
int16 TouchScreen_Measure(void) ;
uint8 TouchScreen_TouchDetect(void) ;

void TouchScreen_SaveConfig(void) ;
void TouchScreen_RestoreConfig(void) ;
void TouchScreen_Sleep(void) ; 
void TouchScreen_Wakeup(void) ; 

/* Macros for emWinGraphics Library */
#define CYTOUCH_START()         TouchScreen_Start() 
#define CYTOUCH_STOP()          TouchScreen_Stop()
#define CYTOUCH_MEASURE()       TouchScreen_Measure()
#define CYTOUCH_ACTIVATE_X()    TouchScreen_ActivateX()
#define CYTOUCH_ACTIVATE_Y()    TouchScreen_ActivateY()
#define CYTOUCH_TOUCHED()       TouchScreen_TouchDetect()


/***************************************
*   Variable with external linkage
***************************************/

extern uint8 TouchScreen_initVar;


/***************************************
*       Constants
***************************************/

/* AMUX channel definitions */
#define TouchScreen_AMUX_XP_CHAN   (0)
#define TouchScreen_AMUX_YP_CHAN   (1)
#define TouchScreen_AMUX_NO_CHAN   (-1)

/* The screen is touched if the measured value is lower than the specified
* threshold.
*/
#define TouchScreen_TOUCH_THRESHOLD        (0x778)


#endif /* CY_RESIST_TOUCH_TouchScreen_H */


/* [] END OF FILE */
