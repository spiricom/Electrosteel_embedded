/*******************************************************************************
* File Name: knobPanelLight1.h  
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

#if !defined(CY_PINS_knobPanelLight1_H) /* Pins knobPanelLight1_H */
#define CY_PINS_knobPanelLight1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "knobPanelLight1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 knobPanelLight1__PORT == 15 && ((knobPanelLight1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    knobPanelLight1_Write(uint8 value);
void    knobPanelLight1_SetDriveMode(uint8 mode);
uint8   knobPanelLight1_ReadDataReg(void);
uint8   knobPanelLight1_Read(void);
void    knobPanelLight1_SetInterruptMode(uint16 position, uint16 mode);
uint8   knobPanelLight1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the knobPanelLight1_SetDriveMode() function.
     *  @{
     */
        #define knobPanelLight1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define knobPanelLight1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define knobPanelLight1_DM_RES_UP          PIN_DM_RES_UP
        #define knobPanelLight1_DM_RES_DWN         PIN_DM_RES_DWN
        #define knobPanelLight1_DM_OD_LO           PIN_DM_OD_LO
        #define knobPanelLight1_DM_OD_HI           PIN_DM_OD_HI
        #define knobPanelLight1_DM_STRONG          PIN_DM_STRONG
        #define knobPanelLight1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define knobPanelLight1_MASK               knobPanelLight1__MASK
#define knobPanelLight1_SHIFT              knobPanelLight1__SHIFT
#define knobPanelLight1_WIDTH              1u

/* Interrupt constants */
#if defined(knobPanelLight1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in knobPanelLight1_SetInterruptMode() function.
     *  @{
     */
        #define knobPanelLight1_INTR_NONE      (uint16)(0x0000u)
        #define knobPanelLight1_INTR_RISING    (uint16)(0x0001u)
        #define knobPanelLight1_INTR_FALLING   (uint16)(0x0002u)
        #define knobPanelLight1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define knobPanelLight1_INTR_MASK      (0x01u) 
#endif /* (knobPanelLight1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define knobPanelLight1_PS                     (* (reg8 *) knobPanelLight1__PS)
/* Data Register */
#define knobPanelLight1_DR                     (* (reg8 *) knobPanelLight1__DR)
/* Port Number */
#define knobPanelLight1_PRT_NUM                (* (reg8 *) knobPanelLight1__PRT) 
/* Connect to Analog Globals */                                                  
#define knobPanelLight1_AG                     (* (reg8 *) knobPanelLight1__AG)                       
/* Analog MUX bux enable */
#define knobPanelLight1_AMUX                   (* (reg8 *) knobPanelLight1__AMUX) 
/* Bidirectional Enable */                                                        
#define knobPanelLight1_BIE                    (* (reg8 *) knobPanelLight1__BIE)
/* Bit-mask for Aliased Register Access */
#define knobPanelLight1_BIT_MASK               (* (reg8 *) knobPanelLight1__BIT_MASK)
/* Bypass Enable */
#define knobPanelLight1_BYP                    (* (reg8 *) knobPanelLight1__BYP)
/* Port wide control signals */                                                   
#define knobPanelLight1_CTL                    (* (reg8 *) knobPanelLight1__CTL)
/* Drive Modes */
#define knobPanelLight1_DM0                    (* (reg8 *) knobPanelLight1__DM0) 
#define knobPanelLight1_DM1                    (* (reg8 *) knobPanelLight1__DM1)
#define knobPanelLight1_DM2                    (* (reg8 *) knobPanelLight1__DM2) 
/* Input Buffer Disable Override */
#define knobPanelLight1_INP_DIS                (* (reg8 *) knobPanelLight1__INP_DIS)
/* LCD Common or Segment Drive */
#define knobPanelLight1_LCD_COM_SEG            (* (reg8 *) knobPanelLight1__LCD_COM_SEG)
/* Enable Segment LCD */
#define knobPanelLight1_LCD_EN                 (* (reg8 *) knobPanelLight1__LCD_EN)
/* Slew Rate Control */
#define knobPanelLight1_SLW                    (* (reg8 *) knobPanelLight1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define knobPanelLight1_PRTDSI__CAPS_SEL       (* (reg8 *) knobPanelLight1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define knobPanelLight1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) knobPanelLight1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define knobPanelLight1_PRTDSI__OE_SEL0        (* (reg8 *) knobPanelLight1__PRTDSI__OE_SEL0) 
#define knobPanelLight1_PRTDSI__OE_SEL1        (* (reg8 *) knobPanelLight1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define knobPanelLight1_PRTDSI__OUT_SEL0       (* (reg8 *) knobPanelLight1__PRTDSI__OUT_SEL0) 
#define knobPanelLight1_PRTDSI__OUT_SEL1       (* (reg8 *) knobPanelLight1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define knobPanelLight1_PRTDSI__SYNC_OUT       (* (reg8 *) knobPanelLight1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(knobPanelLight1__SIO_CFG)
    #define knobPanelLight1_SIO_HYST_EN        (* (reg8 *) knobPanelLight1__SIO_HYST_EN)
    #define knobPanelLight1_SIO_REG_HIFREQ     (* (reg8 *) knobPanelLight1__SIO_REG_HIFREQ)
    #define knobPanelLight1_SIO_CFG            (* (reg8 *) knobPanelLight1__SIO_CFG)
    #define knobPanelLight1_SIO_DIFF           (* (reg8 *) knobPanelLight1__SIO_DIFF)
#endif /* (knobPanelLight1__SIO_CFG) */

/* Interrupt Registers */
#if defined(knobPanelLight1__INTSTAT)
    #define knobPanelLight1_INTSTAT            (* (reg8 *) knobPanelLight1__INTSTAT)
    #define knobPanelLight1_SNAP               (* (reg8 *) knobPanelLight1__SNAP)
    
	#define knobPanelLight1_0_INTTYPE_REG 		(* (reg8 *) knobPanelLight1__0__INTTYPE)
#endif /* (knobPanelLight1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_knobPanelLight1_H */


/* [] END OF FILE */
