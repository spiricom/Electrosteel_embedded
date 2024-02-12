/*******************************************************************************
* File Name: highPin.h  
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

#if !defined(CY_PINS_highPin_H) /* Pins highPin_H */
#define CY_PINS_highPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "highPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 highPin__PORT == 15 && ((highPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    highPin_Write(uint8 value);
void    highPin_SetDriveMode(uint8 mode);
uint8   highPin_ReadDataReg(void);
uint8   highPin_Read(void);
void    highPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   highPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the highPin_SetDriveMode() function.
     *  @{
     */
        #define highPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define highPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define highPin_DM_RES_UP          PIN_DM_RES_UP
        #define highPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define highPin_DM_OD_LO           PIN_DM_OD_LO
        #define highPin_DM_OD_HI           PIN_DM_OD_HI
        #define highPin_DM_STRONG          PIN_DM_STRONG
        #define highPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define highPin_MASK               highPin__MASK
#define highPin_SHIFT              highPin__SHIFT
#define highPin_WIDTH              1u

/* Interrupt constants */
#if defined(highPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in highPin_SetInterruptMode() function.
     *  @{
     */
        #define highPin_INTR_NONE      (uint16)(0x0000u)
        #define highPin_INTR_RISING    (uint16)(0x0001u)
        #define highPin_INTR_FALLING   (uint16)(0x0002u)
        #define highPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define highPin_INTR_MASK      (0x01u) 
#endif /* (highPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define highPin_PS                     (* (reg8 *) highPin__PS)
/* Data Register */
#define highPin_DR                     (* (reg8 *) highPin__DR)
/* Port Number */
#define highPin_PRT_NUM                (* (reg8 *) highPin__PRT) 
/* Connect to Analog Globals */                                                  
#define highPin_AG                     (* (reg8 *) highPin__AG)                       
/* Analog MUX bux enable */
#define highPin_AMUX                   (* (reg8 *) highPin__AMUX) 
/* Bidirectional Enable */                                                        
#define highPin_BIE                    (* (reg8 *) highPin__BIE)
/* Bit-mask for Aliased Register Access */
#define highPin_BIT_MASK               (* (reg8 *) highPin__BIT_MASK)
/* Bypass Enable */
#define highPin_BYP                    (* (reg8 *) highPin__BYP)
/* Port wide control signals */                                                   
#define highPin_CTL                    (* (reg8 *) highPin__CTL)
/* Drive Modes */
#define highPin_DM0                    (* (reg8 *) highPin__DM0) 
#define highPin_DM1                    (* (reg8 *) highPin__DM1)
#define highPin_DM2                    (* (reg8 *) highPin__DM2) 
/* Input Buffer Disable Override */
#define highPin_INP_DIS                (* (reg8 *) highPin__INP_DIS)
/* LCD Common or Segment Drive */
#define highPin_LCD_COM_SEG            (* (reg8 *) highPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define highPin_LCD_EN                 (* (reg8 *) highPin__LCD_EN)
/* Slew Rate Control */
#define highPin_SLW                    (* (reg8 *) highPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define highPin_PRTDSI__CAPS_SEL       (* (reg8 *) highPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define highPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) highPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define highPin_PRTDSI__OE_SEL0        (* (reg8 *) highPin__PRTDSI__OE_SEL0) 
#define highPin_PRTDSI__OE_SEL1        (* (reg8 *) highPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define highPin_PRTDSI__OUT_SEL0       (* (reg8 *) highPin__PRTDSI__OUT_SEL0) 
#define highPin_PRTDSI__OUT_SEL1       (* (reg8 *) highPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define highPin_PRTDSI__SYNC_OUT       (* (reg8 *) highPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(highPin__SIO_CFG)
    #define highPin_SIO_HYST_EN        (* (reg8 *) highPin__SIO_HYST_EN)
    #define highPin_SIO_REG_HIFREQ     (* (reg8 *) highPin__SIO_REG_HIFREQ)
    #define highPin_SIO_CFG            (* (reg8 *) highPin__SIO_CFG)
    #define highPin_SIO_DIFF           (* (reg8 *) highPin__SIO_DIFF)
#endif /* (highPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(highPin__INTSTAT)
    #define highPin_INTSTAT            (* (reg8 *) highPin__INTSTAT)
    #define highPin_SNAP               (* (reg8 *) highPin__SNAP)
    
	#define highPin_0_INTTYPE_REG 		(* (reg8 *) highPin__0__INTTYPE)
#endif /* (highPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_highPin_H */


/* [] END OF FILE */
