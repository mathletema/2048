/*******************************************************************************
* File Name: TouchScreen.c
* Version 2.0
*
* Description:
*  This file provides the API source code for the Resistive Touch component.
*
* Note:
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"
#include "TouchScreen.h"
#include "TouchScreen_xm.h"
#include "TouchScreen_xp.h"
#include "TouchScreen_ym.h"
#include "TouchScreen_yp.h"

uint8 TouchScreen_initVar = 0u;
static uint8 TouchScreen_measurementFlag = 0u;


/*******************************************************************************
* Function Name: TouchScreen_Init
********************************************************************************
*
* Summary:
*  Calls the Init() function of the ADC and AMux components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TouchScreen_Init(void) 
{
    TouchScreen_AMux_Init();
    TouchScreen_ADC_Init();
}


/*******************************************************************************
* Function Name: TouchScreen_Start
********************************************************************************
*
* Summary:
*  Calls Init() if the component has not been initialized before. Calls Enable()
*  to begin the component operation.
*
* Parameters:
*  None
*
* Return:
*  None
* 
* Global variables:
*  TouchScreen_initVar - Indicates whether the component has been
*                             initialized.
*
*******************************************************************************/
void TouchScreen_Start(void)  
{
    if(TouchScreen_initVar == 0u)
    {    
        TouchScreen_Init();
        TouchScreen_initVar = 1u;
    }
    TouchScreen_Enable();
}


/*******************************************************************************
* Function Name: TouchScreen_Stop
********************************************************************************
*
* Summary:
*  Stops the ADC and AMux components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TouchScreen_Stop(void)  
{
    TouchScreen_ADC_Stop();
    TouchScreen_AMux_Stop();
}


/*******************************************************************************
* Function Name: TouchScreen_Enable
********************************************************************************
*
* Summary:
*  Enables the ADC component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TouchScreen_Enable(void)  
{
    TouchScreen_ADC_Enable();
}


/*******************************************************************************
* Function Name: TouchScreen_ActivateX
********************************************************************************
*
* Summary: 
*  Configures the pins to measure the Y-axis.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TouchScreen_ActivateX(void) 
{
    /* Pins configuration to measure Y. */
    CyPins_SetPinDriveMode(TouchScreen_ym_0, PIN_DM_STRONG);
    CyPins_SetPinDriveMode(TouchScreen_yp_0, PIN_DM_STRONG);
    CyPins_SetPinDriveMode(TouchScreen_xp_0, PIN_DM_ALG_HIZ);
    CyPins_SetPinDriveMode(TouchScreen_xm_0, PIN_DM_ALG_HIZ);
    
    /* Switch AMux if channel 0 is not selected. */
    if(TouchScreen_AMux_GetChannel() != TouchScreen_AMUX_XP_CHAN)
    {
        TouchScreen_AMux_Next();
    }
}


/*******************************************************************************
* Function Name: TouchScreen_ActivateY
********************************************************************************
*
* Summary: 
*  Configures the pins to measure X-axis.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TouchScreen_ActivateY(void) 
{
    /* Pins configuration to measure X. */
    CyPins_SetPinDriveMode(TouchScreen_xm_0, PIN_DM_STRONG);
    CyPins_SetPinDriveMode(TouchScreen_xp_0, PIN_DM_STRONG);
    CyPins_SetPinDriveMode(TouchScreen_yp_0, PIN_DM_ALG_HIZ);
    CyPins_SetPinDriveMode(TouchScreen_ym_0, PIN_DM_ALG_HIZ);
    
    /* Switch AMux if channel 1 is not selected. */
    if(TouchScreen_AMux_GetChannel() == TouchScreen_AMUX_XP_CHAN)
    {
        TouchScreen_AMux_Next();
    }
    /* Switch AMux to channel 1 if AMux is disconnected. */
    else if(TouchScreen_AMux_GetChannel() == TouchScreen_AMUX_NO_CHAN)
    {
        TouchScreen_AMux_Next();
        TouchScreen_AMux_Next();
    }
    else
    {
        /* Channel 1 is already selected. */
    }
}


/*******************************************************************************
* Function Name: TouchScreen_TouchDetect
********************************************************************************
*
* Summary:
*  Determines if the screen is touched.
*
* Parameters:
*  None
*
* Return:
*  uint8: The touch state.
*  0 - untouched
*  1 - touched
*
*******************************************************************************/
uint8 TouchScreen_TouchDetect(void) 
{
    /* Configure x+ pin to detect touch. */
    CyPins_SetPinDriveMode(TouchScreen_xp_0, PIN_DM_STRONG);

    /* Add delay for signal to stabilize. */
    CyDelayUs(5u);

    CyPins_SetPinDriveMode(TouchScreen_xp_0, PIN_DM_RES_UP);
    
    /* Switch AMux if channel 0 is not selected. */
    if(TouchScreen_AMux_GetChannel() != TouchScreen_AMUX_XP_CHAN)
    {
        TouchScreen_AMux_Next();
    }

    /* Configure x-, y+ and y- to detect touch. */
    CyPins_SetPinDriveMode(TouchScreen_xm_0, PIN_DM_ALG_HIZ);
    CyPins_SetPinDriveMode(TouchScreen_yp_0, PIN_DM_ALG_HIZ);
    CyPins_SetPinDriveMode(TouchScreen_ym_0, PIN_DM_STRONG);

    /* Add delay for signal to stabilize. The delay is dependant on whether
    * the measurement has been done before touch detect or not.
    */
    if (TouchScreen_measurementFlag == 0u)
    {
        CyDelayUs(20u);
    }
    else
    {
        TouchScreen_measurementFlag = 0u;
        CyDelayUs(8u);        
    }
    /* The screen is touched if the measured value is lower than the specified
    * threshold.
    */
    return ((TouchScreen_Measure() < TouchScreen_TOUCH_THRESHOLD) ? 1u : 0u);
}


/*******************************************************************************
* Function Name: TouchScreen_Measure
********************************************************************************
*
* Summary:
*  Returns the result of the ADC conversion. Does not return until ADC
*  conversion is complete.
*
* Parameters:
*  None
*
* Return:
*  int16: the result of the ADC conversion.
*
*******************************************************************************/
int16 TouchScreen_Measure(void) 
{       
    int16 result;

    /* Trigger the ADC conversion and wait for results (blocking). */
    TouchScreen_ADC_StartConvert();
    (void)TouchScreen_ADC_IsEndConversion(TouchScreen_ADC_WAIT_FOR_RESULT);
    result = TouchScreen_ADC_GetResult16();

    /* Assert a flag indicating that the measurement has been done. */
    TouchScreen_measurementFlag = 1u;
    return (result);
}


/* [] END OF FILE */
