/*******************************************************************************
* File Name: neck2_button.h  
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

#if !defined(CY_PINS_neck2_button_H) /* Pins neck2_button_H */
#define CY_PINS_neck2_button_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "neck2_button_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 neck2_button__PORT == 15 && ((neck2_button__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    neck2_button_Write(uint8 value);
void    neck2_button_SetDriveMode(uint8 mode);
uint8   neck2_button_ReadDataReg(void);
uint8   neck2_button_Read(void);
void    neck2_button_SetInterruptMode(uint16 position, uint16 mode);
uint8   neck2_button_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the neck2_button_SetDriveMode() function.
     *  @{
     */
        #define neck2_button_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define neck2_button_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define neck2_button_DM_RES_UP          PIN_DM_RES_UP
        #define neck2_button_DM_RES_DWN         PIN_DM_RES_DWN
        #define neck2_button_DM_OD_LO           PIN_DM_OD_LO
        #define neck2_button_DM_OD_HI           PIN_DM_OD_HI
        #define neck2_button_DM_STRONG          PIN_DM_STRONG
        #define neck2_button_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define neck2_button_MASK               neck2_button__MASK
#define neck2_button_SHIFT              neck2_button__SHIFT
#define neck2_button_WIDTH              1u

/* Interrupt constants */
#if defined(neck2_button__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in neck2_button_SetInterruptMode() function.
     *  @{
     */
        #define neck2_button_INTR_NONE      (uint16)(0x0000u)
        #define neck2_button_INTR_RISING    (uint16)(0x0001u)
        #define neck2_button_INTR_FALLING   (uint16)(0x0002u)
        #define neck2_button_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define neck2_button_INTR_MASK      (0x01u) 
#endif /* (neck2_button__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define neck2_button_PS                     (* (reg8 *) neck2_button__PS)
/* Data Register */
#define neck2_button_DR                     (* (reg8 *) neck2_button__DR)
/* Port Number */
#define neck2_button_PRT_NUM                (* (reg8 *) neck2_button__PRT) 
/* Connect to Analog Globals */                                                  
#define neck2_button_AG                     (* (reg8 *) neck2_button__AG)                       
/* Analog MUX bux enable */
#define neck2_button_AMUX                   (* (reg8 *) neck2_button__AMUX) 
/* Bidirectional Enable */                                                        
#define neck2_button_BIE                    (* (reg8 *) neck2_button__BIE)
/* Bit-mask for Aliased Register Access */
#define neck2_button_BIT_MASK               (* (reg8 *) neck2_button__BIT_MASK)
/* Bypass Enable */
#define neck2_button_BYP                    (* (reg8 *) neck2_button__BYP)
/* Port wide control signals */                                                   
#define neck2_button_CTL                    (* (reg8 *) neck2_button__CTL)
/* Drive Modes */
#define neck2_button_DM0                    (* (reg8 *) neck2_button__DM0) 
#define neck2_button_DM1                    (* (reg8 *) neck2_button__DM1)
#define neck2_button_DM2                    (* (reg8 *) neck2_button__DM2) 
/* Input Buffer Disable Override */
#define neck2_button_INP_DIS                (* (reg8 *) neck2_button__INP_DIS)
/* LCD Common or Segment Drive */
#define neck2_button_LCD_COM_SEG            (* (reg8 *) neck2_button__LCD_COM_SEG)
/* Enable Segment LCD */
#define neck2_button_LCD_EN                 (* (reg8 *) neck2_button__LCD_EN)
/* Slew Rate Control */
#define neck2_button_SLW                    (* (reg8 *) neck2_button__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define neck2_button_PRTDSI__CAPS_SEL       (* (reg8 *) neck2_button__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define neck2_button_PRTDSI__DBL_SYNC_IN    (* (reg8 *) neck2_button__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define neck2_button_PRTDSI__OE_SEL0        (* (reg8 *) neck2_button__PRTDSI__OE_SEL0) 
#define neck2_button_PRTDSI__OE_SEL1        (* (reg8 *) neck2_button__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define neck2_button_PRTDSI__OUT_SEL0       (* (reg8 *) neck2_button__PRTDSI__OUT_SEL0) 
#define neck2_button_PRTDSI__OUT_SEL1       (* (reg8 *) neck2_button__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define neck2_button_PRTDSI__SYNC_OUT       (* (reg8 *) neck2_button__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(neck2_button__SIO_CFG)
    #define neck2_button_SIO_HYST_EN        (* (reg8 *) neck2_button__SIO_HYST_EN)
    #define neck2_button_SIO_REG_HIFREQ     (* (reg8 *) neck2_button__SIO_REG_HIFREQ)
    #define neck2_button_SIO_CFG            (* (reg8 *) neck2_button__SIO_CFG)
    #define neck2_button_SIO_DIFF           (* (reg8 *) neck2_button__SIO_DIFF)
#endif /* (neck2_button__SIO_CFG) */

/* Interrupt Registers */
#if defined(neck2_button__INTSTAT)
    #define neck2_button_INTSTAT            (* (reg8 *) neck2_button__INTSTAT)
    #define neck2_button_SNAP               (* (reg8 *) neck2_button__SNAP)
    
	#define neck2_button_0_INTTYPE_REG 		(* (reg8 *) neck2_button__0__INTTYPE)
#endif /* (neck2_button__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_neck2_button_H */


/* [] END OF FILE */
