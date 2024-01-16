/*******************************************************************************
* File Name: knobPanelLight2.h  
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

#if !defined(CY_PINS_knobPanelLight2_H) /* Pins knobPanelLight2_H */
#define CY_PINS_knobPanelLight2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "knobPanelLight2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 knobPanelLight2__PORT == 15 && ((knobPanelLight2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    knobPanelLight2_Write(uint8 value);
void    knobPanelLight2_SetDriveMode(uint8 mode);
uint8   knobPanelLight2_ReadDataReg(void);
uint8   knobPanelLight2_Read(void);
void    knobPanelLight2_SetInterruptMode(uint16 position, uint16 mode);
uint8   knobPanelLight2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the knobPanelLight2_SetDriveMode() function.
     *  @{
     */
        #define knobPanelLight2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define knobPanelLight2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define knobPanelLight2_DM_RES_UP          PIN_DM_RES_UP
        #define knobPanelLight2_DM_RES_DWN         PIN_DM_RES_DWN
        #define knobPanelLight2_DM_OD_LO           PIN_DM_OD_LO
        #define knobPanelLight2_DM_OD_HI           PIN_DM_OD_HI
        #define knobPanelLight2_DM_STRONG          PIN_DM_STRONG
        #define knobPanelLight2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define knobPanelLight2_MASK               knobPanelLight2__MASK
#define knobPanelLight2_SHIFT              knobPanelLight2__SHIFT
#define knobPanelLight2_WIDTH              1u

/* Interrupt constants */
#if defined(knobPanelLight2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in knobPanelLight2_SetInterruptMode() function.
     *  @{
     */
        #define knobPanelLight2_INTR_NONE      (uint16)(0x0000u)
        #define knobPanelLight2_INTR_RISING    (uint16)(0x0001u)
        #define knobPanelLight2_INTR_FALLING   (uint16)(0x0002u)
        #define knobPanelLight2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define knobPanelLight2_INTR_MASK      (0x01u) 
#endif /* (knobPanelLight2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define knobPanelLight2_PS                     (* (reg8 *) knobPanelLight2__PS)
/* Data Register */
#define knobPanelLight2_DR                     (* (reg8 *) knobPanelLight2__DR)
/* Port Number */
#define knobPanelLight2_PRT_NUM                (* (reg8 *) knobPanelLight2__PRT) 
/* Connect to Analog Globals */                                                  
#define knobPanelLight2_AG                     (* (reg8 *) knobPanelLight2__AG)                       
/* Analog MUX bux enable */
#define knobPanelLight2_AMUX                   (* (reg8 *) knobPanelLight2__AMUX) 
/* Bidirectional Enable */                                                        
#define knobPanelLight2_BIE                    (* (reg8 *) knobPanelLight2__BIE)
/* Bit-mask for Aliased Register Access */
#define knobPanelLight2_BIT_MASK               (* (reg8 *) knobPanelLight2__BIT_MASK)
/* Bypass Enable */
#define knobPanelLight2_BYP                    (* (reg8 *) knobPanelLight2__BYP)
/* Port wide control signals */                                                   
#define knobPanelLight2_CTL                    (* (reg8 *) knobPanelLight2__CTL)
/* Drive Modes */
#define knobPanelLight2_DM0                    (* (reg8 *) knobPanelLight2__DM0) 
#define knobPanelLight2_DM1                    (* (reg8 *) knobPanelLight2__DM1)
#define knobPanelLight2_DM2                    (* (reg8 *) knobPanelLight2__DM2) 
/* Input Buffer Disable Override */
#define knobPanelLight2_INP_DIS                (* (reg8 *) knobPanelLight2__INP_DIS)
/* LCD Common or Segment Drive */
#define knobPanelLight2_LCD_COM_SEG            (* (reg8 *) knobPanelLight2__LCD_COM_SEG)
/* Enable Segment LCD */
#define knobPanelLight2_LCD_EN                 (* (reg8 *) knobPanelLight2__LCD_EN)
/* Slew Rate Control */
#define knobPanelLight2_SLW                    (* (reg8 *) knobPanelLight2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define knobPanelLight2_PRTDSI__CAPS_SEL       (* (reg8 *) knobPanelLight2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define knobPanelLight2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) knobPanelLight2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define knobPanelLight2_PRTDSI__OE_SEL0        (* (reg8 *) knobPanelLight2__PRTDSI__OE_SEL0) 
#define knobPanelLight2_PRTDSI__OE_SEL1        (* (reg8 *) knobPanelLight2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define knobPanelLight2_PRTDSI__OUT_SEL0       (* (reg8 *) knobPanelLight2__PRTDSI__OUT_SEL0) 
#define knobPanelLight2_PRTDSI__OUT_SEL1       (* (reg8 *) knobPanelLight2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define knobPanelLight2_PRTDSI__SYNC_OUT       (* (reg8 *) knobPanelLight2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(knobPanelLight2__SIO_CFG)
    #define knobPanelLight2_SIO_HYST_EN        (* (reg8 *) knobPanelLight2__SIO_HYST_EN)
    #define knobPanelLight2_SIO_REG_HIFREQ     (* (reg8 *) knobPanelLight2__SIO_REG_HIFREQ)
    #define knobPanelLight2_SIO_CFG            (* (reg8 *) knobPanelLight2__SIO_CFG)
    #define knobPanelLight2_SIO_DIFF           (* (reg8 *) knobPanelLight2__SIO_DIFF)
#endif /* (knobPanelLight2__SIO_CFG) */

/* Interrupt Registers */
#if defined(knobPanelLight2__INTSTAT)
    #define knobPanelLight2_INTSTAT            (* (reg8 *) knobPanelLight2__INTSTAT)
    #define knobPanelLight2_SNAP               (* (reg8 *) knobPanelLight2__SNAP)
    
	#define knobPanelLight2_0_INTTYPE_REG 		(* (reg8 *) knobPanelLight2__0__INTTYPE)
#endif /* (knobPanelLight2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_knobPanelLight2_H */


/* [] END OF FILE */
