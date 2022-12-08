/*******************************************************************************
* File Name: highPin1.h  
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

#if !defined(CY_PINS_highPin1_H) /* Pins highPin1_H */
#define CY_PINS_highPin1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "highPin1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 highPin1__PORT == 15 && ((highPin1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    highPin1_Write(uint8 value);
void    highPin1_SetDriveMode(uint8 mode);
uint8   highPin1_ReadDataReg(void);
uint8   highPin1_Read(void);
void    highPin1_SetInterruptMode(uint16 position, uint16 mode);
uint8   highPin1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the highPin1_SetDriveMode() function.
     *  @{
     */
        #define highPin1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define highPin1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define highPin1_DM_RES_UP          PIN_DM_RES_UP
        #define highPin1_DM_RES_DWN         PIN_DM_RES_DWN
        #define highPin1_DM_OD_LO           PIN_DM_OD_LO
        #define highPin1_DM_OD_HI           PIN_DM_OD_HI
        #define highPin1_DM_STRONG          PIN_DM_STRONG
        #define highPin1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define highPin1_MASK               highPin1__MASK
#define highPin1_SHIFT              highPin1__SHIFT
#define highPin1_WIDTH              1u

/* Interrupt constants */
#if defined(highPin1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in highPin1_SetInterruptMode() function.
     *  @{
     */
        #define highPin1_INTR_NONE      (uint16)(0x0000u)
        #define highPin1_INTR_RISING    (uint16)(0x0001u)
        #define highPin1_INTR_FALLING   (uint16)(0x0002u)
        #define highPin1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define highPin1_INTR_MASK      (0x01u) 
#endif /* (highPin1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define highPin1_PS                     (* (reg8 *) highPin1__PS)
/* Data Register */
#define highPin1_DR                     (* (reg8 *) highPin1__DR)
/* Port Number */
#define highPin1_PRT_NUM                (* (reg8 *) highPin1__PRT) 
/* Connect to Analog Globals */                                                  
#define highPin1_AG                     (* (reg8 *) highPin1__AG)                       
/* Analog MUX bux enable */
#define highPin1_AMUX                   (* (reg8 *) highPin1__AMUX) 
/* Bidirectional Enable */                                                        
#define highPin1_BIE                    (* (reg8 *) highPin1__BIE)
/* Bit-mask for Aliased Register Access */
#define highPin1_BIT_MASK               (* (reg8 *) highPin1__BIT_MASK)
/* Bypass Enable */
#define highPin1_BYP                    (* (reg8 *) highPin1__BYP)
/* Port wide control signals */                                                   
#define highPin1_CTL                    (* (reg8 *) highPin1__CTL)
/* Drive Modes */
#define highPin1_DM0                    (* (reg8 *) highPin1__DM0) 
#define highPin1_DM1                    (* (reg8 *) highPin1__DM1)
#define highPin1_DM2                    (* (reg8 *) highPin1__DM2) 
/* Input Buffer Disable Override */
#define highPin1_INP_DIS                (* (reg8 *) highPin1__INP_DIS)
/* LCD Common or Segment Drive */
#define highPin1_LCD_COM_SEG            (* (reg8 *) highPin1__LCD_COM_SEG)
/* Enable Segment LCD */
#define highPin1_LCD_EN                 (* (reg8 *) highPin1__LCD_EN)
/* Slew Rate Control */
#define highPin1_SLW                    (* (reg8 *) highPin1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define highPin1_PRTDSI__CAPS_SEL       (* (reg8 *) highPin1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define highPin1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) highPin1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define highPin1_PRTDSI__OE_SEL0        (* (reg8 *) highPin1__PRTDSI__OE_SEL0) 
#define highPin1_PRTDSI__OE_SEL1        (* (reg8 *) highPin1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define highPin1_PRTDSI__OUT_SEL0       (* (reg8 *) highPin1__PRTDSI__OUT_SEL0) 
#define highPin1_PRTDSI__OUT_SEL1       (* (reg8 *) highPin1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define highPin1_PRTDSI__SYNC_OUT       (* (reg8 *) highPin1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(highPin1__SIO_CFG)
    #define highPin1_SIO_HYST_EN        (* (reg8 *) highPin1__SIO_HYST_EN)
    #define highPin1_SIO_REG_HIFREQ     (* (reg8 *) highPin1__SIO_REG_HIFREQ)
    #define highPin1_SIO_CFG            (* (reg8 *) highPin1__SIO_CFG)
    #define highPin1_SIO_DIFF           (* (reg8 *) highPin1__SIO_DIFF)
#endif /* (highPin1__SIO_CFG) */

/* Interrupt Registers */
#if defined(highPin1__INTSTAT)
    #define highPin1_INTSTAT            (* (reg8 *) highPin1__INTSTAT)
    #define highPin1_SNAP               (* (reg8 *) highPin1__SNAP)
    
	#define highPin1_0_INTTYPE_REG 		(* (reg8 *) highPin1__0__INTTYPE)
#endif /* (highPin1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_highPin1_H */


/* [] END OF FILE */
