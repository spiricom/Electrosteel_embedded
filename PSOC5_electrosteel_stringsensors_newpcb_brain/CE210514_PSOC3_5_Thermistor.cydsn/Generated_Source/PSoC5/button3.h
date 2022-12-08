/*******************************************************************************
* File Name: button3.h  
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

#if !defined(CY_PINS_button3_H) /* Pins button3_H */
#define CY_PINS_button3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "button3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 button3__PORT == 15 && ((button3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    button3_Write(uint8 value);
void    button3_SetDriveMode(uint8 mode);
uint8   button3_ReadDataReg(void);
uint8   button3_Read(void);
void    button3_SetInterruptMode(uint16 position, uint16 mode);
uint8   button3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the button3_SetDriveMode() function.
     *  @{
     */
        #define button3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define button3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define button3_DM_RES_UP          PIN_DM_RES_UP
        #define button3_DM_RES_DWN         PIN_DM_RES_DWN
        #define button3_DM_OD_LO           PIN_DM_OD_LO
        #define button3_DM_OD_HI           PIN_DM_OD_HI
        #define button3_DM_STRONG          PIN_DM_STRONG
        #define button3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define button3_MASK               button3__MASK
#define button3_SHIFT              button3__SHIFT
#define button3_WIDTH              1u

/* Interrupt constants */
#if defined(button3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in button3_SetInterruptMode() function.
     *  @{
     */
        #define button3_INTR_NONE      (uint16)(0x0000u)
        #define button3_INTR_RISING    (uint16)(0x0001u)
        #define button3_INTR_FALLING   (uint16)(0x0002u)
        #define button3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define button3_INTR_MASK      (0x01u) 
#endif /* (button3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define button3_PS                     (* (reg8 *) button3__PS)
/* Data Register */
#define button3_DR                     (* (reg8 *) button3__DR)
/* Port Number */
#define button3_PRT_NUM                (* (reg8 *) button3__PRT) 
/* Connect to Analog Globals */                                                  
#define button3_AG                     (* (reg8 *) button3__AG)                       
/* Analog MUX bux enable */
#define button3_AMUX                   (* (reg8 *) button3__AMUX) 
/* Bidirectional Enable */                                                        
#define button3_BIE                    (* (reg8 *) button3__BIE)
/* Bit-mask for Aliased Register Access */
#define button3_BIT_MASK               (* (reg8 *) button3__BIT_MASK)
/* Bypass Enable */
#define button3_BYP                    (* (reg8 *) button3__BYP)
/* Port wide control signals */                                                   
#define button3_CTL                    (* (reg8 *) button3__CTL)
/* Drive Modes */
#define button3_DM0                    (* (reg8 *) button3__DM0) 
#define button3_DM1                    (* (reg8 *) button3__DM1)
#define button3_DM2                    (* (reg8 *) button3__DM2) 
/* Input Buffer Disable Override */
#define button3_INP_DIS                (* (reg8 *) button3__INP_DIS)
/* LCD Common or Segment Drive */
#define button3_LCD_COM_SEG            (* (reg8 *) button3__LCD_COM_SEG)
/* Enable Segment LCD */
#define button3_LCD_EN                 (* (reg8 *) button3__LCD_EN)
/* Slew Rate Control */
#define button3_SLW                    (* (reg8 *) button3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define button3_PRTDSI__CAPS_SEL       (* (reg8 *) button3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define button3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) button3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define button3_PRTDSI__OE_SEL0        (* (reg8 *) button3__PRTDSI__OE_SEL0) 
#define button3_PRTDSI__OE_SEL1        (* (reg8 *) button3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define button3_PRTDSI__OUT_SEL0       (* (reg8 *) button3__PRTDSI__OUT_SEL0) 
#define button3_PRTDSI__OUT_SEL1       (* (reg8 *) button3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define button3_PRTDSI__SYNC_OUT       (* (reg8 *) button3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(button3__SIO_CFG)
    #define button3_SIO_HYST_EN        (* (reg8 *) button3__SIO_HYST_EN)
    #define button3_SIO_REG_HIFREQ     (* (reg8 *) button3__SIO_REG_HIFREQ)
    #define button3_SIO_CFG            (* (reg8 *) button3__SIO_CFG)
    #define button3_SIO_DIFF           (* (reg8 *) button3__SIO_DIFF)
#endif /* (button3__SIO_CFG) */

/* Interrupt Registers */
#if defined(button3__INTSTAT)
    #define button3_INTSTAT            (* (reg8 *) button3__INTSTAT)
    #define button3_SNAP               (* (reg8 *) button3__SNAP)
    
	#define button3_0_INTTYPE_REG 		(* (reg8 *) button3__0__INTTYPE)
#endif /* (button3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_button3_H */


/* [] END OF FILE */
