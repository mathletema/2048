/*******************************************************************************
* File Name: TouchScreen_yp.h  
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

#if !defined(CY_PINS_TouchScreen_yp_H) /* Pins TouchScreen_yp_H */
#define CY_PINS_TouchScreen_yp_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TouchScreen_yp_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TouchScreen_yp__PORT == 15 && ((TouchScreen_yp__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    TouchScreen_yp_Write(uint8 value) ;
void    TouchScreen_yp_SetDriveMode(uint8 mode) ;
uint8   TouchScreen_yp_ReadDataReg(void) ;
uint8   TouchScreen_yp_Read(void) ;
uint8   TouchScreen_yp_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define TouchScreen_yp_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define TouchScreen_yp_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define TouchScreen_yp_DM_RES_UP          PIN_DM_RES_UP
#define TouchScreen_yp_DM_RES_DWN         PIN_DM_RES_DWN
#define TouchScreen_yp_DM_OD_LO           PIN_DM_OD_LO
#define TouchScreen_yp_DM_OD_HI           PIN_DM_OD_HI
#define TouchScreen_yp_DM_STRONG          PIN_DM_STRONG
#define TouchScreen_yp_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define TouchScreen_yp_MASK               TouchScreen_yp__MASK
#define TouchScreen_yp_SHIFT              TouchScreen_yp__SHIFT
#define TouchScreen_yp_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TouchScreen_yp_PS                     (* (reg8 *) TouchScreen_yp__PS)
/* Data Register */
#define TouchScreen_yp_DR                     (* (reg8 *) TouchScreen_yp__DR)
/* Port Number */
#define TouchScreen_yp_PRT_NUM                (* (reg8 *) TouchScreen_yp__PRT) 
/* Connect to Analog Globals */                                                  
#define TouchScreen_yp_AG                     (* (reg8 *) TouchScreen_yp__AG)                       
/* Analog MUX bux enable */
#define TouchScreen_yp_AMUX                   (* (reg8 *) TouchScreen_yp__AMUX) 
/* Bidirectional Enable */                                                        
#define TouchScreen_yp_BIE                    (* (reg8 *) TouchScreen_yp__BIE)
/* Bit-mask for Aliased Register Access */
#define TouchScreen_yp_BIT_MASK               (* (reg8 *) TouchScreen_yp__BIT_MASK)
/* Bypass Enable */
#define TouchScreen_yp_BYP                    (* (reg8 *) TouchScreen_yp__BYP)
/* Port wide control signals */                                                   
#define TouchScreen_yp_CTL                    (* (reg8 *) TouchScreen_yp__CTL)
/* Drive Modes */
#define TouchScreen_yp_DM0                    (* (reg8 *) TouchScreen_yp__DM0) 
#define TouchScreen_yp_DM1                    (* (reg8 *) TouchScreen_yp__DM1)
#define TouchScreen_yp_DM2                    (* (reg8 *) TouchScreen_yp__DM2) 
/* Input Buffer Disable Override */
#define TouchScreen_yp_INP_DIS                (* (reg8 *) TouchScreen_yp__INP_DIS)
/* LCD Common or Segment Drive */
#define TouchScreen_yp_LCD_COM_SEG            (* (reg8 *) TouchScreen_yp__LCD_COM_SEG)
/* Enable Segment LCD */
#define TouchScreen_yp_LCD_EN                 (* (reg8 *) TouchScreen_yp__LCD_EN)
/* Slew Rate Control */
#define TouchScreen_yp_SLW                    (* (reg8 *) TouchScreen_yp__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TouchScreen_yp_PRTDSI__CAPS_SEL       (* (reg8 *) TouchScreen_yp__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TouchScreen_yp_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TouchScreen_yp__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TouchScreen_yp_PRTDSI__OE_SEL0        (* (reg8 *) TouchScreen_yp__PRTDSI__OE_SEL0) 
#define TouchScreen_yp_PRTDSI__OE_SEL1        (* (reg8 *) TouchScreen_yp__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TouchScreen_yp_PRTDSI__OUT_SEL0       (* (reg8 *) TouchScreen_yp__PRTDSI__OUT_SEL0) 
#define TouchScreen_yp_PRTDSI__OUT_SEL1       (* (reg8 *) TouchScreen_yp__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TouchScreen_yp_PRTDSI__SYNC_OUT       (* (reg8 *) TouchScreen_yp__PRTDSI__SYNC_OUT) 


#if defined(TouchScreen_yp__INTSTAT)  /* Interrupt Registers */

    #define TouchScreen_yp_INTSTAT                (* (reg8 *) TouchScreen_yp__INTSTAT)
    #define TouchScreen_yp_SNAP                   (* (reg8 *) TouchScreen_yp__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TouchScreen_yp_H */


/* [] END OF FILE */
