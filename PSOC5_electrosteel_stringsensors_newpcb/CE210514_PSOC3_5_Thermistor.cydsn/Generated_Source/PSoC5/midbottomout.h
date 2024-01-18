/*******************************************************************************
* File Name: midbottomout.h  
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

#if !defined(CY_PINS_midbottomout_H) /* Pins midbottomout_H */
#define CY_PINS_midbottomout_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "midbottomout_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 midbottomout__PORT == 15 && ((midbottomout__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    midbottomout_Write(uint8 value);
void    midbottomout_SetDriveMode(uint8 mode);
uint8   midbottomout_ReadDataReg(void);
uint8   midbottomout_Read(void);
void    midbottomout_SetInterruptMode(uint16 position, uint16 mode);
uint8   midbottomout_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the midbottomout_SetDriveMode() function.
     *  @{
     */
        #define midbottomout_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define midbottomout_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define midbottomout_DM_RES_UP          PIN_DM_RES_UP
        #define midbottomout_DM_RES_DWN         PIN_DM_RES_DWN
        #define midbottomout_DM_OD_LO           PIN_DM_OD_LO
        #define midbottomout_DM_OD_HI           PIN_DM_OD_HI
        #define midbottomout_DM_STRONG          PIN_DM_STRONG
        #define midbottomout_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define midbottomout_MASK               midbottomout__MASK
#define midbottomout_SHIFT              midbottomout__SHIFT
#define midbottomout_WIDTH              1u

/* Interrupt constants */
#if defined(midbottomout__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in midbottomout_SetInterruptMode() function.
     *  @{
     */
        #define midbottomout_INTR_NONE      (uint16)(0x0000u)
        #define midbottomout_INTR_RISING    (uint16)(0x0001u)
        #define midbottomout_INTR_FALLING   (uint16)(0x0002u)
        #define midbottomout_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define midbottomout_INTR_MASK      (0x01u) 
#endif /* (midbottomout__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define midbottomout_PS                     (* (reg8 *) midbottomout__PS)
/* Data Register */
#define midbottomout_DR                     (* (reg8 *) midbottomout__DR)
/* Port Number */
#define midbottomout_PRT_NUM                (* (reg8 *) midbottomout__PRT) 
/* Connect to Analog Globals */                                                  
#define midbottomout_AG                     (* (reg8 *) midbottomout__AG)                       
/* Analog MUX bux enable */
#define midbottomout_AMUX                   (* (reg8 *) midbottomout__AMUX) 
/* Bidirectional Enable */                                                        
#define midbottomout_BIE                    (* (reg8 *) midbottomout__BIE)
/* Bit-mask for Aliased Register Access */
#define midbottomout_BIT_MASK               (* (reg8 *) midbottomout__BIT_MASK)
/* Bypass Enable */
#define midbottomout_BYP                    (* (reg8 *) midbottomout__BYP)
/* Port wide control signals */                                                   
#define midbottomout_CTL                    (* (reg8 *) midbottomout__CTL)
/* Drive Modes */
#define midbottomout_DM0                    (* (reg8 *) midbottomout__DM0) 
#define midbottomout_DM1                    (* (reg8 *) midbottomout__DM1)
#define midbottomout_DM2                    (* (reg8 *) midbottomout__DM2) 
/* Input Buffer Disable Override */
#define midbottomout_INP_DIS                (* (reg8 *) midbottomout__INP_DIS)
/* LCD Common or Segment Drive */
#define midbottomout_LCD_COM_SEG            (* (reg8 *) midbottomout__LCD_COM_SEG)
/* Enable Segment LCD */
#define midbottomout_LCD_EN                 (* (reg8 *) midbottomout__LCD_EN)
/* Slew Rate Control */
#define midbottomout_SLW                    (* (reg8 *) midbottomout__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define midbottomout_PRTDSI__CAPS_SEL       (* (reg8 *) midbottomout__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define midbottomout_PRTDSI__DBL_SYNC_IN    (* (reg8 *) midbottomout__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define midbottomout_PRTDSI__OE_SEL0        (* (reg8 *) midbottomout__PRTDSI__OE_SEL0) 
#define midbottomout_PRTDSI__OE_SEL1        (* (reg8 *) midbottomout__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define midbottomout_PRTDSI__OUT_SEL0       (* (reg8 *) midbottomout__PRTDSI__OUT_SEL0) 
#define midbottomout_PRTDSI__OUT_SEL1       (* (reg8 *) midbottomout__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define midbottomout_PRTDSI__SYNC_OUT       (* (reg8 *) midbottomout__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(midbottomout__SIO_CFG)
    #define midbottomout_SIO_HYST_EN        (* (reg8 *) midbottomout__SIO_HYST_EN)
    #define midbottomout_SIO_REG_HIFREQ     (* (reg8 *) midbottomout__SIO_REG_HIFREQ)
    #define midbottomout_SIO_CFG            (* (reg8 *) midbottomout__SIO_CFG)
    #define midbottomout_SIO_DIFF           (* (reg8 *) midbottomout__SIO_DIFF)
#endif /* (midbottomout__SIO_CFG) */

/* Interrupt Registers */
#if defined(midbottomout__INTSTAT)
    #define midbottomout_INTSTAT            (* (reg8 *) midbottomout__INTSTAT)
    #define midbottomout_SNAP               (* (reg8 *) midbottomout__SNAP)
    
	#define midbottomout_0_INTTYPE_REG 		(* (reg8 *) midbottomout__0__INTTYPE)
#endif /* (midbottomout__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_midbottomout_H */


/* [] END OF FILE */
