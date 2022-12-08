/*******************************************************************************
* File Name: foot1.h  
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

#if !defined(CY_PINS_foot1_H) /* Pins foot1_H */
#define CY_PINS_foot1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "foot1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 foot1__PORT == 15 && ((foot1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    foot1_Write(uint8 value);
void    foot1_SetDriveMode(uint8 mode);
uint8   foot1_ReadDataReg(void);
uint8   foot1_Read(void);
void    foot1_SetInterruptMode(uint16 position, uint16 mode);
uint8   foot1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the foot1_SetDriveMode() function.
     *  @{
     */
        #define foot1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define foot1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define foot1_DM_RES_UP          PIN_DM_RES_UP
        #define foot1_DM_RES_DWN         PIN_DM_RES_DWN
        #define foot1_DM_OD_LO           PIN_DM_OD_LO
        #define foot1_DM_OD_HI           PIN_DM_OD_HI
        #define foot1_DM_STRONG          PIN_DM_STRONG
        #define foot1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define foot1_MASK               foot1__MASK
#define foot1_SHIFT              foot1__SHIFT
#define foot1_WIDTH              1u

/* Interrupt constants */
#if defined(foot1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in foot1_SetInterruptMode() function.
     *  @{
     */
        #define foot1_INTR_NONE      (uint16)(0x0000u)
        #define foot1_INTR_RISING    (uint16)(0x0001u)
        #define foot1_INTR_FALLING   (uint16)(0x0002u)
        #define foot1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define foot1_INTR_MASK      (0x01u) 
#endif /* (foot1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define foot1_PS                     (* (reg8 *) foot1__PS)
/* Data Register */
#define foot1_DR                     (* (reg8 *) foot1__DR)
/* Port Number */
#define foot1_PRT_NUM                (* (reg8 *) foot1__PRT) 
/* Connect to Analog Globals */                                                  
#define foot1_AG                     (* (reg8 *) foot1__AG)                       
/* Analog MUX bux enable */
#define foot1_AMUX                   (* (reg8 *) foot1__AMUX) 
/* Bidirectional Enable */                                                        
#define foot1_BIE                    (* (reg8 *) foot1__BIE)
/* Bit-mask for Aliased Register Access */
#define foot1_BIT_MASK               (* (reg8 *) foot1__BIT_MASK)
/* Bypass Enable */
#define foot1_BYP                    (* (reg8 *) foot1__BYP)
/* Port wide control signals */                                                   
#define foot1_CTL                    (* (reg8 *) foot1__CTL)
/* Drive Modes */
#define foot1_DM0                    (* (reg8 *) foot1__DM0) 
#define foot1_DM1                    (* (reg8 *) foot1__DM1)
#define foot1_DM2                    (* (reg8 *) foot1__DM2) 
/* Input Buffer Disable Override */
#define foot1_INP_DIS                (* (reg8 *) foot1__INP_DIS)
/* LCD Common or Segment Drive */
#define foot1_LCD_COM_SEG            (* (reg8 *) foot1__LCD_COM_SEG)
/* Enable Segment LCD */
#define foot1_LCD_EN                 (* (reg8 *) foot1__LCD_EN)
/* Slew Rate Control */
#define foot1_SLW                    (* (reg8 *) foot1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define foot1_PRTDSI__CAPS_SEL       (* (reg8 *) foot1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define foot1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) foot1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define foot1_PRTDSI__OE_SEL0        (* (reg8 *) foot1__PRTDSI__OE_SEL0) 
#define foot1_PRTDSI__OE_SEL1        (* (reg8 *) foot1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define foot1_PRTDSI__OUT_SEL0       (* (reg8 *) foot1__PRTDSI__OUT_SEL0) 
#define foot1_PRTDSI__OUT_SEL1       (* (reg8 *) foot1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define foot1_PRTDSI__SYNC_OUT       (* (reg8 *) foot1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(foot1__SIO_CFG)
    #define foot1_SIO_HYST_EN        (* (reg8 *) foot1__SIO_HYST_EN)
    #define foot1_SIO_REG_HIFREQ     (* (reg8 *) foot1__SIO_REG_HIFREQ)
    #define foot1_SIO_CFG            (* (reg8 *) foot1__SIO_CFG)
    #define foot1_SIO_DIFF           (* (reg8 *) foot1__SIO_DIFF)
#endif /* (foot1__SIO_CFG) */

/* Interrupt Registers */
#if defined(foot1__INTSTAT)
    #define foot1_INTSTAT            (* (reg8 *) foot1__INTSTAT)
    #define foot1_SNAP               (* (reg8 *) foot1__SNAP)
    
	#define foot1_0_INTTYPE_REG 		(* (reg8 *) foot1__0__INTTYPE)
#endif /* (foot1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_foot1_H */


/* [] END OF FILE */
