/*******************************************************************************
* File Name: highPin2.h  
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

#if !defined(CY_PINS_highPin2_H) /* Pins highPin2_H */
#define CY_PINS_highPin2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "highPin2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 highPin2__PORT == 15 && ((highPin2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    highPin2_Write(uint8 value);
void    highPin2_SetDriveMode(uint8 mode);
uint8   highPin2_ReadDataReg(void);
uint8   highPin2_Read(void);
void    highPin2_SetInterruptMode(uint16 position, uint16 mode);
uint8   highPin2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the highPin2_SetDriveMode() function.
     *  @{
     */
        #define highPin2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define highPin2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define highPin2_DM_RES_UP          PIN_DM_RES_UP
        #define highPin2_DM_RES_DWN         PIN_DM_RES_DWN
        #define highPin2_DM_OD_LO           PIN_DM_OD_LO
        #define highPin2_DM_OD_HI           PIN_DM_OD_HI
        #define highPin2_DM_STRONG          PIN_DM_STRONG
        #define highPin2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define highPin2_MASK               highPin2__MASK
#define highPin2_SHIFT              highPin2__SHIFT
#define highPin2_WIDTH              1u

/* Interrupt constants */
#if defined(highPin2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in highPin2_SetInterruptMode() function.
     *  @{
     */
        #define highPin2_INTR_NONE      (uint16)(0x0000u)
        #define highPin2_INTR_RISING    (uint16)(0x0001u)
        #define highPin2_INTR_FALLING   (uint16)(0x0002u)
        #define highPin2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define highPin2_INTR_MASK      (0x01u) 
#endif /* (highPin2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define highPin2_PS                     (* (reg8 *) highPin2__PS)
/* Data Register */
#define highPin2_DR                     (* (reg8 *) highPin2__DR)
/* Port Number */
#define highPin2_PRT_NUM                (* (reg8 *) highPin2__PRT) 
/* Connect to Analog Globals */                                                  
#define highPin2_AG                     (* (reg8 *) highPin2__AG)                       
/* Analog MUX bux enable */
#define highPin2_AMUX                   (* (reg8 *) highPin2__AMUX) 
/* Bidirectional Enable */                                                        
#define highPin2_BIE                    (* (reg8 *) highPin2__BIE)
/* Bit-mask for Aliased Register Access */
#define highPin2_BIT_MASK               (* (reg8 *) highPin2__BIT_MASK)
/* Bypass Enable */
#define highPin2_BYP                    (* (reg8 *) highPin2__BYP)
/* Port wide control signals */                                                   
#define highPin2_CTL                    (* (reg8 *) highPin2__CTL)
/* Drive Modes */
#define highPin2_DM0                    (* (reg8 *) highPin2__DM0) 
#define highPin2_DM1                    (* (reg8 *) highPin2__DM1)
#define highPin2_DM2                    (* (reg8 *) highPin2__DM2) 
/* Input Buffer Disable Override */
#define highPin2_INP_DIS                (* (reg8 *) highPin2__INP_DIS)
/* LCD Common or Segment Drive */
#define highPin2_LCD_COM_SEG            (* (reg8 *) highPin2__LCD_COM_SEG)
/* Enable Segment LCD */
#define highPin2_LCD_EN                 (* (reg8 *) highPin2__LCD_EN)
/* Slew Rate Control */
#define highPin2_SLW                    (* (reg8 *) highPin2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define highPin2_PRTDSI__CAPS_SEL       (* (reg8 *) highPin2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define highPin2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) highPin2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define highPin2_PRTDSI__OE_SEL0        (* (reg8 *) highPin2__PRTDSI__OE_SEL0) 
#define highPin2_PRTDSI__OE_SEL1        (* (reg8 *) highPin2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define highPin2_PRTDSI__OUT_SEL0       (* (reg8 *) highPin2__PRTDSI__OUT_SEL0) 
#define highPin2_PRTDSI__OUT_SEL1       (* (reg8 *) highPin2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define highPin2_PRTDSI__SYNC_OUT       (* (reg8 *) highPin2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(highPin2__SIO_CFG)
    #define highPin2_SIO_HYST_EN        (* (reg8 *) highPin2__SIO_HYST_EN)
    #define highPin2_SIO_REG_HIFREQ     (* (reg8 *) highPin2__SIO_REG_HIFREQ)
    #define highPin2_SIO_CFG            (* (reg8 *) highPin2__SIO_CFG)
    #define highPin2_SIO_DIFF           (* (reg8 *) highPin2__SIO_DIFF)
#endif /* (highPin2__SIO_CFG) */

/* Interrupt Registers */
#if defined(highPin2__INTSTAT)
    #define highPin2_INTSTAT            (* (reg8 *) highPin2__INTSTAT)
    #define highPin2_SNAP               (* (reg8 *) highPin2__SNAP)
    
	#define highPin2_0_INTTYPE_REG 		(* (reg8 *) highPin2__0__INTTYPE)
#endif /* (highPin2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_highPin2_H */


/* [] END OF FILE */
