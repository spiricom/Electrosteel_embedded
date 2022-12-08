/*******************************************************************************
* File Name: spi2_miso.h  
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

#if !defined(CY_PINS_spi2_miso_H) /* Pins spi2_miso_H */
#define CY_PINS_spi2_miso_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "spi2_miso_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 spi2_miso__PORT == 15 && ((spi2_miso__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    spi2_miso_Write(uint8 value);
void    spi2_miso_SetDriveMode(uint8 mode);
uint8   spi2_miso_ReadDataReg(void);
uint8   spi2_miso_Read(void);
void    spi2_miso_SetInterruptMode(uint16 position, uint16 mode);
uint8   spi2_miso_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the spi2_miso_SetDriveMode() function.
     *  @{
     */
        #define spi2_miso_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define spi2_miso_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define spi2_miso_DM_RES_UP          PIN_DM_RES_UP
        #define spi2_miso_DM_RES_DWN         PIN_DM_RES_DWN
        #define spi2_miso_DM_OD_LO           PIN_DM_OD_LO
        #define spi2_miso_DM_OD_HI           PIN_DM_OD_HI
        #define spi2_miso_DM_STRONG          PIN_DM_STRONG
        #define spi2_miso_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define spi2_miso_MASK               spi2_miso__MASK
#define spi2_miso_SHIFT              spi2_miso__SHIFT
#define spi2_miso_WIDTH              1u

/* Interrupt constants */
#if defined(spi2_miso__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in spi2_miso_SetInterruptMode() function.
     *  @{
     */
        #define spi2_miso_INTR_NONE      (uint16)(0x0000u)
        #define spi2_miso_INTR_RISING    (uint16)(0x0001u)
        #define spi2_miso_INTR_FALLING   (uint16)(0x0002u)
        #define spi2_miso_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define spi2_miso_INTR_MASK      (0x01u) 
#endif /* (spi2_miso__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define spi2_miso_PS                     (* (reg8 *) spi2_miso__PS)
/* Data Register */
#define spi2_miso_DR                     (* (reg8 *) spi2_miso__DR)
/* Port Number */
#define spi2_miso_PRT_NUM                (* (reg8 *) spi2_miso__PRT) 
/* Connect to Analog Globals */                                                  
#define spi2_miso_AG                     (* (reg8 *) spi2_miso__AG)                       
/* Analog MUX bux enable */
#define spi2_miso_AMUX                   (* (reg8 *) spi2_miso__AMUX) 
/* Bidirectional Enable */                                                        
#define spi2_miso_BIE                    (* (reg8 *) spi2_miso__BIE)
/* Bit-mask for Aliased Register Access */
#define spi2_miso_BIT_MASK               (* (reg8 *) spi2_miso__BIT_MASK)
/* Bypass Enable */
#define spi2_miso_BYP                    (* (reg8 *) spi2_miso__BYP)
/* Port wide control signals */                                                   
#define spi2_miso_CTL                    (* (reg8 *) spi2_miso__CTL)
/* Drive Modes */
#define spi2_miso_DM0                    (* (reg8 *) spi2_miso__DM0) 
#define spi2_miso_DM1                    (* (reg8 *) spi2_miso__DM1)
#define spi2_miso_DM2                    (* (reg8 *) spi2_miso__DM2) 
/* Input Buffer Disable Override */
#define spi2_miso_INP_DIS                (* (reg8 *) spi2_miso__INP_DIS)
/* LCD Common or Segment Drive */
#define spi2_miso_LCD_COM_SEG            (* (reg8 *) spi2_miso__LCD_COM_SEG)
/* Enable Segment LCD */
#define spi2_miso_LCD_EN                 (* (reg8 *) spi2_miso__LCD_EN)
/* Slew Rate Control */
#define spi2_miso_SLW                    (* (reg8 *) spi2_miso__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define spi2_miso_PRTDSI__CAPS_SEL       (* (reg8 *) spi2_miso__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define spi2_miso_PRTDSI__DBL_SYNC_IN    (* (reg8 *) spi2_miso__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define spi2_miso_PRTDSI__OE_SEL0        (* (reg8 *) spi2_miso__PRTDSI__OE_SEL0) 
#define spi2_miso_PRTDSI__OE_SEL1        (* (reg8 *) spi2_miso__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define spi2_miso_PRTDSI__OUT_SEL0       (* (reg8 *) spi2_miso__PRTDSI__OUT_SEL0) 
#define spi2_miso_PRTDSI__OUT_SEL1       (* (reg8 *) spi2_miso__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define spi2_miso_PRTDSI__SYNC_OUT       (* (reg8 *) spi2_miso__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(spi2_miso__SIO_CFG)
    #define spi2_miso_SIO_HYST_EN        (* (reg8 *) spi2_miso__SIO_HYST_EN)
    #define spi2_miso_SIO_REG_HIFREQ     (* (reg8 *) spi2_miso__SIO_REG_HIFREQ)
    #define spi2_miso_SIO_CFG            (* (reg8 *) spi2_miso__SIO_CFG)
    #define spi2_miso_SIO_DIFF           (* (reg8 *) spi2_miso__SIO_DIFF)
#endif /* (spi2_miso__SIO_CFG) */

/* Interrupt Registers */
#if defined(spi2_miso__INTSTAT)
    #define spi2_miso_INTSTAT            (* (reg8 *) spi2_miso__INTSTAT)
    #define spi2_miso_SNAP               (* (reg8 *) spi2_miso__SNAP)
    
	#define spi2_miso_0_INTTYPE_REG 		(* (reg8 *) spi2_miso__0__INTTYPE)
#endif /* (spi2_miso__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_spi2_miso_H */


/* [] END OF FILE */
