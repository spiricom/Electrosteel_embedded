/*******************************************************************************
* File Name: top_high.h  
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

#if !defined(CY_PINS_top_high_H) /* Pins top_high_H */
#define CY_PINS_top_high_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "top_high_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 top_high__PORT == 15 && ((top_high__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    top_high_Write(uint8 value);
void    top_high_SetDriveMode(uint8 mode);
uint8   top_high_ReadDataReg(void);
uint8   top_high_Read(void);
void    top_high_SetInterruptMode(uint16 position, uint16 mode);
uint8   top_high_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the top_high_SetDriveMode() function.
     *  @{
     */
        #define top_high_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define top_high_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define top_high_DM_RES_UP          PIN_DM_RES_UP
        #define top_high_DM_RES_DWN         PIN_DM_RES_DWN
        #define top_high_DM_OD_LO           PIN_DM_OD_LO
        #define top_high_DM_OD_HI           PIN_DM_OD_HI
        #define top_high_DM_STRONG          PIN_DM_STRONG
        #define top_high_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define top_high_MASK               top_high__MASK
#define top_high_SHIFT              top_high__SHIFT
#define top_high_WIDTH              1u

/* Interrupt constants */
#if defined(top_high__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in top_high_SetInterruptMode() function.
     *  @{
     */
        #define top_high_INTR_NONE      (uint16)(0x0000u)
        #define top_high_INTR_RISING    (uint16)(0x0001u)
        #define top_high_INTR_FALLING   (uint16)(0x0002u)
        #define top_high_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define top_high_INTR_MASK      (0x01u) 
#endif /* (top_high__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define top_high_PS                     (* (reg8 *) top_high__PS)
/* Data Register */
#define top_high_DR                     (* (reg8 *) top_high__DR)
/* Port Number */
#define top_high_PRT_NUM                (* (reg8 *) top_high__PRT) 
/* Connect to Analog Globals */                                                  
#define top_high_AG                     (* (reg8 *) top_high__AG)                       
/* Analog MUX bux enable */
#define top_high_AMUX                   (* (reg8 *) top_high__AMUX) 
/* Bidirectional Enable */                                                        
#define top_high_BIE                    (* (reg8 *) top_high__BIE)
/* Bit-mask for Aliased Register Access */
#define top_high_BIT_MASK               (* (reg8 *) top_high__BIT_MASK)
/* Bypass Enable */
#define top_high_BYP                    (* (reg8 *) top_high__BYP)
/* Port wide control signals */                                                   
#define top_high_CTL                    (* (reg8 *) top_high__CTL)
/* Drive Modes */
#define top_high_DM0                    (* (reg8 *) top_high__DM0) 
#define top_high_DM1                    (* (reg8 *) top_high__DM1)
#define top_high_DM2                    (* (reg8 *) top_high__DM2) 
/* Input Buffer Disable Override */
#define top_high_INP_DIS                (* (reg8 *) top_high__INP_DIS)
/* LCD Common or Segment Drive */
#define top_high_LCD_COM_SEG            (* (reg8 *) top_high__LCD_COM_SEG)
/* Enable Segment LCD */
#define top_high_LCD_EN                 (* (reg8 *) top_high__LCD_EN)
/* Slew Rate Control */
#define top_high_SLW                    (* (reg8 *) top_high__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define top_high_PRTDSI__CAPS_SEL       (* (reg8 *) top_high__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define top_high_PRTDSI__DBL_SYNC_IN    (* (reg8 *) top_high__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define top_high_PRTDSI__OE_SEL0        (* (reg8 *) top_high__PRTDSI__OE_SEL0) 
#define top_high_PRTDSI__OE_SEL1        (* (reg8 *) top_high__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define top_high_PRTDSI__OUT_SEL0       (* (reg8 *) top_high__PRTDSI__OUT_SEL0) 
#define top_high_PRTDSI__OUT_SEL1       (* (reg8 *) top_high__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define top_high_PRTDSI__SYNC_OUT       (* (reg8 *) top_high__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(top_high__SIO_CFG)
    #define top_high_SIO_HYST_EN        (* (reg8 *) top_high__SIO_HYST_EN)
    #define top_high_SIO_REG_HIFREQ     (* (reg8 *) top_high__SIO_REG_HIFREQ)
    #define top_high_SIO_CFG            (* (reg8 *) top_high__SIO_CFG)
    #define top_high_SIO_DIFF           (* (reg8 *) top_high__SIO_DIFF)
#endif /* (top_high__SIO_CFG) */

/* Interrupt Registers */
#if defined(top_high__INTSTAT)
    #define top_high_INTSTAT            (* (reg8 *) top_high__INTSTAT)
    #define top_high_SNAP               (* (reg8 *) top_high__SNAP)
    
	#define top_high_0_INTTYPE_REG 		(* (reg8 *) top_high__0__INTTYPE)
#endif /* (top_high__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_top_high_H */


/* [] END OF FILE */
