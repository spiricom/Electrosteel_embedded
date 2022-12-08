/*******************************************************************************
* File Name: lowPin.h  
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

#if !defined(CY_PINS_lowPin_H) /* Pins lowPin_H */
#define CY_PINS_lowPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "lowPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 lowPin__PORT == 15 && ((lowPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    lowPin_Write(uint8 value);
void    lowPin_SetDriveMode(uint8 mode);
uint8   lowPin_ReadDataReg(void);
uint8   lowPin_Read(void);
void    lowPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   lowPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the lowPin_SetDriveMode() function.
     *  @{
     */
        #define lowPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define lowPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define lowPin_DM_RES_UP          PIN_DM_RES_UP
        #define lowPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define lowPin_DM_OD_LO           PIN_DM_OD_LO
        #define lowPin_DM_OD_HI           PIN_DM_OD_HI
        #define lowPin_DM_STRONG          PIN_DM_STRONG
        #define lowPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define lowPin_MASK               lowPin__MASK
#define lowPin_SHIFT              lowPin__SHIFT
#define lowPin_WIDTH              1u

/* Interrupt constants */
#if defined(lowPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in lowPin_SetInterruptMode() function.
     *  @{
     */
        #define lowPin_INTR_NONE      (uint16)(0x0000u)
        #define lowPin_INTR_RISING    (uint16)(0x0001u)
        #define lowPin_INTR_FALLING   (uint16)(0x0002u)
        #define lowPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define lowPin_INTR_MASK      (0x01u) 
#endif /* (lowPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define lowPin_PS                     (* (reg8 *) lowPin__PS)
/* Data Register */
#define lowPin_DR                     (* (reg8 *) lowPin__DR)
/* Port Number */
#define lowPin_PRT_NUM                (* (reg8 *) lowPin__PRT) 
/* Connect to Analog Globals */                                                  
#define lowPin_AG                     (* (reg8 *) lowPin__AG)                       
/* Analog MUX bux enable */
#define lowPin_AMUX                   (* (reg8 *) lowPin__AMUX) 
/* Bidirectional Enable */                                                        
#define lowPin_BIE                    (* (reg8 *) lowPin__BIE)
/* Bit-mask for Aliased Register Access */
#define lowPin_BIT_MASK               (* (reg8 *) lowPin__BIT_MASK)
/* Bypass Enable */
#define lowPin_BYP                    (* (reg8 *) lowPin__BYP)
/* Port wide control signals */                                                   
#define lowPin_CTL                    (* (reg8 *) lowPin__CTL)
/* Drive Modes */
#define lowPin_DM0                    (* (reg8 *) lowPin__DM0) 
#define lowPin_DM1                    (* (reg8 *) lowPin__DM1)
#define lowPin_DM2                    (* (reg8 *) lowPin__DM2) 
/* Input Buffer Disable Override */
#define lowPin_INP_DIS                (* (reg8 *) lowPin__INP_DIS)
/* LCD Common or Segment Drive */
#define lowPin_LCD_COM_SEG            (* (reg8 *) lowPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define lowPin_LCD_EN                 (* (reg8 *) lowPin__LCD_EN)
/* Slew Rate Control */
#define lowPin_SLW                    (* (reg8 *) lowPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define lowPin_PRTDSI__CAPS_SEL       (* (reg8 *) lowPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define lowPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) lowPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define lowPin_PRTDSI__OE_SEL0        (* (reg8 *) lowPin__PRTDSI__OE_SEL0) 
#define lowPin_PRTDSI__OE_SEL1        (* (reg8 *) lowPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define lowPin_PRTDSI__OUT_SEL0       (* (reg8 *) lowPin__PRTDSI__OUT_SEL0) 
#define lowPin_PRTDSI__OUT_SEL1       (* (reg8 *) lowPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define lowPin_PRTDSI__SYNC_OUT       (* (reg8 *) lowPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(lowPin__SIO_CFG)
    #define lowPin_SIO_HYST_EN        (* (reg8 *) lowPin__SIO_HYST_EN)
    #define lowPin_SIO_REG_HIFREQ     (* (reg8 *) lowPin__SIO_REG_HIFREQ)
    #define lowPin_SIO_CFG            (* (reg8 *) lowPin__SIO_CFG)
    #define lowPin_SIO_DIFF           (* (reg8 *) lowPin__SIO_DIFF)
#endif /* (lowPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(lowPin__INTSTAT)
    #define lowPin_INTSTAT            (* (reg8 *) lowPin__INTSTAT)
    #define lowPin_SNAP               (* (reg8 *) lowPin__SNAP)
    
	#define lowPin_0_INTTYPE_REG 		(* (reg8 *) lowPin__0__INTTYPE)
#endif /* (lowPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_lowPin_H */


/* [] END OF FILE */
