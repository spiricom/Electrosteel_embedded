/*******************************************************************************
* File Name: myLed.h  
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

#if !defined(CY_PINS_myLed_H) /* Pins myLed_H */
#define CY_PINS_myLed_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "myLed_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 myLed__PORT == 15 && ((myLed__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    myLed_Write(uint8 value);
void    myLed_SetDriveMode(uint8 mode);
uint8   myLed_ReadDataReg(void);
uint8   myLed_Read(void);
void    myLed_SetInterruptMode(uint16 position, uint16 mode);
uint8   myLed_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the myLed_SetDriveMode() function.
     *  @{
     */
        #define myLed_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define myLed_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define myLed_DM_RES_UP          PIN_DM_RES_UP
        #define myLed_DM_RES_DWN         PIN_DM_RES_DWN
        #define myLed_DM_OD_LO           PIN_DM_OD_LO
        #define myLed_DM_OD_HI           PIN_DM_OD_HI
        #define myLed_DM_STRONG          PIN_DM_STRONG
        #define myLed_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define myLed_MASK               myLed__MASK
#define myLed_SHIFT              myLed__SHIFT
#define myLed_WIDTH              1u

/* Interrupt constants */
#if defined(myLed__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in myLed_SetInterruptMode() function.
     *  @{
     */
        #define myLed_INTR_NONE      (uint16)(0x0000u)
        #define myLed_INTR_RISING    (uint16)(0x0001u)
        #define myLed_INTR_FALLING   (uint16)(0x0002u)
        #define myLed_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define myLed_INTR_MASK      (0x01u) 
#endif /* (myLed__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define myLed_PS                     (* (reg8 *) myLed__PS)
/* Data Register */
#define myLed_DR                     (* (reg8 *) myLed__DR)
/* Port Number */
#define myLed_PRT_NUM                (* (reg8 *) myLed__PRT) 
/* Connect to Analog Globals */                                                  
#define myLed_AG                     (* (reg8 *) myLed__AG)                       
/* Analog MUX bux enable */
#define myLed_AMUX                   (* (reg8 *) myLed__AMUX) 
/* Bidirectional Enable */                                                        
#define myLed_BIE                    (* (reg8 *) myLed__BIE)
/* Bit-mask for Aliased Register Access */
#define myLed_BIT_MASK               (* (reg8 *) myLed__BIT_MASK)
/* Bypass Enable */
#define myLed_BYP                    (* (reg8 *) myLed__BYP)
/* Port wide control signals */                                                   
#define myLed_CTL                    (* (reg8 *) myLed__CTL)
/* Drive Modes */
#define myLed_DM0                    (* (reg8 *) myLed__DM0) 
#define myLed_DM1                    (* (reg8 *) myLed__DM1)
#define myLed_DM2                    (* (reg8 *) myLed__DM2) 
/* Input Buffer Disable Override */
#define myLed_INP_DIS                (* (reg8 *) myLed__INP_DIS)
/* LCD Common or Segment Drive */
#define myLed_LCD_COM_SEG            (* (reg8 *) myLed__LCD_COM_SEG)
/* Enable Segment LCD */
#define myLed_LCD_EN                 (* (reg8 *) myLed__LCD_EN)
/* Slew Rate Control */
#define myLed_SLW                    (* (reg8 *) myLed__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define myLed_PRTDSI__CAPS_SEL       (* (reg8 *) myLed__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define myLed_PRTDSI__DBL_SYNC_IN    (* (reg8 *) myLed__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define myLed_PRTDSI__OE_SEL0        (* (reg8 *) myLed__PRTDSI__OE_SEL0) 
#define myLed_PRTDSI__OE_SEL1        (* (reg8 *) myLed__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define myLed_PRTDSI__OUT_SEL0       (* (reg8 *) myLed__PRTDSI__OUT_SEL0) 
#define myLed_PRTDSI__OUT_SEL1       (* (reg8 *) myLed__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define myLed_PRTDSI__SYNC_OUT       (* (reg8 *) myLed__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(myLed__SIO_CFG)
    #define myLed_SIO_HYST_EN        (* (reg8 *) myLed__SIO_HYST_EN)
    #define myLed_SIO_REG_HIFREQ     (* (reg8 *) myLed__SIO_REG_HIFREQ)
    #define myLed_SIO_CFG            (* (reg8 *) myLed__SIO_CFG)
    #define myLed_SIO_DIFF           (* (reg8 *) myLed__SIO_DIFF)
#endif /* (myLed__SIO_CFG) */

/* Interrupt Registers */
#if defined(myLed__INTSTAT)
    #define myLed_INTSTAT            (* (reg8 *) myLed__INTSTAT)
    #define myLed_SNAP               (* (reg8 *) myLed__SNAP)
    
	#define myLed_0_INTTYPE_REG 		(* (reg8 *) myLed__0__INTTYPE)
#endif /* (myLed__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_myLed_H */


/* [] END OF FILE */
