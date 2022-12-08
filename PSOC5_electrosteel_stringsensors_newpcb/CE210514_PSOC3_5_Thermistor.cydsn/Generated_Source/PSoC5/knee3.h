/*******************************************************************************
* File Name: knee3.h  
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

#if !defined(CY_PINS_knee3_H) /* Pins knee3_H */
#define CY_PINS_knee3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "knee3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 knee3__PORT == 15 && ((knee3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    knee3_Write(uint8 value);
void    knee3_SetDriveMode(uint8 mode);
uint8   knee3_ReadDataReg(void);
uint8   knee3_Read(void);
void    knee3_SetInterruptMode(uint16 position, uint16 mode);
uint8   knee3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the knee3_SetDriveMode() function.
     *  @{
     */
        #define knee3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define knee3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define knee3_DM_RES_UP          PIN_DM_RES_UP
        #define knee3_DM_RES_DWN         PIN_DM_RES_DWN
        #define knee3_DM_OD_LO           PIN_DM_OD_LO
        #define knee3_DM_OD_HI           PIN_DM_OD_HI
        #define knee3_DM_STRONG          PIN_DM_STRONG
        #define knee3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define knee3_MASK               knee3__MASK
#define knee3_SHIFT              knee3__SHIFT
#define knee3_WIDTH              1u

/* Interrupt constants */
#if defined(knee3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in knee3_SetInterruptMode() function.
     *  @{
     */
        #define knee3_INTR_NONE      (uint16)(0x0000u)
        #define knee3_INTR_RISING    (uint16)(0x0001u)
        #define knee3_INTR_FALLING   (uint16)(0x0002u)
        #define knee3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define knee3_INTR_MASK      (0x01u) 
#endif /* (knee3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define knee3_PS                     (* (reg8 *) knee3__PS)
/* Data Register */
#define knee3_DR                     (* (reg8 *) knee3__DR)
/* Port Number */
#define knee3_PRT_NUM                (* (reg8 *) knee3__PRT) 
/* Connect to Analog Globals */                                                  
#define knee3_AG                     (* (reg8 *) knee3__AG)                       
/* Analog MUX bux enable */
#define knee3_AMUX                   (* (reg8 *) knee3__AMUX) 
/* Bidirectional Enable */                                                        
#define knee3_BIE                    (* (reg8 *) knee3__BIE)
/* Bit-mask for Aliased Register Access */
#define knee3_BIT_MASK               (* (reg8 *) knee3__BIT_MASK)
/* Bypass Enable */
#define knee3_BYP                    (* (reg8 *) knee3__BYP)
/* Port wide control signals */                                                   
#define knee3_CTL                    (* (reg8 *) knee3__CTL)
/* Drive Modes */
#define knee3_DM0                    (* (reg8 *) knee3__DM0) 
#define knee3_DM1                    (* (reg8 *) knee3__DM1)
#define knee3_DM2                    (* (reg8 *) knee3__DM2) 
/* Input Buffer Disable Override */
#define knee3_INP_DIS                (* (reg8 *) knee3__INP_DIS)
/* LCD Common or Segment Drive */
#define knee3_LCD_COM_SEG            (* (reg8 *) knee3__LCD_COM_SEG)
/* Enable Segment LCD */
#define knee3_LCD_EN                 (* (reg8 *) knee3__LCD_EN)
/* Slew Rate Control */
#define knee3_SLW                    (* (reg8 *) knee3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define knee3_PRTDSI__CAPS_SEL       (* (reg8 *) knee3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define knee3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) knee3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define knee3_PRTDSI__OE_SEL0        (* (reg8 *) knee3__PRTDSI__OE_SEL0) 
#define knee3_PRTDSI__OE_SEL1        (* (reg8 *) knee3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define knee3_PRTDSI__OUT_SEL0       (* (reg8 *) knee3__PRTDSI__OUT_SEL0) 
#define knee3_PRTDSI__OUT_SEL1       (* (reg8 *) knee3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define knee3_PRTDSI__SYNC_OUT       (* (reg8 *) knee3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(knee3__SIO_CFG)
    #define knee3_SIO_HYST_EN        (* (reg8 *) knee3__SIO_HYST_EN)
    #define knee3_SIO_REG_HIFREQ     (* (reg8 *) knee3__SIO_REG_HIFREQ)
    #define knee3_SIO_CFG            (* (reg8 *) knee3__SIO_CFG)
    #define knee3_SIO_DIFF           (* (reg8 *) knee3__SIO_DIFF)
#endif /* (knee3__SIO_CFG) */

/* Interrupt Registers */
#if defined(knee3__INTSTAT)
    #define knee3_INTSTAT            (* (reg8 *) knee3__INTSTAT)
    #define knee3_SNAP               (* (reg8 *) knee3__SNAP)
    
	#define knee3_0_INTTYPE_REG 		(* (reg8 *) knee3__0__INTTYPE)
#endif /* (knee3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_knee3_H */


/* [] END OF FILE */
