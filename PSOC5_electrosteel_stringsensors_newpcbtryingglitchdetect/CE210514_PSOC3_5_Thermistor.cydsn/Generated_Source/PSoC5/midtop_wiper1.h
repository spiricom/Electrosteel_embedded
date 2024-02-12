/*******************************************************************************
* File Name: midtop_wiper1.h  
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

#if !defined(CY_PINS_midtop_wiper1_H) /* Pins midtop_wiper1_H */
#define CY_PINS_midtop_wiper1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "midtop_wiper1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 midtop_wiper1__PORT == 15 && ((midtop_wiper1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    midtop_wiper1_Write(uint8 value);
void    midtop_wiper1_SetDriveMode(uint8 mode);
uint8   midtop_wiper1_ReadDataReg(void);
uint8   midtop_wiper1_Read(void);
void    midtop_wiper1_SetInterruptMode(uint16 position, uint16 mode);
uint8   midtop_wiper1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the midtop_wiper1_SetDriveMode() function.
     *  @{
     */
        #define midtop_wiper1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define midtop_wiper1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define midtop_wiper1_DM_RES_UP          PIN_DM_RES_UP
        #define midtop_wiper1_DM_RES_DWN         PIN_DM_RES_DWN
        #define midtop_wiper1_DM_OD_LO           PIN_DM_OD_LO
        #define midtop_wiper1_DM_OD_HI           PIN_DM_OD_HI
        #define midtop_wiper1_DM_STRONG          PIN_DM_STRONG
        #define midtop_wiper1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define midtop_wiper1_MASK               midtop_wiper1__MASK
#define midtop_wiper1_SHIFT              midtop_wiper1__SHIFT
#define midtop_wiper1_WIDTH              1u

/* Interrupt constants */
#if defined(midtop_wiper1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in midtop_wiper1_SetInterruptMode() function.
     *  @{
     */
        #define midtop_wiper1_INTR_NONE      (uint16)(0x0000u)
        #define midtop_wiper1_INTR_RISING    (uint16)(0x0001u)
        #define midtop_wiper1_INTR_FALLING   (uint16)(0x0002u)
        #define midtop_wiper1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define midtop_wiper1_INTR_MASK      (0x01u) 
#endif /* (midtop_wiper1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define midtop_wiper1_PS                     (* (reg8 *) midtop_wiper1__PS)
/* Data Register */
#define midtop_wiper1_DR                     (* (reg8 *) midtop_wiper1__DR)
/* Port Number */
#define midtop_wiper1_PRT_NUM                (* (reg8 *) midtop_wiper1__PRT) 
/* Connect to Analog Globals */                                                  
#define midtop_wiper1_AG                     (* (reg8 *) midtop_wiper1__AG)                       
/* Analog MUX bux enable */
#define midtop_wiper1_AMUX                   (* (reg8 *) midtop_wiper1__AMUX) 
/* Bidirectional Enable */                                                        
#define midtop_wiper1_BIE                    (* (reg8 *) midtop_wiper1__BIE)
/* Bit-mask for Aliased Register Access */
#define midtop_wiper1_BIT_MASK               (* (reg8 *) midtop_wiper1__BIT_MASK)
/* Bypass Enable */
#define midtop_wiper1_BYP                    (* (reg8 *) midtop_wiper1__BYP)
/* Port wide control signals */                                                   
#define midtop_wiper1_CTL                    (* (reg8 *) midtop_wiper1__CTL)
/* Drive Modes */
#define midtop_wiper1_DM0                    (* (reg8 *) midtop_wiper1__DM0) 
#define midtop_wiper1_DM1                    (* (reg8 *) midtop_wiper1__DM1)
#define midtop_wiper1_DM2                    (* (reg8 *) midtop_wiper1__DM2) 
/* Input Buffer Disable Override */
#define midtop_wiper1_INP_DIS                (* (reg8 *) midtop_wiper1__INP_DIS)
/* LCD Common or Segment Drive */
#define midtop_wiper1_LCD_COM_SEG            (* (reg8 *) midtop_wiper1__LCD_COM_SEG)
/* Enable Segment LCD */
#define midtop_wiper1_LCD_EN                 (* (reg8 *) midtop_wiper1__LCD_EN)
/* Slew Rate Control */
#define midtop_wiper1_SLW                    (* (reg8 *) midtop_wiper1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define midtop_wiper1_PRTDSI__CAPS_SEL       (* (reg8 *) midtop_wiper1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define midtop_wiper1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) midtop_wiper1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define midtop_wiper1_PRTDSI__OE_SEL0        (* (reg8 *) midtop_wiper1__PRTDSI__OE_SEL0) 
#define midtop_wiper1_PRTDSI__OE_SEL1        (* (reg8 *) midtop_wiper1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define midtop_wiper1_PRTDSI__OUT_SEL0       (* (reg8 *) midtop_wiper1__PRTDSI__OUT_SEL0) 
#define midtop_wiper1_PRTDSI__OUT_SEL1       (* (reg8 *) midtop_wiper1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define midtop_wiper1_PRTDSI__SYNC_OUT       (* (reg8 *) midtop_wiper1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(midtop_wiper1__SIO_CFG)
    #define midtop_wiper1_SIO_HYST_EN        (* (reg8 *) midtop_wiper1__SIO_HYST_EN)
    #define midtop_wiper1_SIO_REG_HIFREQ     (* (reg8 *) midtop_wiper1__SIO_REG_HIFREQ)
    #define midtop_wiper1_SIO_CFG            (* (reg8 *) midtop_wiper1__SIO_CFG)
    #define midtop_wiper1_SIO_DIFF           (* (reg8 *) midtop_wiper1__SIO_DIFF)
#endif /* (midtop_wiper1__SIO_CFG) */

/* Interrupt Registers */
#if defined(midtop_wiper1__INTSTAT)
    #define midtop_wiper1_INTSTAT            (* (reg8 *) midtop_wiper1__INTSTAT)
    #define midtop_wiper1_SNAP               (* (reg8 *) midtop_wiper1__SNAP)
    
	#define midtop_wiper1_0_INTTYPE_REG 		(* (reg8 *) midtop_wiper1__0__INTTYPE)
#endif /* (midtop_wiper1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_midtop_wiper1_H */


/* [] END OF FILE */
