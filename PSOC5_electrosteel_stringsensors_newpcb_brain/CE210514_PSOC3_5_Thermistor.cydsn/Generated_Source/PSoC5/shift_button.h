/*******************************************************************************
* File Name: shift_button.h  
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

#if !defined(CY_PINS_shift_button_H) /* Pins shift_button_H */
#define CY_PINS_shift_button_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "shift_button_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 shift_button__PORT == 15 && ((shift_button__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    shift_button_Write(uint8 value);
void    shift_button_SetDriveMode(uint8 mode);
uint8   shift_button_ReadDataReg(void);
uint8   shift_button_Read(void);
void    shift_button_SetInterruptMode(uint16 position, uint16 mode);
uint8   shift_button_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the shift_button_SetDriveMode() function.
     *  @{
     */
        #define shift_button_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define shift_button_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define shift_button_DM_RES_UP          PIN_DM_RES_UP
        #define shift_button_DM_RES_DWN         PIN_DM_RES_DWN
        #define shift_button_DM_OD_LO           PIN_DM_OD_LO
        #define shift_button_DM_OD_HI           PIN_DM_OD_HI
        #define shift_button_DM_STRONG          PIN_DM_STRONG
        #define shift_button_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define shift_button_MASK               shift_button__MASK
#define shift_button_SHIFT              shift_button__SHIFT
#define shift_button_WIDTH              1u

/* Interrupt constants */
#if defined(shift_button__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in shift_button_SetInterruptMode() function.
     *  @{
     */
        #define shift_button_INTR_NONE      (uint16)(0x0000u)
        #define shift_button_INTR_RISING    (uint16)(0x0001u)
        #define shift_button_INTR_FALLING   (uint16)(0x0002u)
        #define shift_button_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define shift_button_INTR_MASK      (0x01u) 
#endif /* (shift_button__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define shift_button_PS                     (* (reg8 *) shift_button__PS)
/* Data Register */
#define shift_button_DR                     (* (reg8 *) shift_button__DR)
/* Port Number */
#define shift_button_PRT_NUM                (* (reg8 *) shift_button__PRT) 
/* Connect to Analog Globals */                                                  
#define shift_button_AG                     (* (reg8 *) shift_button__AG)                       
/* Analog MUX bux enable */
#define shift_button_AMUX                   (* (reg8 *) shift_button__AMUX) 
/* Bidirectional Enable */                                                        
#define shift_button_BIE                    (* (reg8 *) shift_button__BIE)
/* Bit-mask for Aliased Register Access */
#define shift_button_BIT_MASK               (* (reg8 *) shift_button__BIT_MASK)
/* Bypass Enable */
#define shift_button_BYP                    (* (reg8 *) shift_button__BYP)
/* Port wide control signals */                                                   
#define shift_button_CTL                    (* (reg8 *) shift_button__CTL)
/* Drive Modes */
#define shift_button_DM0                    (* (reg8 *) shift_button__DM0) 
#define shift_button_DM1                    (* (reg8 *) shift_button__DM1)
#define shift_button_DM2                    (* (reg8 *) shift_button__DM2) 
/* Input Buffer Disable Override */
#define shift_button_INP_DIS                (* (reg8 *) shift_button__INP_DIS)
/* LCD Common or Segment Drive */
#define shift_button_LCD_COM_SEG            (* (reg8 *) shift_button__LCD_COM_SEG)
/* Enable Segment LCD */
#define shift_button_LCD_EN                 (* (reg8 *) shift_button__LCD_EN)
/* Slew Rate Control */
#define shift_button_SLW                    (* (reg8 *) shift_button__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define shift_button_PRTDSI__CAPS_SEL       (* (reg8 *) shift_button__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define shift_button_PRTDSI__DBL_SYNC_IN    (* (reg8 *) shift_button__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define shift_button_PRTDSI__OE_SEL0        (* (reg8 *) shift_button__PRTDSI__OE_SEL0) 
#define shift_button_PRTDSI__OE_SEL1        (* (reg8 *) shift_button__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define shift_button_PRTDSI__OUT_SEL0       (* (reg8 *) shift_button__PRTDSI__OUT_SEL0) 
#define shift_button_PRTDSI__OUT_SEL1       (* (reg8 *) shift_button__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define shift_button_PRTDSI__SYNC_OUT       (* (reg8 *) shift_button__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(shift_button__SIO_CFG)
    #define shift_button_SIO_HYST_EN        (* (reg8 *) shift_button__SIO_HYST_EN)
    #define shift_button_SIO_REG_HIFREQ     (* (reg8 *) shift_button__SIO_REG_HIFREQ)
    #define shift_button_SIO_CFG            (* (reg8 *) shift_button__SIO_CFG)
    #define shift_button_SIO_DIFF           (* (reg8 *) shift_button__SIO_DIFF)
#endif /* (shift_button__SIO_CFG) */

/* Interrupt Registers */
#if defined(shift_button__INTSTAT)
    #define shift_button_INTSTAT            (* (reg8 *) shift_button__INTSTAT)
    #define shift_button_SNAP               (* (reg8 *) shift_button__SNAP)
    
	#define shift_button_0_INTTYPE_REG 		(* (reg8 *) shift_button__0__INTTYPE)
#endif /* (shift_button__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_shift_button_H */


/* [] END OF FILE */
