/*******************************************************************************
* File Name: foot2.h  
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

#if !defined(CY_PINS_foot2_H) /* Pins foot2_H */
#define CY_PINS_foot2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "foot2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 foot2__PORT == 15 && ((foot2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    foot2_Write(uint8 value);
void    foot2_SetDriveMode(uint8 mode);
uint8   foot2_ReadDataReg(void);
uint8   foot2_Read(void);
void    foot2_SetInterruptMode(uint16 position, uint16 mode);
uint8   foot2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the foot2_SetDriveMode() function.
     *  @{
     */
        #define foot2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define foot2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define foot2_DM_RES_UP          PIN_DM_RES_UP
        #define foot2_DM_RES_DWN         PIN_DM_RES_DWN
        #define foot2_DM_OD_LO           PIN_DM_OD_LO
        #define foot2_DM_OD_HI           PIN_DM_OD_HI
        #define foot2_DM_STRONG          PIN_DM_STRONG
        #define foot2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define foot2_MASK               foot2__MASK
#define foot2_SHIFT              foot2__SHIFT
#define foot2_WIDTH              1u

/* Interrupt constants */
#if defined(foot2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in foot2_SetInterruptMode() function.
     *  @{
     */
        #define foot2_INTR_NONE      (uint16)(0x0000u)
        #define foot2_INTR_RISING    (uint16)(0x0001u)
        #define foot2_INTR_FALLING   (uint16)(0x0002u)
        #define foot2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define foot2_INTR_MASK      (0x01u) 
#endif /* (foot2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define foot2_PS                     (* (reg8 *) foot2__PS)
/* Data Register */
#define foot2_DR                     (* (reg8 *) foot2__DR)
/* Port Number */
#define foot2_PRT_NUM                (* (reg8 *) foot2__PRT) 
/* Connect to Analog Globals */                                                  
#define foot2_AG                     (* (reg8 *) foot2__AG)                       
/* Analog MUX bux enable */
#define foot2_AMUX                   (* (reg8 *) foot2__AMUX) 
/* Bidirectional Enable */                                                        
#define foot2_BIE                    (* (reg8 *) foot2__BIE)
/* Bit-mask for Aliased Register Access */
#define foot2_BIT_MASK               (* (reg8 *) foot2__BIT_MASK)
/* Bypass Enable */
#define foot2_BYP                    (* (reg8 *) foot2__BYP)
/* Port wide control signals */                                                   
#define foot2_CTL                    (* (reg8 *) foot2__CTL)
/* Drive Modes */
#define foot2_DM0                    (* (reg8 *) foot2__DM0) 
#define foot2_DM1                    (* (reg8 *) foot2__DM1)
#define foot2_DM2                    (* (reg8 *) foot2__DM2) 
/* Input Buffer Disable Override */
#define foot2_INP_DIS                (* (reg8 *) foot2__INP_DIS)
/* LCD Common or Segment Drive */
#define foot2_LCD_COM_SEG            (* (reg8 *) foot2__LCD_COM_SEG)
/* Enable Segment LCD */
#define foot2_LCD_EN                 (* (reg8 *) foot2__LCD_EN)
/* Slew Rate Control */
#define foot2_SLW                    (* (reg8 *) foot2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define foot2_PRTDSI__CAPS_SEL       (* (reg8 *) foot2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define foot2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) foot2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define foot2_PRTDSI__OE_SEL0        (* (reg8 *) foot2__PRTDSI__OE_SEL0) 
#define foot2_PRTDSI__OE_SEL1        (* (reg8 *) foot2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define foot2_PRTDSI__OUT_SEL0       (* (reg8 *) foot2__PRTDSI__OUT_SEL0) 
#define foot2_PRTDSI__OUT_SEL1       (* (reg8 *) foot2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define foot2_PRTDSI__SYNC_OUT       (* (reg8 *) foot2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(foot2__SIO_CFG)
    #define foot2_SIO_HYST_EN        (* (reg8 *) foot2__SIO_HYST_EN)
    #define foot2_SIO_REG_HIFREQ     (* (reg8 *) foot2__SIO_REG_HIFREQ)
    #define foot2_SIO_CFG            (* (reg8 *) foot2__SIO_CFG)
    #define foot2_SIO_DIFF           (* (reg8 *) foot2__SIO_DIFF)
#endif /* (foot2__SIO_CFG) */

/* Interrupt Registers */
#if defined(foot2__INTSTAT)
    #define foot2_INTSTAT            (* (reg8 *) foot2__INTSTAT)
    #define foot2_SNAP               (* (reg8 *) foot2__SNAP)
    
	#define foot2_0_INTTYPE_REG 		(* (reg8 *) foot2__0__INTTYPE)
#endif /* (foot2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_foot2_H */


/* [] END OF FILE */
