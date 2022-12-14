/*******************************************************************************
* File Name: VHIN.h  
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

#if !defined(CY_PINS_VHIN_H) /* Pins VHIN_H */
#define CY_PINS_VHIN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "VHIN_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 VHIN__PORT == 15 && ((VHIN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    VHIN_Write(uint8 value);
void    VHIN_SetDriveMode(uint8 mode);
uint8   VHIN_ReadDataReg(void);
uint8   VHIN_Read(void);
void    VHIN_SetInterruptMode(uint16 position, uint16 mode);
uint8   VHIN_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the VHIN_SetDriveMode() function.
     *  @{
     */
        #define VHIN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define VHIN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define VHIN_DM_RES_UP          PIN_DM_RES_UP
        #define VHIN_DM_RES_DWN         PIN_DM_RES_DWN
        #define VHIN_DM_OD_LO           PIN_DM_OD_LO
        #define VHIN_DM_OD_HI           PIN_DM_OD_HI
        #define VHIN_DM_STRONG          PIN_DM_STRONG
        #define VHIN_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define VHIN_MASK               VHIN__MASK
#define VHIN_SHIFT              VHIN__SHIFT
#define VHIN_WIDTH              1u

/* Interrupt constants */
#if defined(VHIN__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VHIN_SetInterruptMode() function.
     *  @{
     */
        #define VHIN_INTR_NONE      (uint16)(0x0000u)
        #define VHIN_INTR_RISING    (uint16)(0x0001u)
        #define VHIN_INTR_FALLING   (uint16)(0x0002u)
        #define VHIN_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define VHIN_INTR_MASK      (0x01u) 
#endif /* (VHIN__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VHIN_PS                     (* (reg8 *) VHIN__PS)
/* Data Register */
#define VHIN_DR                     (* (reg8 *) VHIN__DR)
/* Port Number */
#define VHIN_PRT_NUM                (* (reg8 *) VHIN__PRT) 
/* Connect to Analog Globals */                                                  
#define VHIN_AG                     (* (reg8 *) VHIN__AG)                       
/* Analog MUX bux enable */
#define VHIN_AMUX                   (* (reg8 *) VHIN__AMUX) 
/* Bidirectional Enable */                                                        
#define VHIN_BIE                    (* (reg8 *) VHIN__BIE)
/* Bit-mask for Aliased Register Access */
#define VHIN_BIT_MASK               (* (reg8 *) VHIN__BIT_MASK)
/* Bypass Enable */
#define VHIN_BYP                    (* (reg8 *) VHIN__BYP)
/* Port wide control signals */                                                   
#define VHIN_CTL                    (* (reg8 *) VHIN__CTL)
/* Drive Modes */
#define VHIN_DM0                    (* (reg8 *) VHIN__DM0) 
#define VHIN_DM1                    (* (reg8 *) VHIN__DM1)
#define VHIN_DM2                    (* (reg8 *) VHIN__DM2) 
/* Input Buffer Disable Override */
#define VHIN_INP_DIS                (* (reg8 *) VHIN__INP_DIS)
/* LCD Common or Segment Drive */
#define VHIN_LCD_COM_SEG            (* (reg8 *) VHIN__LCD_COM_SEG)
/* Enable Segment LCD */
#define VHIN_LCD_EN                 (* (reg8 *) VHIN__LCD_EN)
/* Slew Rate Control */
#define VHIN_SLW                    (* (reg8 *) VHIN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VHIN_PRTDSI__CAPS_SEL       (* (reg8 *) VHIN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VHIN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VHIN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VHIN_PRTDSI__OE_SEL0        (* (reg8 *) VHIN__PRTDSI__OE_SEL0) 
#define VHIN_PRTDSI__OE_SEL1        (* (reg8 *) VHIN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VHIN_PRTDSI__OUT_SEL0       (* (reg8 *) VHIN__PRTDSI__OUT_SEL0) 
#define VHIN_PRTDSI__OUT_SEL1       (* (reg8 *) VHIN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VHIN_PRTDSI__SYNC_OUT       (* (reg8 *) VHIN__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(VHIN__SIO_CFG)
    #define VHIN_SIO_HYST_EN        (* (reg8 *) VHIN__SIO_HYST_EN)
    #define VHIN_SIO_REG_HIFREQ     (* (reg8 *) VHIN__SIO_REG_HIFREQ)
    #define VHIN_SIO_CFG            (* (reg8 *) VHIN__SIO_CFG)
    #define VHIN_SIO_DIFF           (* (reg8 *) VHIN__SIO_DIFF)
#endif /* (VHIN__SIO_CFG) */

/* Interrupt Registers */
#if defined(VHIN__INTSTAT)
    #define VHIN_INTSTAT            (* (reg8 *) VHIN__INTSTAT)
    #define VHIN_SNAP               (* (reg8 *) VHIN__SNAP)
    
	#define VHIN_0_INTTYPE_REG 		(* (reg8 *) VHIN__0__INTTYPE)
#endif /* (VHIN__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_VHIN_H */


/* [] END OF FILE */
