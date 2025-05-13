/*******************************************************************************
* File Name: TouchScreen_AMux.c
* Version 1.80
*
*  Description:
*    This file contains functions for the AMuxSeq.
*
*   Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "TouchScreen_AMux.h"

uint8 TouchScreen_AMux_initVar = 0u;


/*******************************************************************************
* Function Name: TouchScreen_AMux_Start
********************************************************************************
* Summary:
*  Disconnect all channels. The next time Next is called, channel 0 will be
*  connected.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void TouchScreen_AMux_Start(void)
{
    TouchScreen_AMux_DisconnectAll();
    TouchScreen_AMux_initVar = 1u;
}


/*******************************************************************************
* Function Name: TouchScreen_AMux_Init
********************************************************************************
* Summary:
*  Disconnect all channels. The next time Next is called, channel 0 will be
*  connected.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void TouchScreen_AMux_Init(void)
{
    TouchScreen_AMux_DisconnectAll();
}


/*******************************************************************************
* Function Name: TouchScreen_AMux_Stop
********************************************************************************
* Summary:
*  Disconnect all channels. The next time Next is called, channel 0 will be
*  connected.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void TouchScreen_AMux_Stop(void)
{
    TouchScreen_AMux_DisconnectAll();
}

#if (TouchScreen_AMux_MUXTYPE == TouchScreen_AMux_MUX_DIFF)

/*******************************************************************************
* Function Name: TouchScreen_AMux_Next
********************************************************************************
* Summary:
*  Disconnects the previous channel and connects the next one in the sequence.
*  When Next is called for the first time after Init, Start, Enable, Stop, or
*  DisconnectAll, it connects channel 0.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void TouchScreen_AMux_Next(void)
{
    TouchScreen_AMux_CYAMUXSIDE_A_Next();
    TouchScreen_AMux_CYAMUXSIDE_B_Next();
}


/*******************************************************************************
* Function Name: TouchScreen_AMux_DisconnectAll
********************************************************************************
* Summary:
*  This function disconnects all channels. The next time Next is called, channel
*  0 will be connected.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void TouchScreen_AMux_DisconnectAll(void)
{
    TouchScreen_AMux_CYAMUXSIDE_A_DisconnectAll();
    TouchScreen_AMux_CYAMUXSIDE_B_DisconnectAll();
}


/*******************************************************************************
* Function Name: TouchScreen_AMux_GetChannel
********************************************************************************
* Summary:
*  The currently connected channel is retuned. If no channel is connected
*  returns -1.
*
* Parameters:
*  void
*
* Return:
*  The current channel or -1.
*
*******************************************************************************/
int8 TouchScreen_AMux_GetChannel(void)
{
    return TouchScreen_AMux_CYAMUXSIDE_A_curChannel;
}

#else

/*******************************************************************************
* Function Name: TouchScreen_AMux_GetChannel
********************************************************************************
* Summary:
*  The currently connected channel is retuned. If no channel is connected
*  returns -1.
*
* Parameters:
*  void
*
* Return:
*  The current channel or -1.
*
*******************************************************************************/
int8 TouchScreen_AMux_GetChannel(void)
{
    return TouchScreen_AMux_curChannel;
}

#endif


/* [] END OF FILE */
