/*******************************************************************************
* File Name: Input_Data.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Input_Data_ALIASES_H) /* Pins Input_Data_ALIASES_H */
#define CY_PINS_Input_Data_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Input_Data_0			(Input_Data__0__PC)
#define Input_Data_0_INTR	((uint16)((uint16)0x0001u << Input_Data__0__SHIFT))

#define Input_Data_1			(Input_Data__1__PC)
#define Input_Data_1_INTR	((uint16)((uint16)0x0001u << Input_Data__1__SHIFT))

#define Input_Data_2			(Input_Data__2__PC)
#define Input_Data_2_INTR	((uint16)((uint16)0x0001u << Input_Data__2__SHIFT))

#define Input_Data_3			(Input_Data__3__PC)
#define Input_Data_3_INTR	((uint16)((uint16)0x0001u << Input_Data__3__SHIFT))

#define Input_Data_INTR_ALL	 ((uint16)(Input_Data_0_INTR| Input_Data_1_INTR| Input_Data_2_INTR| Input_Data_3_INTR))

#endif /* End Pins Input_Data_ALIASES_H */


/* [] END OF FILE */
