/*******************************************************************************
* File Name: foot3.h  
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

#if !defined(CY_PINS_foot3_H) /* Pins foot3_H */
#define CY_PINS_foot3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "foot3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 foot3__PORT == 15 && ((foot3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    foot3_Write(uint8 value);
void    foot3_SetDriveMode(uint8 mode);
uint8   foot3_ReadDataReg(void);
uint8   foot3_Read(void);
void    foot3_SetInterruptMode(uint16 position, uint16 mode);
uint8   foot3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the foot3_SetDriveMode() function.
     *  @{
     */
        #define foot3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define foot3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define foot3_DM_RES_UP          PIN_DM_RES_UP
        #define foot3_DM_RES_DWN         PIN_DM_RES_DWN
        #define foot3_DM_OD_LO           PIN_DM_OD_LO
        #define foot3_DM_OD_HI           PIN_DM_OD_HI
        #define foot3_DM_STRONG          PIN_DM_STRONG
        #define foot3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define foot3_MASK               foot3__MASK
#define foot3_SHIFT              foot3__SHIFT
#define foot3_WIDTH              1u

/* Interrupt constants */
#if defined(foot3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in foot3_SetInterruptMode() function.
     *  @{
     */
        #define foot3_INTR_NONE      (uint16)(0x0000u)
        #define foot3_INTR_RISING    (uint16)(0x0001u)
        #define foot3_INTR_FALLING   (uint16)(0x0002u)
        #define foot3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define foot3_INTR_MASK      (0x01u) 
#endif /* (foot3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define foot3_PS                     (* (reg8 *) foot3__PS)
/* Data Register */
#define foot3_DR                     (* (reg8 *) foot3__DR)
/* Port Number */
#define foot3_PRT_NUM                (* (reg8 *) foot3__PRT) 
/* Connect to Analog Globals */                                                  
#define foot3_AG                     (* (reg8 *) foot3__AG)                       
/* Analog MUX bux enable */
#define foot3_AMUX                   (* (reg8 *) foot3__AMUX) 
/* Bidirectional Enable */                                                        
#define foot3_BIE                    (* (reg8 *) foot3__BIE)
/* Bit-mask for Aliased Register Access */
#define foot3_BIT_MASK               (* (reg8 *) foot3__BIT_MASK)
/* Bypass Enable */
#define foot3_BYP                    (* (reg8 *) foot3__BYP)
/* Port wide control signals */                                                   
#define foot3_CTL                    (* (reg8 *) foot3__CTL)
/* Drive Modes */
#define foot3_DM0                    (* (reg8 *) foot3__DM0) 
#define foot3_DM1                    (* (reg8 *) foot3__DM1)
#define foot3_DM2                    (* (reg8 *) foot3__DM2) 
/* Input Buffer Disable Override */
#define foot3_INP_DIS                (* (reg8 *) foot3__INP_DIS)
/* LCD Common or Segment Drive */
#define foot3_LCD_COM_SEG            (* (reg8 *) foot3__LCD_COM_SEG)
/* Enable Segment LCD */
#define foot3_LCD_EN                 (* (reg8 *) foot3__LCD_EN)
/* Slew Rate Control */
#define foot3_SLW                    (* (reg8 *) foot3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define foot3_PRTDSI__CAPS_SEL       (* (reg8 *) foot3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define foot3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) foot3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define foot3_PRTDSI__OE_SEL0        (* (reg8 *) foot3__PRTDSI__OE_SEL0) 
#define foot3_PRTDSI__OE_SEL1        (* (reg8 *) foot3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define foot3_PRTDSI__OUT_SEL0       (* (reg8 *) foot3__PRTDSI__OUT_SEL0) 
#define foot3_PRTDSI__OUT_SEL1       (* (reg8 *) foot3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define foot3_PRTDSI__SYNC_OUT       (* (reg8 *) foot3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(foot3__SIO_CFG)
    #define foot3_SIO_HYST_EN        (* (reg8 *) foot3__SIO_HYST_EN)
    #define foot3_SIO_REG_HIFREQ     (* (reg8 *) foot3__SIO_REG_HIFREQ)
    #define foot3_SIO_CFG            (* (reg8 *) foot3__SIO_CFG)
    #define foot3_SIO_DIFF           (* (reg8 *) foot3__SIO_DIFF)
#endif /* (foot3__SIO_CFG) */

/* Interrupt Registers */
#if defined(foot3__INTSTAT)
    #define foot3_INTSTAT            (* (reg8 *) foot3__INTSTAT)
    #define foot3_SNAP               (* (reg8 *) foot3__SNAP)
    
	#define foot3_0_INTTYPE_REG 		(* (reg8 *) foot3__0__INTTYPE)
#endif /* (foot3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_foot3_H */


/* [] END OF FILE */
