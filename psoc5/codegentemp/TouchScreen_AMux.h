/*******************************************************************************
* File Name: TouchScreen_AMux.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the AMuxSeq.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUXSEQ_TouchScreen_AMux_H)
#define CY_AMUXSEQ_TouchScreen_AMux_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define TouchScreen_AMux_MUX_SINGLE 1
#define TouchScreen_AMux_MUX_DIFF   2
#define TouchScreen_AMux_MUXTYPE    1


/***************************************
*        Function Prototypes
***************************************/

void TouchScreen_AMux_Start(void);
void TouchScreen_AMux_Init(void);
void TouchScreen_AMux_Stop(void);
#if (TouchScreen_AMux_MUXTYPE == TouchScreen_AMux_MUX_DIFF)
void TouchScreen_AMux_Next(void);
void TouchScreen_AMux_DisconnectAll(void);
#else
/* The Next and DisconnectAll functions are declared in cyfitter_cfg.h. */
/* void TouchScreen_AMux_Next(void); */
/* void TouchScreen_AMux_DisconnectAll(void); */
#endif
int8 TouchScreen_AMux_GetChannel(void);


/***************************************
*           Global Variables
***************************************/

extern uint8 TouchScreen_AMux_initVar;


/***************************************
*         Parameter Constants
***************************************/
#define TouchScreen_AMux_CHANNELS 2


#endif /* CY_AMUXSEQ_TouchScreen_AMux_H */


/* [] END OF FILE */
