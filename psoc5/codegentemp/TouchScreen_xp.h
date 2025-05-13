/*******************************************************************************
* File Name: TouchScreen_xp.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_TouchScreen_xp_H) /* Pins TouchScreen_xp_H */
#define CY_PINS_TouchScreen_xp_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TouchScreen_xp_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TouchScreen_xp__PORT == 15 && ((TouchScreen_xp__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    TouchScreen_xp_Write(uint8 value) ;
void    TouchScreen_xp_SetDriveMode(uint8 mode) ;
uint8   TouchScreen_xp_ReadDataReg(void) ;
uint8   TouchScreen_xp_Read(void) ;
uint8   TouchScreen_xp_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define TouchScreen_xp_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define TouchScreen_xp_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define TouchScreen_xp_DM_RES_UP          PIN_DM_RES_UP
#define TouchScreen_xp_DM_RES_DWN         PIN_DM_RES_DWN
#define TouchScreen_xp_DM_OD_LO           PIN_DM_OD_LO
#define TouchScreen_xp_DM_OD_HI           PIN_DM_OD_HI
#define TouchScreen_xp_DM_STRONG          PIN_DM_STRONG
#define TouchScreen_xp_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define TouchScreen_xp_MASK               TouchScreen_xp__MASK
#define TouchScreen_xp_SHIFT              TouchScreen_xp__SHIFT
#define TouchScreen_xp_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TouchScreen_xp_PS                     (* (reg8 *) TouchScreen_xp__PS)
/* Data Register */
#define TouchScreen_xp_DR                     (* (reg8 *) TouchScreen_xp__DR)
/* Port Number */
#define TouchScreen_xp_PRT_NUM                (* (reg8 *) TouchScreen_xp__PRT) 
/* Connect to Analog Globals */                                                  
#define TouchScreen_xp_AG                     (* (reg8 *) TouchScreen_xp__AG)                       
/* Analog MUX bux enable */
#define TouchScreen_xp_AMUX                   (* (reg8 *) TouchScreen_xp__AMUX) 
/* Bidirectional Enable */                                                        
#define TouchScreen_xp_BIE                    (* (reg8 *) TouchScreen_xp__BIE)
/* Bit-mask for Aliased Register Access */
#define TouchScreen_xp_BIT_MASK               (* (reg8 *) TouchScreen_xp__BIT_MASK)
/* Bypass Enable */
#define TouchScreen_xp_BYP                    (* (reg8 *) TouchScreen_xp__BYP)
/* Port wide control signals */                                                   
#define TouchScreen_xp_CTL                    (* (reg8 *) TouchScreen_xp__CTL)
/* Drive Modes */
#define TouchScreen_xp_DM0                    (* (reg8 *) TouchScreen_xp__DM0) 
#define TouchScreen_xp_DM1                    (* (reg8 *) TouchScreen_xp__DM1)
#define TouchScreen_xp_DM2                    (* (reg8 *) TouchScreen_xp__DM2) 
/* Input Buffer Disable Override */
#define TouchScreen_xp_INP_DIS                (* (reg8 *) TouchScreen_xp__INP_DIS)
/* LCD Common or Segment Drive */
#define TouchScreen_xp_LCD_COM_SEG            (* (reg8 *) TouchScreen_xp__LCD_COM_SEG)
/* Enable Segment LCD */
#define TouchScreen_xp_LCD_EN                 (* (reg8 *) TouchScreen_xp__LCD_EN)
/* Slew Rate Control */
#define TouchScreen_xp_SLW                    (* (reg8 *) TouchScreen_xp__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TouchScreen_xp_PRTDSI__CAPS_SEL       (* (reg8 *) TouchScreen_xp__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TouchScreen_xp_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TouchScreen_xp__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TouchScreen_xp_PRTDSI__OE_SEL0        (* (reg8 *) TouchScreen_xp__PRTDSI__OE_SEL0) 
#define TouchScreen_xp_PRTDSI__OE_SEL1        (* (reg8 *) TouchScreen_xp__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TouchScreen_xp_PRTDSI__OUT_SEL0       (* (reg8 *) TouchScreen_xp__PRTDSI__OUT_SEL0) 
#define TouchScreen_xp_PRTDSI__OUT_SEL1       (* (reg8 *) TouchScreen_xp__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TouchScreen_xp_PRTDSI__SYNC_OUT       (* (reg8 *) TouchScreen_xp__PRTDSI__SYNC_OUT) 


#if defined(TouchScreen_xp__INTSTAT)  /* Interrupt Registers */

    #define TouchScreen_xp_INTSTAT                (* (reg8 *) TouchScreen_xp__INTSTAT)
    #define TouchScreen_xp_SNAP                   (* (reg8 *) TouchScreen_xp__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TouchScreen_xp_H */


/* [] END OF FILE */
