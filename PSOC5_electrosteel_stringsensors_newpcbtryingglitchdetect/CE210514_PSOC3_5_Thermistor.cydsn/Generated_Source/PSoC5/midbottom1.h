/*******************************************************************************
* File Name: midbottom1.h  
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

#if !defined(CY_PINS_midbottom1_H) /* Pins midbottom1_H */
#define CY_PINS_midbottom1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "midbottom1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 midbottom1__PORT == 15 && ((midbottom1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    midbottom1_Write(uint8 value);
void    midbottom1_SetDriveMode(uint8 mode);
uint8   midbottom1_ReadDataReg(void);
uint8   midbottom1_Read(void);
void    midbottom1_SetInterruptMode(uint16 position, uint16 mode);
uint8   midbottom1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the midbottom1_SetDriveMode() function.
     *  @{
     */
        #define midbottom1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define midbottom1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define midbottom1_DM_RES_UP          PIN_DM_RES_UP
        #define midbottom1_DM_RES_DWN         PIN_DM_RES_DWN
        #define midbottom1_DM_OD_LO           PIN_DM_OD_LO
        #define midbottom1_DM_OD_HI           PIN_DM_OD_HI
        #define midbottom1_DM_STRONG          PIN_DM_STRONG
        #define midbottom1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define midbottom1_MASK               midbottom1__MASK
#define midbottom1_SHIFT              midbottom1__SHIFT
#define midbottom1_WIDTH              1u

/* Interrupt constants */
#if defined(midbottom1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in midbottom1_SetInterruptMode() function.
     *  @{
     */
        #define midbottom1_INTR_NONE      (uint16)(0x0000u)
        #define midbottom1_INTR_RISING    (uint16)(0x0001u)
        #define midbottom1_INTR_FALLING   (uint16)(0x0002u)
        #define midbottom1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define midbottom1_INTR_MASK      (0x01u) 
#endif /* (midbottom1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define midbottom1_PS                     (* (reg8 *) midbottom1__PS)
/* Data Register */
#define midbottom1_DR                     (* (reg8 *) midbottom1__DR)
/* Port Number */
#define midbottom1_PRT_NUM                (* (reg8 *) midbottom1__PRT) 
/* Connect to Analog Globals */                                                  
#define midbottom1_AG                     (* (reg8 *) midbottom1__AG)                       
/* Analog MUX bux enable */
#define midbottom1_AMUX                   (* (reg8 *) midbottom1__AMUX) 
/* Bidirectional Enable */                                                        
#define midbottom1_BIE                    (* (reg8 *) midbottom1__BIE)
/* Bit-mask for Aliased Register Access */
#define midbottom1_BIT_MASK               (* (reg8 *) midbottom1__BIT_MASK)
/* Bypass Enable */
#define midbottom1_BYP                    (* (reg8 *) midbottom1__BYP)
/* Port wide control signals */                                                   
#define midbottom1_CTL                    (* (reg8 *) midbottom1__CTL)
/* Drive Modes */
#define midbottom1_DM0                    (* (reg8 *) midbottom1__DM0) 
#define midbottom1_DM1                    (* (reg8 *) midbottom1__DM1)
#define midbottom1_DM2                    (* (reg8 *) midbottom1__DM2) 
/* Input Buffer Disable Override */
#define midbottom1_INP_DIS                (* (reg8 *) midbottom1__INP_DIS)
/* LCD Common or Segment Drive */
#define midbottom1_LCD_COM_SEG            (* (reg8 *) midbottom1__LCD_COM_SEG)
/* Enable Segment LCD */
#define midbottom1_LCD_EN                 (* (reg8 *) midbottom1__LCD_EN)
/* Slew Rate Control */
#define midbottom1_SLW                    (* (reg8 *) midbottom1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define midbottom1_PRTDSI__CAPS_SEL       (* (reg8 *) midbottom1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define midbottom1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) midbottom1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define midbottom1_PRTDSI__OE_SEL0        (* (reg8 *) midbottom1__PRTDSI__OE_SEL0) 
#define midbottom1_PRTDSI__OE_SEL1        (* (reg8 *) midbottom1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define midbottom1_PRTDSI__OUT_SEL0       (* (reg8 *) midbottom1__PRTDSI__OUT_SEL0) 
#define midbottom1_PRTDSI__OUT_SEL1       (* (reg8 *) midbottom1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define midbottom1_PRTDSI__SYNC_OUT       (* (reg8 *) midbottom1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(midbottom1__SIO_CFG)
    #define midbottom1_SIO_HYST_EN        (* (reg8 *) midbottom1__SIO_HYST_EN)
    #define midbottom1_SIO_REG_HIFREQ     (* (reg8 *) midbottom1__SIO_REG_HIFREQ)
    #define midbottom1_SIO_CFG            (* (reg8 *) midbottom1__SIO_CFG)
    #define midbottom1_SIO_DIFF           (* (reg8 *) midbottom1__SIO_DIFF)
#endif /* (midbottom1__SIO_CFG) */

/* Interrupt Registers */
#if defined(midbottom1__INTSTAT)
    #define midbottom1_INTSTAT            (* (reg8 *) midbottom1__INTSTAT)
    #define midbottom1_SNAP               (* (reg8 *) midbottom1__SNAP)
    
	#define midbottom1_0_INTTYPE_REG 		(* (reg8 *) midbottom1__0__INTTYPE)
#endif /* (midbottom1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_midbottom1_H */


/* [] END OF FILE */
