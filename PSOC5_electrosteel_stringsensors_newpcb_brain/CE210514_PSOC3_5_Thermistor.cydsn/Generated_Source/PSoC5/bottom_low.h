/*******************************************************************************
* File Name: bottom_low.h  
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

#if !defined(CY_PINS_bottom_low_H) /* Pins bottom_low_H */
#define CY_PINS_bottom_low_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "bottom_low_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 bottom_low__PORT == 15 && ((bottom_low__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    bottom_low_Write(uint8 value);
void    bottom_low_SetDriveMode(uint8 mode);
uint8   bottom_low_ReadDataReg(void);
uint8   bottom_low_Read(void);
void    bottom_low_SetInterruptMode(uint16 position, uint16 mode);
uint8   bottom_low_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the bottom_low_SetDriveMode() function.
     *  @{
     */
        #define bottom_low_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define bottom_low_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define bottom_low_DM_RES_UP          PIN_DM_RES_UP
        #define bottom_low_DM_RES_DWN         PIN_DM_RES_DWN
        #define bottom_low_DM_OD_LO           PIN_DM_OD_LO
        #define bottom_low_DM_OD_HI           PIN_DM_OD_HI
        #define bottom_low_DM_STRONG          PIN_DM_STRONG
        #define bottom_low_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define bottom_low_MASK               bottom_low__MASK
#define bottom_low_SHIFT              bottom_low__SHIFT
#define bottom_low_WIDTH              1u

/* Interrupt constants */
#if defined(bottom_low__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in bottom_low_SetInterruptMode() function.
     *  @{
     */
        #define bottom_low_INTR_NONE      (uint16)(0x0000u)
        #define bottom_low_INTR_RISING    (uint16)(0x0001u)
        #define bottom_low_INTR_FALLING   (uint16)(0x0002u)
        #define bottom_low_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define bottom_low_INTR_MASK      (0x01u) 
#endif /* (bottom_low__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define bottom_low_PS                     (* (reg8 *) bottom_low__PS)
/* Data Register */
#define bottom_low_DR                     (* (reg8 *) bottom_low__DR)
/* Port Number */
#define bottom_low_PRT_NUM                (* (reg8 *) bottom_low__PRT) 
/* Connect to Analog Globals */                                                  
#define bottom_low_AG                     (* (reg8 *) bottom_low__AG)                       
/* Analog MUX bux enable */
#define bottom_low_AMUX                   (* (reg8 *) bottom_low__AMUX) 
/* Bidirectional Enable */                                                        
#define bottom_low_BIE                    (* (reg8 *) bottom_low__BIE)
/* Bit-mask for Aliased Register Access */
#define bottom_low_BIT_MASK               (* (reg8 *) bottom_low__BIT_MASK)
/* Bypass Enable */
#define bottom_low_BYP                    (* (reg8 *) bottom_low__BYP)
/* Port wide control signals */                                                   
#define bottom_low_CTL                    (* (reg8 *) bottom_low__CTL)
/* Drive Modes */
#define bottom_low_DM0                    (* (reg8 *) bottom_low__DM0) 
#define bottom_low_DM1                    (* (reg8 *) bottom_low__DM1)
#define bottom_low_DM2                    (* (reg8 *) bottom_low__DM2) 
/* Input Buffer Disable Override */
#define bottom_low_INP_DIS                (* (reg8 *) bottom_low__INP_DIS)
/* LCD Common or Segment Drive */
#define bottom_low_LCD_COM_SEG            (* (reg8 *) bottom_low__LCD_COM_SEG)
/* Enable Segment LCD */
#define bottom_low_LCD_EN                 (* (reg8 *) bottom_low__LCD_EN)
/* Slew Rate Control */
#define bottom_low_SLW                    (* (reg8 *) bottom_low__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define bottom_low_PRTDSI__CAPS_SEL       (* (reg8 *) bottom_low__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define bottom_low_PRTDSI__DBL_SYNC_IN    (* (reg8 *) bottom_low__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define bottom_low_PRTDSI__OE_SEL0        (* (reg8 *) bottom_low__PRTDSI__OE_SEL0) 
#define bottom_low_PRTDSI__OE_SEL1        (* (reg8 *) bottom_low__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define bottom_low_PRTDSI__OUT_SEL0       (* (reg8 *) bottom_low__PRTDSI__OUT_SEL0) 
#define bottom_low_PRTDSI__OUT_SEL1       (* (reg8 *) bottom_low__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define bottom_low_PRTDSI__SYNC_OUT       (* (reg8 *) bottom_low__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(bottom_low__SIO_CFG)
    #define bottom_low_SIO_HYST_EN        (* (reg8 *) bottom_low__SIO_HYST_EN)
    #define bottom_low_SIO_REG_HIFREQ     (* (reg8 *) bottom_low__SIO_REG_HIFREQ)
    #define bottom_low_SIO_CFG            (* (reg8 *) bottom_low__SIO_CFG)
    #define bottom_low_SIO_DIFF           (* (reg8 *) bottom_low__SIO_DIFF)
#endif /* (bottom_low__SIO_CFG) */

/* Interrupt Registers */
#if defined(bottom_low__INTSTAT)
    #define bottom_low_INTSTAT            (* (reg8 *) bottom_low__INTSTAT)
    #define bottom_low_SNAP               (* (reg8 *) bottom_low__SNAP)
    
	#define bottom_low_0_INTTYPE_REG 		(* (reg8 *) bottom_low__0__INTTYPE)
#endif /* (bottom_low__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_bottom_low_H */


/* [] END OF FILE */
