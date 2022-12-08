/*******************************************************************************
* File Name: foot4.h  
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

#if !defined(CY_PINS_foot4_H) /* Pins foot4_H */
#define CY_PINS_foot4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "foot4_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 foot4__PORT == 15 && ((foot4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    foot4_Write(uint8 value);
void    foot4_SetDriveMode(uint8 mode);
uint8   foot4_ReadDataReg(void);
uint8   foot4_Read(void);
void    foot4_SetInterruptMode(uint16 position, uint16 mode);
uint8   foot4_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the foot4_SetDriveMode() function.
     *  @{
     */
        #define foot4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define foot4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define foot4_DM_RES_UP          PIN_DM_RES_UP
        #define foot4_DM_RES_DWN         PIN_DM_RES_DWN
        #define foot4_DM_OD_LO           PIN_DM_OD_LO
        #define foot4_DM_OD_HI           PIN_DM_OD_HI
        #define foot4_DM_STRONG          PIN_DM_STRONG
        #define foot4_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define foot4_MASK               foot4__MASK
#define foot4_SHIFT              foot4__SHIFT
#define foot4_WIDTH              1u

/* Interrupt constants */
#if defined(foot4__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in foot4_SetInterruptMode() function.
     *  @{
     */
        #define foot4_INTR_NONE      (uint16)(0x0000u)
        #define foot4_INTR_RISING    (uint16)(0x0001u)
        #define foot4_INTR_FALLING   (uint16)(0x0002u)
        #define foot4_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define foot4_INTR_MASK      (0x01u) 
#endif /* (foot4__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define foot4_PS                     (* (reg8 *) foot4__PS)
/* Data Register */
#define foot4_DR                     (* (reg8 *) foot4__DR)
/* Port Number */
#define foot4_PRT_NUM                (* (reg8 *) foot4__PRT) 
/* Connect to Analog Globals */                                                  
#define foot4_AG                     (* (reg8 *) foot4__AG)                       
/* Analog MUX bux enable */
#define foot4_AMUX                   (* (reg8 *) foot4__AMUX) 
/* Bidirectional Enable */                                                        
#define foot4_BIE                    (* (reg8 *) foot4__BIE)
/* Bit-mask for Aliased Register Access */
#define foot4_BIT_MASK               (* (reg8 *) foot4__BIT_MASK)
/* Bypass Enable */
#define foot4_BYP                    (* (reg8 *) foot4__BYP)
/* Port wide control signals */                                                   
#define foot4_CTL                    (* (reg8 *) foot4__CTL)
/* Drive Modes */
#define foot4_DM0                    (* (reg8 *) foot4__DM0) 
#define foot4_DM1                    (* (reg8 *) foot4__DM1)
#define foot4_DM2                    (* (reg8 *) foot4__DM2) 
/* Input Buffer Disable Override */
#define foot4_INP_DIS                (* (reg8 *) foot4__INP_DIS)
/* LCD Common or Segment Drive */
#define foot4_LCD_COM_SEG            (* (reg8 *) foot4__LCD_COM_SEG)
/* Enable Segment LCD */
#define foot4_LCD_EN                 (* (reg8 *) foot4__LCD_EN)
/* Slew Rate Control */
#define foot4_SLW                    (* (reg8 *) foot4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define foot4_PRTDSI__CAPS_SEL       (* (reg8 *) foot4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define foot4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) foot4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define foot4_PRTDSI__OE_SEL0        (* (reg8 *) foot4__PRTDSI__OE_SEL0) 
#define foot4_PRTDSI__OE_SEL1        (* (reg8 *) foot4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define foot4_PRTDSI__OUT_SEL0       (* (reg8 *) foot4__PRTDSI__OUT_SEL0) 
#define foot4_PRTDSI__OUT_SEL1       (* (reg8 *) foot4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define foot4_PRTDSI__SYNC_OUT       (* (reg8 *) foot4__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(foot4__SIO_CFG)
    #define foot4_SIO_HYST_EN        (* (reg8 *) foot4__SIO_HYST_EN)
    #define foot4_SIO_REG_HIFREQ     (* (reg8 *) foot4__SIO_REG_HIFREQ)
    #define foot4_SIO_CFG            (* (reg8 *) foot4__SIO_CFG)
    #define foot4_SIO_DIFF           (* (reg8 *) foot4__SIO_DIFF)
#endif /* (foot4__SIO_CFG) */

/* Interrupt Registers */
#if defined(foot4__INTSTAT)
    #define foot4_INTSTAT            (* (reg8 *) foot4__INTSTAT)
    #define foot4_SNAP               (* (reg8 *) foot4__SNAP)
    
	#define foot4_0_INTTYPE_REG 		(* (reg8 *) foot4__0__INTTYPE)
#endif /* (foot4__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_foot4_H */


/* [] END OF FILE */
