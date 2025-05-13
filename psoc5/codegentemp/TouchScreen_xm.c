/*******************************************************************************
* File Name: TouchScreen_xm.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "TouchScreen_xm.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 TouchScreen_xm__PORT == 15 && ((TouchScreen_xm__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: TouchScreen_xm_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void TouchScreen_xm_Write(uint8 value) 
{
    uint8 staticBits = (TouchScreen_xm_DR & (uint8)(~TouchScreen_xm_MASK));
    TouchScreen_xm_DR = staticBits | ((uint8)(value << TouchScreen_xm_SHIFT) & TouchScreen_xm_MASK);
}


/*******************************************************************************
* Function Name: TouchScreen_xm_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  TouchScreen_xm_DM_STRONG     Strong Drive 
*  TouchScreen_xm_DM_OD_HI      Open Drain, Drives High 
*  TouchScreen_xm_DM_OD_LO      Open Drain, Drives Low 
*  TouchScreen_xm_DM_RES_UP     Resistive Pull Up 
*  TouchScreen_xm_DM_RES_DWN    Resistive Pull Down 
*  TouchScreen_xm_DM_RES_UPDWN  Resistive Pull Up/Down 
*  TouchScreen_xm_DM_DIG_HIZ    High Impedance Digital 
*  TouchScreen_xm_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void TouchScreen_xm_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(TouchScreen_xm_0, mode);
}


/*******************************************************************************
* Function Name: TouchScreen_xm_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro TouchScreen_xm_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 TouchScreen_xm_Read(void) 
{
    return (TouchScreen_xm_PS & TouchScreen_xm_MASK) >> TouchScreen_xm_SHIFT;
}


/*******************************************************************************
* Function Name: TouchScreen_xm_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 TouchScreen_xm_ReadDataReg(void) 
{
    return (TouchScreen_xm_DR & TouchScreen_xm_MASK) >> TouchScreen_xm_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(TouchScreen_xm_INTSTAT) 

    /*******************************************************************************
    * Function Name: TouchScreen_xm_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 TouchScreen_xm_ClearInterrupt(void) 
    {
        return (TouchScreen_xm_INTSTAT & TouchScreen_xm_MASK) >> TouchScreen_xm_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
