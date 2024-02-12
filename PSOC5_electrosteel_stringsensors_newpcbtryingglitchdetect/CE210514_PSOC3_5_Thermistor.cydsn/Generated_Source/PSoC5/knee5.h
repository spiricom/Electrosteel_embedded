/*******************************************************************************
* File Name: knee5.h  
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

#if !defined(CY_PINS_knee5_H) /* Pins knee5_H */
#define CY_PINS_knee5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "knee5_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 knee5__PORT == 15 && ((knee5__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    knee5_Write(uint8 value);
void    knee5_SetDriveMode(uint8 mode);
uint8   knee5_ReadDataReg(void);
uint8   knee5_Read(void);
void    knee5_SetInterruptMode(uint16 position, uint16 mode);
uint8   knee5_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the knee5_SetDriveMode() function.
     *  @{
     */
        #define knee5_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define knee5_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define knee5_DM_RES_UP          PIN_DM_RES_UP
        #define knee5_DM_RES_DWN         PIN_DM_RES_DWN
        #define knee5_DM_OD_LO           PIN_DM_OD_LO
        #define knee5_DM_OD_HI           PIN_DM_OD_HI
        #define knee5_DM_STRONG          PIN_DM_STRONG
        #define knee5_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define knee5_MASK               knee5__MASK
#define knee5_SHIFT              knee5__SHIFT
#define knee5_WIDTH              1u

/* Interrupt constants */
#if defined(knee5__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in knee5_SetInterruptMode() function.
     *  @{
     */
        #define knee5_INTR_NONE      (uint16)(0x0000u)
        #define knee5_INTR_RISING    (uint16)(0x0001u)
        #define knee5_INTR_FALLING   (uint16)(0x0002u)
        #define knee5_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define knee5_INTR_MASK      (0x01u) 
#endif /* (knee5__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define knee5_PS                     (* (reg8 *) knee5__PS)
/* Data Register */
#define knee5_DR                     (* (reg8 *) knee5__DR)
/* Port Number */
#define knee5_PRT_NUM                (* (reg8 *) knee5__PRT) 
/* Connect to Analog Globals */                                                  
#define knee5_AG                     (* (reg8 *) knee5__AG)                       
/* Analog MUX bux enable */
#define knee5_AMUX                   (* (reg8 *) knee5__AMUX) 
/* Bidirectional Enable */                                                        
#define knee5_BIE                    (* (reg8 *) knee5__BIE)
/* Bit-mask for Aliased Register Access */
#define knee5_BIT_MASK               (* (reg8 *) knee5__BIT_MASK)
/* Bypass Enable */
#define knee5_BYP                    (* (reg8 *) knee5__BYP)
/* Port wide control signals */                                                   
#define knee5_CTL                    (* (reg8 *) knee5__CTL)
/* Drive Modes */
#define knee5_DM0                    (* (reg8 *) knee5__DM0) 
#define knee5_DM1                    (* (reg8 *) knee5__DM1)
#define knee5_DM2                    (* (reg8 *) knee5__DM2) 
/* Input Buffer Disable Override */
#define knee5_INP_DIS                (* (reg8 *) knee5__INP_DIS)
/* LCD Common or Segment Drive */
#define knee5_LCD_COM_SEG            (* (reg8 *) knee5__LCD_COM_SEG)
/* Enable Segment LCD */
#define knee5_LCD_EN                 (* (reg8 *) knee5__LCD_EN)
/* Slew Rate Control */
#define knee5_SLW                    (* (reg8 *) knee5__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define knee5_PRTDSI__CAPS_SEL       (* (reg8 *) knee5__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define knee5_PRTDSI__DBL_SYNC_IN    (* (reg8 *) knee5__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define knee5_PRTDSI__OE_SEL0        (* (reg8 *) knee5__PRTDSI__OE_SEL0) 
#define knee5_PRTDSI__OE_SEL1        (* (reg8 *) knee5__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define knee5_PRTDSI__OUT_SEL0       (* (reg8 *) knee5__PRTDSI__OUT_SEL0) 
#define knee5_PRTDSI__OUT_SEL1       (* (reg8 *) knee5__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define knee5_PRTDSI__SYNC_OUT       (* (reg8 *) knee5__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(knee5__SIO_CFG)
    #define knee5_SIO_HYST_EN        (* (reg8 *) knee5__SIO_HYST_EN)
    #define knee5_SIO_REG_HIFREQ     (* (reg8 *) knee5__SIO_REG_HIFREQ)
    #define knee5_SIO_CFG            (* (reg8 *) knee5__SIO_CFG)
    #define knee5_SIO_DIFF           (* (reg8 *) knee5__SIO_DIFF)
#endif /* (knee5__SIO_CFG) */

/* Interrupt Registers */
#if defined(knee5__INTSTAT)
    #define knee5_INTSTAT            (* (reg8 *) knee5__INTSTAT)
    #define knee5_SNAP               (* (reg8 *) knee5__SNAP)
    
	#define knee5_0_INTTYPE_REG 		(* (reg8 *) knee5__0__INTTYPE)
#endif /* (knee5__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_knee5_H */


/* [] END OF FILE */
