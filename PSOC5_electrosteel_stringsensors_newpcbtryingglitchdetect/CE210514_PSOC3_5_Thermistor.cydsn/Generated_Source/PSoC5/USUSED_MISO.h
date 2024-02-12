/*******************************************************************************
* File Name: USUSED_MISO.h  
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

#if !defined(CY_PINS_USUSED_MISO_H) /* Pins USUSED_MISO_H */
#define CY_PINS_USUSED_MISO_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "USUSED_MISO_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 USUSED_MISO__PORT == 15 && ((USUSED_MISO__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    USUSED_MISO_Write(uint8 value);
void    USUSED_MISO_SetDriveMode(uint8 mode);
uint8   USUSED_MISO_ReadDataReg(void);
uint8   USUSED_MISO_Read(void);
void    USUSED_MISO_SetInterruptMode(uint16 position, uint16 mode);
uint8   USUSED_MISO_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the USUSED_MISO_SetDriveMode() function.
     *  @{
     */
        #define USUSED_MISO_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define USUSED_MISO_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define USUSED_MISO_DM_RES_UP          PIN_DM_RES_UP
        #define USUSED_MISO_DM_RES_DWN         PIN_DM_RES_DWN
        #define USUSED_MISO_DM_OD_LO           PIN_DM_OD_LO
        #define USUSED_MISO_DM_OD_HI           PIN_DM_OD_HI
        #define USUSED_MISO_DM_STRONG          PIN_DM_STRONG
        #define USUSED_MISO_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define USUSED_MISO_MASK               USUSED_MISO__MASK
#define USUSED_MISO_SHIFT              USUSED_MISO__SHIFT
#define USUSED_MISO_WIDTH              1u

/* Interrupt constants */
#if defined(USUSED_MISO__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in USUSED_MISO_SetInterruptMode() function.
     *  @{
     */
        #define USUSED_MISO_INTR_NONE      (uint16)(0x0000u)
        #define USUSED_MISO_INTR_RISING    (uint16)(0x0001u)
        #define USUSED_MISO_INTR_FALLING   (uint16)(0x0002u)
        #define USUSED_MISO_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define USUSED_MISO_INTR_MASK      (0x01u) 
#endif /* (USUSED_MISO__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define USUSED_MISO_PS                     (* (reg8 *) USUSED_MISO__PS)
/* Data Register */
#define USUSED_MISO_DR                     (* (reg8 *) USUSED_MISO__DR)
/* Port Number */
#define USUSED_MISO_PRT_NUM                (* (reg8 *) USUSED_MISO__PRT) 
/* Connect to Analog Globals */                                                  
#define USUSED_MISO_AG                     (* (reg8 *) USUSED_MISO__AG)                       
/* Analog MUX bux enable */
#define USUSED_MISO_AMUX                   (* (reg8 *) USUSED_MISO__AMUX) 
/* Bidirectional Enable */                                                        
#define USUSED_MISO_BIE                    (* (reg8 *) USUSED_MISO__BIE)
/* Bit-mask for Aliased Register Access */
#define USUSED_MISO_BIT_MASK               (* (reg8 *) USUSED_MISO__BIT_MASK)
/* Bypass Enable */
#define USUSED_MISO_BYP                    (* (reg8 *) USUSED_MISO__BYP)
/* Port wide control signals */                                                   
#define USUSED_MISO_CTL                    (* (reg8 *) USUSED_MISO__CTL)
/* Drive Modes */
#define USUSED_MISO_DM0                    (* (reg8 *) USUSED_MISO__DM0) 
#define USUSED_MISO_DM1                    (* (reg8 *) USUSED_MISO__DM1)
#define USUSED_MISO_DM2                    (* (reg8 *) USUSED_MISO__DM2) 
/* Input Buffer Disable Override */
#define USUSED_MISO_INP_DIS                (* (reg8 *) USUSED_MISO__INP_DIS)
/* LCD Common or Segment Drive */
#define USUSED_MISO_LCD_COM_SEG            (* (reg8 *) USUSED_MISO__LCD_COM_SEG)
/* Enable Segment LCD */
#define USUSED_MISO_LCD_EN                 (* (reg8 *) USUSED_MISO__LCD_EN)
/* Slew Rate Control */
#define USUSED_MISO_SLW                    (* (reg8 *) USUSED_MISO__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define USUSED_MISO_PRTDSI__CAPS_SEL       (* (reg8 *) USUSED_MISO__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define USUSED_MISO_PRTDSI__DBL_SYNC_IN    (* (reg8 *) USUSED_MISO__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define USUSED_MISO_PRTDSI__OE_SEL0        (* (reg8 *) USUSED_MISO__PRTDSI__OE_SEL0) 
#define USUSED_MISO_PRTDSI__OE_SEL1        (* (reg8 *) USUSED_MISO__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define USUSED_MISO_PRTDSI__OUT_SEL0       (* (reg8 *) USUSED_MISO__PRTDSI__OUT_SEL0) 
#define USUSED_MISO_PRTDSI__OUT_SEL1       (* (reg8 *) USUSED_MISO__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define USUSED_MISO_PRTDSI__SYNC_OUT       (* (reg8 *) USUSED_MISO__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(USUSED_MISO__SIO_CFG)
    #define USUSED_MISO_SIO_HYST_EN        (* (reg8 *) USUSED_MISO__SIO_HYST_EN)
    #define USUSED_MISO_SIO_REG_HIFREQ     (* (reg8 *) USUSED_MISO__SIO_REG_HIFREQ)
    #define USUSED_MISO_SIO_CFG            (* (reg8 *) USUSED_MISO__SIO_CFG)
    #define USUSED_MISO_SIO_DIFF           (* (reg8 *) USUSED_MISO__SIO_DIFF)
#endif /* (USUSED_MISO__SIO_CFG) */

/* Interrupt Registers */
#if defined(USUSED_MISO__INTSTAT)
    #define USUSED_MISO_INTSTAT            (* (reg8 *) USUSED_MISO__INTSTAT)
    #define USUSED_MISO_SNAP               (* (reg8 *) USUSED_MISO__SNAP)
    
	#define USUSED_MISO_0_INTTYPE_REG 		(* (reg8 *) USUSED_MISO__0__INTTYPE)
#endif /* (USUSED_MISO__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_USUSED_MISO_H */


/* [] END OF FILE */
