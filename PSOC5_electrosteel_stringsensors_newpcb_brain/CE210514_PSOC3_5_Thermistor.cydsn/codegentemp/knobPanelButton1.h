/*******************************************************************************
* File Name: knobPanelButton1.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_knobPanelButton1_H) /* Pins knobPanelButton1_H */
#define CY_PINS_knobPanelButton1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "knobPanelButton1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 knobPanelButton1__PORT == 15 && ((knobPanelButton1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    knobPanelButton1_Write(uint8 value);
void    knobPanelButton1_SetDriveMode(uint8 mode);
uint8   knobPanelButton1_ReadDataReg(void);
uint8   knobPanelButton1_Read(void);
void    knobPanelButton1_SetInterruptMode(uint16 position, uint16 mode);
uint8   knobPanelButton1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the knobPanelButton1_SetDriveMode() function.
     *  @{
     */
        #define knobPanelButton1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define knobPanelButton1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define knobPanelButton1_DM_RES_UP          PIN_DM_RES_UP
        #define knobPanelButton1_DM_RES_DWN         PIN_DM_RES_DWN
        #define knobPanelButton1_DM_OD_LO           PIN_DM_OD_LO
        #define knobPanelButton1_DM_OD_HI           PIN_DM_OD_HI
        #define knobPanelButton1_DM_STRONG          PIN_DM_STRONG
        #define knobPanelButton1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define knobPanelButton1_MASK               knobPanelButton1__MASK
#define knobPanelButton1_SHIFT              knobPanelButton1__SHIFT
#define knobPanelButton1_WIDTH              1u

/* Interrupt constants */
#if defined(knobPanelButton1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in knobPanelButton1_SetInterruptMode() function.
     *  @{
     */
        #define knobPanelButton1_INTR_NONE      (uint16)(0x0000u)
        #define knobPanelButton1_INTR_RISING    (uint16)(0x0001u)
        #define knobPanelButton1_INTR_FALLING   (uint16)(0x0002u)
        #define knobPanelButton1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define knobPanelButton1_INTR_MASK      (0x01u) 
#endif /* (knobPanelButton1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define knobPanelButton1_PS                     (* (reg8 *) knobPanelButton1__PS)
/* Data Register */
#define knobPanelButton1_DR                     (* (reg8 *) knobPanelButton1__DR)
/* Port Number */
#define knobPanelButton1_PRT_NUM                (* (reg8 *) knobPanelButton1__PRT) 
/* Connect to Analog Globals */                                                  
#define knobPanelButton1_AG                     (* (reg8 *) knobPanelButton1__AG)                       
/* Analog MUX bux enable */
#define knobPanelButton1_AMUX                   (* (reg8 *) knobPanelButton1__AMUX) 
/* Bidirectional Enable */                                                        
#define knobPanelButton1_BIE                    (* (reg8 *) knobPanelButton1__BIE)
/* Bit-mask for Aliased Register Access */
#define knobPanelButton1_BIT_MASK               (* (reg8 *) knobPanelButton1__BIT_MASK)
/* Bypass Enable */
#define knobPanelButton1_BYP                    (* (reg8 *) knobPanelButton1__BYP)
/* Port wide control signals */                                                   
#define knobPanelButton1_CTL                    (* (reg8 *) knobPanelButton1__CTL)
/* Drive Modes */
#define knobPanelButton1_DM0                    (* (reg8 *) knobPanelButton1__DM0) 
#define knobPanelButton1_DM1                    (* (reg8 *) knobPanelButton1__DM1)
#define knobPanelButton1_DM2                    (* (reg8 *) knobPanelButton1__DM2) 
/* Input Buffer Disable Override */
#define knobPanelButton1_INP_DIS                (* (reg8 *) knobPanelButton1__INP_DIS)
/* LCD Common or Segment Drive */
#define knobPanelButton1_LCD_COM_SEG            (* (reg8 *) knobPanelButton1__LCD_COM_SEG)
/* Enable Segment LCD */
#define knobPanelButton1_LCD_EN                 (* (reg8 *) knobPanelButton1__LCD_EN)
/* Slew Rate Control */
#define knobPanelButton1_SLW                    (* (reg8 *) knobPanelButton1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define knobPanelButton1_PRTDSI__CAPS_SEL       (* (reg8 *) knobPanelButton1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define knobPanelButton1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) knobPanelButton1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define knobPanelButton1_PRTDSI__OE_SEL0        (* (reg8 *) knobPanelButton1__PRTDSI__OE_SEL0) 
#define knobPanelButton1_PRTDSI__OE_SEL1        (* (reg8 *) knobPanelButton1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define knobPanelButton1_PRTDSI__OUT_SEL0       (* (reg8 *) knobPanelButton1__PRTDSI__OUT_SEL0) 
#define knobPanelButton1_PRTDSI__OUT_SEL1       (* (reg8 *) knobPanelButton1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define knobPanelButton1_PRTDSI__SYNC_OUT       (* (reg8 *) knobPanelButton1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(knobPanelButton1__SIO_CFG)
    #define knobPanelButton1_SIO_HYST_EN        (* (reg8 *) knobPanelButton1__SIO_HYST_EN)
    #define knobPanelButton1_SIO_REG_HIFREQ     (* (reg8 *) knobPanelButton1__SIO_REG_HIFREQ)
    #define knobPanelButton1_SIO_CFG            (* (reg8 *) knobPanelButton1__SIO_CFG)
    #define knobPanelButton1_SIO_DIFF           (* (reg8 *) knobPanelButton1__SIO_DIFF)
#endif /* (knobPanelButton1__SIO_CFG) */

/* Interrupt Registers */
#if defined(knobPanelButton1__INTSTAT)
    #define knobPanelButton1_INTSTAT            (* (reg8 *) knobPanelButton1__INTSTAT)
    #define knobPanelButton1_SNAP               (* (reg8 *) knobPanelButton1__SNAP)
    
	#define knobPanelButton1_0_INTTYPE_REG 		(* (reg8 *) knobPanelButton1__0__INTTYPE)
#endif /* (knobPanelButton1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_knobPanelButton1_H */


/* [] END OF FILE */
