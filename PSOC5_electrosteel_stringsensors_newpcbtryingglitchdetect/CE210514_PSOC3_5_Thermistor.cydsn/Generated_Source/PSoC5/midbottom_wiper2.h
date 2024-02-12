/*******************************************************************************
* File Name: midbottom_wiper2.h  
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

#if !defined(CY_PINS_midbottom_wiper2_H) /* Pins midbottom_wiper2_H */
#define CY_PINS_midbottom_wiper2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "midbottom_wiper2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 midbottom_wiper2__PORT == 15 && ((midbottom_wiper2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    midbottom_wiper2_Write(uint8 value);
void    midbottom_wiper2_SetDriveMode(uint8 mode);
uint8   midbottom_wiper2_ReadDataReg(void);
uint8   midbottom_wiper2_Read(void);
void    midbottom_wiper2_SetInterruptMode(uint16 position, uint16 mode);
uint8   midbottom_wiper2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the midbottom_wiper2_SetDriveMode() function.
     *  @{
     */
        #define midbottom_wiper2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define midbottom_wiper2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define midbottom_wiper2_DM_RES_UP          PIN_DM_RES_UP
        #define midbottom_wiper2_DM_RES_DWN         PIN_DM_RES_DWN
        #define midbottom_wiper2_DM_OD_LO           PIN_DM_OD_LO
        #define midbottom_wiper2_DM_OD_HI           PIN_DM_OD_HI
        #define midbottom_wiper2_DM_STRONG          PIN_DM_STRONG
        #define midbottom_wiper2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define midbottom_wiper2_MASK               midbottom_wiper2__MASK
#define midbottom_wiper2_SHIFT              midbottom_wiper2__SHIFT
#define midbottom_wiper2_WIDTH              1u

/* Interrupt constants */
#if defined(midbottom_wiper2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in midbottom_wiper2_SetInterruptMode() function.
     *  @{
     */
        #define midbottom_wiper2_INTR_NONE      (uint16)(0x0000u)
        #define midbottom_wiper2_INTR_RISING    (uint16)(0x0001u)
        #define midbottom_wiper2_INTR_FALLING   (uint16)(0x0002u)
        #define midbottom_wiper2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define midbottom_wiper2_INTR_MASK      (0x01u) 
#endif /* (midbottom_wiper2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define midbottom_wiper2_PS                     (* (reg8 *) midbottom_wiper2__PS)
/* Data Register */
#define midbottom_wiper2_DR                     (* (reg8 *) midbottom_wiper2__DR)
/* Port Number */
#define midbottom_wiper2_PRT_NUM                (* (reg8 *) midbottom_wiper2__PRT) 
/* Connect to Analog Globals */                                                  
#define midbottom_wiper2_AG                     (* (reg8 *) midbottom_wiper2__AG)                       
/* Analog MUX bux enable */
#define midbottom_wiper2_AMUX                   (* (reg8 *) midbottom_wiper2__AMUX) 
/* Bidirectional Enable */                                                        
#define midbottom_wiper2_BIE                    (* (reg8 *) midbottom_wiper2__BIE)
/* Bit-mask for Aliased Register Access */
#define midbottom_wiper2_BIT_MASK               (* (reg8 *) midbottom_wiper2__BIT_MASK)
/* Bypass Enable */
#define midbottom_wiper2_BYP                    (* (reg8 *) midbottom_wiper2__BYP)
/* Port wide control signals */                                                   
#define midbottom_wiper2_CTL                    (* (reg8 *) midbottom_wiper2__CTL)
/* Drive Modes */
#define midbottom_wiper2_DM0                    (* (reg8 *) midbottom_wiper2__DM0) 
#define midbottom_wiper2_DM1                    (* (reg8 *) midbottom_wiper2__DM1)
#define midbottom_wiper2_DM2                    (* (reg8 *) midbottom_wiper2__DM2) 
/* Input Buffer Disable Override */
#define midbottom_wiper2_INP_DIS                (* (reg8 *) midbottom_wiper2__INP_DIS)
/* LCD Common or Segment Drive */
#define midbottom_wiper2_LCD_COM_SEG            (* (reg8 *) midbottom_wiper2__LCD_COM_SEG)
/* Enable Segment LCD */
#define midbottom_wiper2_LCD_EN                 (* (reg8 *) midbottom_wiper2__LCD_EN)
/* Slew Rate Control */
#define midbottom_wiper2_SLW                    (* (reg8 *) midbottom_wiper2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define midbottom_wiper2_PRTDSI__CAPS_SEL       (* (reg8 *) midbottom_wiper2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define midbottom_wiper2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) midbottom_wiper2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define midbottom_wiper2_PRTDSI__OE_SEL0        (* (reg8 *) midbottom_wiper2__PRTDSI__OE_SEL0) 
#define midbottom_wiper2_PRTDSI__OE_SEL1        (* (reg8 *) midbottom_wiper2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define midbottom_wiper2_PRTDSI__OUT_SEL0       (* (reg8 *) midbottom_wiper2__PRTDSI__OUT_SEL0) 
#define midbottom_wiper2_PRTDSI__OUT_SEL1       (* (reg8 *) midbottom_wiper2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define midbottom_wiper2_PRTDSI__SYNC_OUT       (* (reg8 *) midbottom_wiper2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(midbottom_wiper2__SIO_CFG)
    #define midbottom_wiper2_SIO_HYST_EN        (* (reg8 *) midbottom_wiper2__SIO_HYST_EN)
    #define midbottom_wiper2_SIO_REG_HIFREQ     (* (reg8 *) midbottom_wiper2__SIO_REG_HIFREQ)
    #define midbottom_wiper2_SIO_CFG            (* (reg8 *) midbottom_wiper2__SIO_CFG)
    #define midbottom_wiper2_SIO_DIFF           (* (reg8 *) midbottom_wiper2__SIO_DIFF)
#endif /* (midbottom_wiper2__SIO_CFG) */

/* Interrupt Registers */
#if defined(midbottom_wiper2__INTSTAT)
    #define midbottom_wiper2_INTSTAT            (* (reg8 *) midbottom_wiper2__INTSTAT)
    #define midbottom_wiper2_SNAP               (* (reg8 *) midbottom_wiper2__SNAP)
    
	#define midbottom_wiper2_0_INTTYPE_REG 		(* (reg8 *) midbottom_wiper2__0__INTTYPE)
#endif /* (midbottom_wiper2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_midbottom_wiper2_H */


/* [] END OF FILE */
