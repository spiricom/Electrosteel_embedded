/*******************************************************************************
* File Name: button2.h  
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

#if !defined(CY_PINS_button2_H) /* Pins button2_H */
#define CY_PINS_button2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "button2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 button2__PORT == 15 && ((button2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    button2_Write(uint8 value);
void    button2_SetDriveMode(uint8 mode);
uint8   button2_ReadDataReg(void);
uint8   button2_Read(void);
void    button2_SetInterruptMode(uint16 position, uint16 mode);
uint8   button2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the button2_SetDriveMode() function.
     *  @{
     */
        #define button2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define button2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define button2_DM_RES_UP          PIN_DM_RES_UP
        #define button2_DM_RES_DWN         PIN_DM_RES_DWN
        #define button2_DM_OD_LO           PIN_DM_OD_LO
        #define button2_DM_OD_HI           PIN_DM_OD_HI
        #define button2_DM_STRONG          PIN_DM_STRONG
        #define button2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define button2_MASK               button2__MASK
#define button2_SHIFT              button2__SHIFT
#define button2_WIDTH              1u

/* Interrupt constants */
#if defined(button2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in button2_SetInterruptMode() function.
     *  @{
     */
        #define button2_INTR_NONE      (uint16)(0x0000u)
        #define button2_INTR_RISING    (uint16)(0x0001u)
        #define button2_INTR_FALLING   (uint16)(0x0002u)
        #define button2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define button2_INTR_MASK      (0x01u) 
#endif /* (button2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define button2_PS                     (* (reg8 *) button2__PS)
/* Data Register */
#define button2_DR                     (* (reg8 *) button2__DR)
/* Port Number */
#define button2_PRT_NUM                (* (reg8 *) button2__PRT) 
/* Connect to Analog Globals */                                                  
#define button2_AG                     (* (reg8 *) button2__AG)                       
/* Analog MUX bux enable */
#define button2_AMUX                   (* (reg8 *) button2__AMUX) 
/* Bidirectional Enable */                                                        
#define button2_BIE                    (* (reg8 *) button2__BIE)
/* Bit-mask for Aliased Register Access */
#define button2_BIT_MASK               (* (reg8 *) button2__BIT_MASK)
/* Bypass Enable */
#define button2_BYP                    (* (reg8 *) button2__BYP)
/* Port wide control signals */                                                   
#define button2_CTL                    (* (reg8 *) button2__CTL)
/* Drive Modes */
#define button2_DM0                    (* (reg8 *) button2__DM0) 
#define button2_DM1                    (* (reg8 *) button2__DM1)
#define button2_DM2                    (* (reg8 *) button2__DM2) 
/* Input Buffer Disable Override */
#define button2_INP_DIS                (* (reg8 *) button2__INP_DIS)
/* LCD Common or Segment Drive */
#define button2_LCD_COM_SEG            (* (reg8 *) button2__LCD_COM_SEG)
/* Enable Segment LCD */
#define button2_LCD_EN                 (* (reg8 *) button2__LCD_EN)
/* Slew Rate Control */
#define button2_SLW                    (* (reg8 *) button2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define button2_PRTDSI__CAPS_SEL       (* (reg8 *) button2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define button2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) button2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define button2_PRTDSI__OE_SEL0        (* (reg8 *) button2__PRTDSI__OE_SEL0) 
#define button2_PRTDSI__OE_SEL1        (* (reg8 *) button2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define button2_PRTDSI__OUT_SEL0       (* (reg8 *) button2__PRTDSI__OUT_SEL0) 
#define button2_PRTDSI__OUT_SEL1       (* (reg8 *) button2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define button2_PRTDSI__SYNC_OUT       (* (reg8 *) button2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(button2__SIO_CFG)
    #define button2_SIO_HYST_EN        (* (reg8 *) button2__SIO_HYST_EN)
    #define button2_SIO_REG_HIFREQ     (* (reg8 *) button2__SIO_REG_HIFREQ)
    #define button2_SIO_CFG            (* (reg8 *) button2__SIO_CFG)
    #define button2_SIO_DIFF           (* (reg8 *) button2__SIO_DIFF)
#endif /* (button2__SIO_CFG) */

/* Interrupt Registers */
#if defined(button2__INTSTAT)
    #define button2_INTSTAT            (* (reg8 *) button2__INTSTAT)
    #define button2_SNAP               (* (reg8 *) button2__SNAP)
    
	#define button2_0_INTTYPE_REG 		(* (reg8 *) button2__0__INTTYPE)
#endif /* (button2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_button2_H */


/* [] END OF FILE */
