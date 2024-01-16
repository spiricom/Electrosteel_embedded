/*******************************************************************************
* File Name: knobPanelButton2.h  
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

#if !defined(CY_PINS_knobPanelButton2_H) /* Pins knobPanelButton2_H */
#define CY_PINS_knobPanelButton2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "knobPanelButton2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 knobPanelButton2__PORT == 15 && ((knobPanelButton2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    knobPanelButton2_Write(uint8 value);
void    knobPanelButton2_SetDriveMode(uint8 mode);
uint8   knobPanelButton2_ReadDataReg(void);
uint8   knobPanelButton2_Read(void);
void    knobPanelButton2_SetInterruptMode(uint16 position, uint16 mode);
uint8   knobPanelButton2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the knobPanelButton2_SetDriveMode() function.
     *  @{
     */
        #define knobPanelButton2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define knobPanelButton2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define knobPanelButton2_DM_RES_UP          PIN_DM_RES_UP
        #define knobPanelButton2_DM_RES_DWN         PIN_DM_RES_DWN
        #define knobPanelButton2_DM_OD_LO           PIN_DM_OD_LO
        #define knobPanelButton2_DM_OD_HI           PIN_DM_OD_HI
        #define knobPanelButton2_DM_STRONG          PIN_DM_STRONG
        #define knobPanelButton2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define knobPanelButton2_MASK               knobPanelButton2__MASK
#define knobPanelButton2_SHIFT              knobPanelButton2__SHIFT
#define knobPanelButton2_WIDTH              1u

/* Interrupt constants */
#if defined(knobPanelButton2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in knobPanelButton2_SetInterruptMode() function.
     *  @{
     */
        #define knobPanelButton2_INTR_NONE      (uint16)(0x0000u)
        #define knobPanelButton2_INTR_RISING    (uint16)(0x0001u)
        #define knobPanelButton2_INTR_FALLING   (uint16)(0x0002u)
        #define knobPanelButton2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define knobPanelButton2_INTR_MASK      (0x01u) 
#endif /* (knobPanelButton2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define knobPanelButton2_PS                     (* (reg8 *) knobPanelButton2__PS)
/* Data Register */
#define knobPanelButton2_DR                     (* (reg8 *) knobPanelButton2__DR)
/* Port Number */
#define knobPanelButton2_PRT_NUM                (* (reg8 *) knobPanelButton2__PRT) 
/* Connect to Analog Globals */                                                  
#define knobPanelButton2_AG                     (* (reg8 *) knobPanelButton2__AG)                       
/* Analog MUX bux enable */
#define knobPanelButton2_AMUX                   (* (reg8 *) knobPanelButton2__AMUX) 
/* Bidirectional Enable */                                                        
#define knobPanelButton2_BIE                    (* (reg8 *) knobPanelButton2__BIE)
/* Bit-mask for Aliased Register Access */
#define knobPanelButton2_BIT_MASK               (* (reg8 *) knobPanelButton2__BIT_MASK)
/* Bypass Enable */
#define knobPanelButton2_BYP                    (* (reg8 *) knobPanelButton2__BYP)
/* Port wide control signals */                                                   
#define knobPanelButton2_CTL                    (* (reg8 *) knobPanelButton2__CTL)
/* Drive Modes */
#define knobPanelButton2_DM0                    (* (reg8 *) knobPanelButton2__DM0) 
#define knobPanelButton2_DM1                    (* (reg8 *) knobPanelButton2__DM1)
#define knobPanelButton2_DM2                    (* (reg8 *) knobPanelButton2__DM2) 
/* Input Buffer Disable Override */
#define knobPanelButton2_INP_DIS                (* (reg8 *) knobPanelButton2__INP_DIS)
/* LCD Common or Segment Drive */
#define knobPanelButton2_LCD_COM_SEG            (* (reg8 *) knobPanelButton2__LCD_COM_SEG)
/* Enable Segment LCD */
#define knobPanelButton2_LCD_EN                 (* (reg8 *) knobPanelButton2__LCD_EN)
/* Slew Rate Control */
#define knobPanelButton2_SLW                    (* (reg8 *) knobPanelButton2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define knobPanelButton2_PRTDSI__CAPS_SEL       (* (reg8 *) knobPanelButton2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define knobPanelButton2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) knobPanelButton2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define knobPanelButton2_PRTDSI__OE_SEL0        (* (reg8 *) knobPanelButton2__PRTDSI__OE_SEL0) 
#define knobPanelButton2_PRTDSI__OE_SEL1        (* (reg8 *) knobPanelButton2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define knobPanelButton2_PRTDSI__OUT_SEL0       (* (reg8 *) knobPanelButton2__PRTDSI__OUT_SEL0) 
#define knobPanelButton2_PRTDSI__OUT_SEL1       (* (reg8 *) knobPanelButton2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define knobPanelButton2_PRTDSI__SYNC_OUT       (* (reg8 *) knobPanelButton2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(knobPanelButton2__SIO_CFG)
    #define knobPanelButton2_SIO_HYST_EN        (* (reg8 *) knobPanelButton2__SIO_HYST_EN)
    #define knobPanelButton2_SIO_REG_HIFREQ     (* (reg8 *) knobPanelButton2__SIO_REG_HIFREQ)
    #define knobPanelButton2_SIO_CFG            (* (reg8 *) knobPanelButton2__SIO_CFG)
    #define knobPanelButton2_SIO_DIFF           (* (reg8 *) knobPanelButton2__SIO_DIFF)
#endif /* (knobPanelButton2__SIO_CFG) */

/* Interrupt Registers */
#if defined(knobPanelButton2__INTSTAT)
    #define knobPanelButton2_INTSTAT            (* (reg8 *) knobPanelButton2__INTSTAT)
    #define knobPanelButton2_SNAP               (* (reg8 *) knobPanelButton2__SNAP)
    
	#define knobPanelButton2_0_INTTYPE_REG 		(* (reg8 *) knobPanelButton2__0__INTTYPE)
#endif /* (knobPanelButton2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_knobPanelButton2_H */


/* [] END OF FILE */
