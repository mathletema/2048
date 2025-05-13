/*******************************************************************************
* File Name: TouchScreen_PM.c
* Version 2.0
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "TouchScreen.h"


/*******************************************************************************
* Function Name: TouchScreen_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the ADC configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TouchScreen_SaveConfig(void) 
{
    TouchScreen_ADC_SaveConfig();   
}


/*******************************************************************************
* Function Name: TouchScreen_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the ADC configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void TouchScreen_RestoreConfig(void) 
{
    TouchScreen_ADC_RestoreConfig();  
}


/*******************************************************************************
* Function Name: TouchScreen_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TouchScreen_Sleep(void) 
{
    TouchScreen_ADC_Sleep();
    TouchScreen_AMux_Stop();
}


/*******************************************************************************
* Function Name: TouchScreen_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TouchScreen_Wakeup(void)  
{
    TouchScreen_ADC_Wakeup();
}


/* [] END OF FILE */
