/*******************************************************************************
* File Name: button1.h  
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

#if !defined(CY_PINS_button1_H) /* Pins button1_H */
#define CY_PINS_button1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "button1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 button1__PORT == 15 && ((button1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    button1_Write(uint8 value);
void    button1_SetDriveMode(uint8 mode);
uint8   button1_ReadDataReg(void);
uint8   button1_Read(void);
void    button1_SetInterruptMode(uint16 position, uint16 mode);
uint8   button1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the button1_SetDriveMode() function.
     *  @{
     */
        #define button1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define button1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define button1_DM_RES_UP          PIN_DM_RES_UP
        #define button1_DM_RES_DWN         PIN_DM_RES_DWN
        #define button1_DM_OD_LO           PIN_DM_OD_LO
        #define button1_DM_OD_HI           PIN_DM_OD_HI
        #define button1_DM_STRONG          PIN_DM_STRONG
        #define button1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define button1_MASK               button1__MASK
#define button1_SHIFT              button1__SHIFT
#define button1_WIDTH              1u

/* Interrupt constants */
#if defined(button1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in button1_SetInterruptMode() function.
     *  @{
     */
        #define button1_INTR_NONE      (uint16)(0x0000u)
        #define button1_INTR_RISING    (uint16)(0x0001u)
        #define button1_INTR_FALLING   (uint16)(0x0002u)
        #define button1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define button1_INTR_MASK      (0x01u) 
#endif /* (button1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define button1_PS                     (* (reg8 *) button1__PS)
/* Data Register */
#define button1_DR                     (* (reg8 *) button1__DR)
/* Port Number */
#define button1_PRT_NUM                (* (reg8 *) button1__PRT) 
/* Connect to Analog Globals */                                                  
#define button1_AG                     (* (reg8 *) button1__AG)                       
/* Analog MUX bux enable */
#define button1_AMUX                   (* (reg8 *) button1__AMUX) 
/* Bidirectional Enable */                                                        
#define button1_BIE                    (* (reg8 *) button1__BIE)
/* Bit-mask for Aliased Register Access */
#define button1_BIT_MASK               (* (reg8 *) button1__BIT_MASK)
/* Bypass Enable */
#define button1_BYP                    (* (reg8 *) button1__BYP)
/* Port wide control signals */                                                   
#define button1_CTL                    (* (reg8 *) button1__CTL)
/* Drive Modes */
#define button1_DM0                    (* (reg8 *) button1__DM0) 
#define button1_DM1                    (* (reg8 *) button1__DM1)
#define button1_DM2                    (* (reg8 *) button1__DM2) 
/* Input Buffer Disable Override */
#define button1_INP_DIS                (* (reg8 *) button1__INP_DIS)
/* LCD Common or Segment Drive */
#define button1_LCD_COM_SEG            (* (reg8 *) button1__LCD_COM_SEG)
/* Enable Segment LCD */
#define button1_LCD_EN                 (* (reg8 *) button1__LCD_EN)
/* Slew Rate Control */
#define button1_SLW                    (* (reg8 *) button1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define button1_PRTDSI__CAPS_SEL       (* (reg8 *) button1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define button1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) button1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define button1_PRTDSI__OE_SEL0        (* (reg8 *) button1__PRTDSI__OE_SEL0) 
#define button1_PRTDSI__OE_SEL1        (* (reg8 *) button1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define button1_PRTDSI__OUT_SEL0       (* (reg8 *) button1__PRTDSI__OUT_SEL0) 
#define button1_PRTDSI__OUT_SEL1       (* (reg8 *) button1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define button1_PRTDSI__SYNC_OUT       (* (reg8 *) button1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(button1__SIO_CFG)
    #define button1_SIO_HYST_EN        (* (reg8 *) button1__SIO_HYST_EN)
    #define button1_SIO_REG_HIFREQ     (* (reg8 *) button1__SIO_REG_HIFREQ)
    #define button1_SIO_CFG            (* (reg8 *) button1__SIO_CFG)
    #define button1_SIO_DIFF           (* (reg8 *) button1__SIO_DIFF)
#endif /* (button1__SIO_CFG) */

/* Interrupt Registers */
#if defined(button1__INTSTAT)
    #define button1_INTSTAT            (* (reg8 *) button1__INTSTAT)
    #define button1_SNAP               (* (reg8 *) button1__SNAP)
    
	#define button1_0_INTTYPE_REG 		(* (reg8 *) button1__0__INTTYPE)
#endif /* (button1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_button1_H */


/* [] END OF FILE */
