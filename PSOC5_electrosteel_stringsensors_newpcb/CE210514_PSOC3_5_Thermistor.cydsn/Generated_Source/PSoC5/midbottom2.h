/*******************************************************************************
* File Name: midbottom2.h  
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

#if !defined(CY_PINS_midbottom2_H) /* Pins midbottom2_H */
#define CY_PINS_midbottom2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "midbottom2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 midbottom2__PORT == 15 && ((midbottom2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    midbottom2_Write(uint8 value);
void    midbottom2_SetDriveMode(uint8 mode);
uint8   midbottom2_ReadDataReg(void);
uint8   midbottom2_Read(void);
void    midbottom2_SetInterruptMode(uint16 position, uint16 mode);
uint8   midbottom2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the midbottom2_SetDriveMode() function.
     *  @{
     */
        #define midbottom2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define midbottom2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define midbottom2_DM_RES_UP          PIN_DM_RES_UP
        #define midbottom2_DM_RES_DWN         PIN_DM_RES_DWN
        #define midbottom2_DM_OD_LO           PIN_DM_OD_LO
        #define midbottom2_DM_OD_HI           PIN_DM_OD_HI
        #define midbottom2_DM_STRONG          PIN_DM_STRONG
        #define midbottom2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define midbottom2_MASK               midbottom2__MASK
#define midbottom2_SHIFT              midbottom2__SHIFT
#define midbottom2_WIDTH              1u

/* Interrupt constants */
#if defined(midbottom2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in midbottom2_SetInterruptMode() function.
     *  @{
     */
        #define midbottom2_INTR_NONE      (uint16)(0x0000u)
        #define midbottom2_INTR_RISING    (uint16)(0x0001u)
        #define midbottom2_INTR_FALLING   (uint16)(0x0002u)
        #define midbottom2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define midbottom2_INTR_MASK      (0x01u) 
#endif /* (midbottom2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define midbottom2_PS                     (* (reg8 *) midbottom2__PS)
/* Data Register */
#define midbottom2_DR                     (* (reg8 *) midbottom2__DR)
/* Port Number */
#define midbottom2_PRT_NUM                (* (reg8 *) midbottom2__PRT) 
/* Connect to Analog Globals */                                                  
#define midbottom2_AG                     (* (reg8 *) midbottom2__AG)                       
/* Analog MUX bux enable */
#define midbottom2_AMUX                   (* (reg8 *) midbottom2__AMUX) 
/* Bidirectional Enable */                                                        
#define midbottom2_BIE                    (* (reg8 *) midbottom2__BIE)
/* Bit-mask for Aliased Register Access */
#define midbottom2_BIT_MASK               (* (reg8 *) midbottom2__BIT_MASK)
/* Bypass Enable */
#define midbottom2_BYP                    (* (reg8 *) midbottom2__BYP)
/* Port wide control signals */                                                   
#define midbottom2_CTL                    (* (reg8 *) midbottom2__CTL)
/* Drive Modes */
#define midbottom2_DM0                    (* (reg8 *) midbottom2__DM0) 
#define midbottom2_DM1                    (* (reg8 *) midbottom2__DM1)
#define midbottom2_DM2                    (* (reg8 *) midbottom2__DM2) 
/* Input Buffer Disable Override */
#define midbottom2_INP_DIS                (* (reg8 *) midbottom2__INP_DIS)
/* LCD Common or Segment Drive */
#define midbottom2_LCD_COM_SEG            (* (reg8 *) midbottom2__LCD_COM_SEG)
/* Enable Segment LCD */
#define midbottom2_LCD_EN                 (* (reg8 *) midbottom2__LCD_EN)
/* Slew Rate Control */
#define midbottom2_SLW                    (* (reg8 *) midbottom2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define midbottom2_PRTDSI__CAPS_SEL       (* (reg8 *) midbottom2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define midbottom2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) midbottom2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define midbottom2_PRTDSI__OE_SEL0        (* (reg8 *) midbottom2__PRTDSI__OE_SEL0) 
#define midbottom2_PRTDSI__OE_SEL1        (* (reg8 *) midbottom2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define midbottom2_PRTDSI__OUT_SEL0       (* (reg8 *) midbottom2__PRTDSI__OUT_SEL0) 
#define midbottom2_PRTDSI__OUT_SEL1       (* (reg8 *) midbottom2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define midbottom2_PRTDSI__SYNC_OUT       (* (reg8 *) midbottom2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(midbottom2__SIO_CFG)
    #define midbottom2_SIO_HYST_EN        (* (reg8 *) midbottom2__SIO_HYST_EN)
    #define midbottom2_SIO_REG_HIFREQ     (* (reg8 *) midbottom2__SIO_REG_HIFREQ)
    #define midbottom2_SIO_CFG            (* (reg8 *) midbottom2__SIO_CFG)
    #define midbottom2_SIO_DIFF           (* (reg8 *) midbottom2__SIO_DIFF)
#endif /* (midbottom2__SIO_CFG) */

/* Interrupt Registers */
#if defined(midbottom2__INTSTAT)
    #define midbottom2_INTSTAT            (* (reg8 *) midbottom2__INTSTAT)
    #define midbottom2_SNAP               (* (reg8 *) midbottom2__SNAP)
    
	#define midbottom2_0_INTTYPE_REG 		(* (reg8 *) midbottom2__0__INTTYPE)
#endif /* (midbottom2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_midbottom2_H */


/* [] END OF FILE */
