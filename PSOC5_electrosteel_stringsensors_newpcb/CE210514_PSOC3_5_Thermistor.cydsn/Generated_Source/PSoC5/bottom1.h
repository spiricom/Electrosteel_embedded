/*******************************************************************************
* File Name: bottom1.h  
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

#if !defined(CY_PINS_bottom1_H) /* Pins bottom1_H */
#define CY_PINS_bottom1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "bottom1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 bottom1__PORT == 15 && ((bottom1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    bottom1_Write(uint8 value);
void    bottom1_SetDriveMode(uint8 mode);
uint8   bottom1_ReadDataReg(void);
uint8   bottom1_Read(void);
void    bottom1_SetInterruptMode(uint16 position, uint16 mode);
uint8   bottom1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the bottom1_SetDriveMode() function.
     *  @{
     */
        #define bottom1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define bottom1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define bottom1_DM_RES_UP          PIN_DM_RES_UP
        #define bottom1_DM_RES_DWN         PIN_DM_RES_DWN
        #define bottom1_DM_OD_LO           PIN_DM_OD_LO
        #define bottom1_DM_OD_HI           PIN_DM_OD_HI
        #define bottom1_DM_STRONG          PIN_DM_STRONG
        #define bottom1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define bottom1_MASK               bottom1__MASK
#define bottom1_SHIFT              bottom1__SHIFT
#define bottom1_WIDTH              1u

/* Interrupt constants */
#if defined(bottom1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in bottom1_SetInterruptMode() function.
     *  @{
     */
        #define bottom1_INTR_NONE      (uint16)(0x0000u)
        #define bottom1_INTR_RISING    (uint16)(0x0001u)
        #define bottom1_INTR_FALLING   (uint16)(0x0002u)
        #define bottom1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define bottom1_INTR_MASK      (0x01u) 
#endif /* (bottom1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define bottom1_PS                     (* (reg8 *) bottom1__PS)
/* Data Register */
#define bottom1_DR                     (* (reg8 *) bottom1__DR)
/* Port Number */
#define bottom1_PRT_NUM                (* (reg8 *) bottom1__PRT) 
/* Connect to Analog Globals */                                                  
#define bottom1_AG                     (* (reg8 *) bottom1__AG)                       
/* Analog MUX bux enable */
#define bottom1_AMUX                   (* (reg8 *) bottom1__AMUX) 
/* Bidirectional Enable */                                                        
#define bottom1_BIE                    (* (reg8 *) bottom1__BIE)
/* Bit-mask for Aliased Register Access */
#define bottom1_BIT_MASK               (* (reg8 *) bottom1__BIT_MASK)
/* Bypass Enable */
#define bottom1_BYP                    (* (reg8 *) bottom1__BYP)
/* Port wide control signals */                                                   
#define bottom1_CTL                    (* (reg8 *) bottom1__CTL)
/* Drive Modes */
#define bottom1_DM0                    (* (reg8 *) bottom1__DM0) 
#define bottom1_DM1                    (* (reg8 *) bottom1__DM1)
#define bottom1_DM2                    (* (reg8 *) bottom1__DM2) 
/* Input Buffer Disable Override */
#define bottom1_INP_DIS                (* (reg8 *) bottom1__INP_DIS)
/* LCD Common or Segment Drive */
#define bottom1_LCD_COM_SEG            (* (reg8 *) bottom1__LCD_COM_SEG)
/* Enable Segment LCD */
#define bottom1_LCD_EN                 (* (reg8 *) bottom1__LCD_EN)
/* Slew Rate Control */
#define bottom1_SLW                    (* (reg8 *) bottom1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define bottom1_PRTDSI__CAPS_SEL       (* (reg8 *) bottom1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define bottom1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) bottom1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define bottom1_PRTDSI__OE_SEL0        (* (reg8 *) bottom1__PRTDSI__OE_SEL0) 
#define bottom1_PRTDSI__OE_SEL1        (* (reg8 *) bottom1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define bottom1_PRTDSI__OUT_SEL0       (* (reg8 *) bottom1__PRTDSI__OUT_SEL0) 
#define bottom1_PRTDSI__OUT_SEL1       (* (reg8 *) bottom1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define bottom1_PRTDSI__SYNC_OUT       (* (reg8 *) bottom1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(bottom1__SIO_CFG)
    #define bottom1_SIO_HYST_EN        (* (reg8 *) bottom1__SIO_HYST_EN)
    #define bottom1_SIO_REG_HIFREQ     (* (reg8 *) bottom1__SIO_REG_HIFREQ)
    #define bottom1_SIO_CFG            (* (reg8 *) bottom1__SIO_CFG)
    #define bottom1_SIO_DIFF           (* (reg8 *) bottom1__SIO_DIFF)
#endif /* (bottom1__SIO_CFG) */

/* Interrupt Registers */
#if defined(bottom1__INTSTAT)
    #define bottom1_INTSTAT            (* (reg8 *) bottom1__INTSTAT)
    #define bottom1_SNAP               (* (reg8 *) bottom1__SNAP)
    
	#define bottom1_0_INTTYPE_REG 		(* (reg8 *) bottom1__0__INTTYPE)
#endif /* (bottom1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_bottom1_H */


/* [] END OF FILE */
