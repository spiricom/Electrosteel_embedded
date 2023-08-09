/*******************************************************************************
* File Name: RedLED2.h  
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

#if !defined(CY_PINS_RedLED2_H) /* Pins RedLED2_H */
#define CY_PINS_RedLED2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RedLED2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RedLED2__PORT == 15 && ((RedLED2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RedLED2_Write(uint8 value);
void    RedLED2_SetDriveMode(uint8 mode);
uint8   RedLED2_ReadDataReg(void);
uint8   RedLED2_Read(void);
void    RedLED2_SetInterruptMode(uint16 position, uint16 mode);
uint8   RedLED2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RedLED2_SetDriveMode() function.
     *  @{
     */
        #define RedLED2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RedLED2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RedLED2_DM_RES_UP          PIN_DM_RES_UP
        #define RedLED2_DM_RES_DWN         PIN_DM_RES_DWN
        #define RedLED2_DM_OD_LO           PIN_DM_OD_LO
        #define RedLED2_DM_OD_HI           PIN_DM_OD_HI
        #define RedLED2_DM_STRONG          PIN_DM_STRONG
        #define RedLED2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RedLED2_MASK               RedLED2__MASK
#define RedLED2_SHIFT              RedLED2__SHIFT
#define RedLED2_WIDTH              1u

/* Interrupt constants */
#if defined(RedLED2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RedLED2_SetInterruptMode() function.
     *  @{
     */
        #define RedLED2_INTR_NONE      (uint16)(0x0000u)
        #define RedLED2_INTR_RISING    (uint16)(0x0001u)
        #define RedLED2_INTR_FALLING   (uint16)(0x0002u)
        #define RedLED2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RedLED2_INTR_MASK      (0x01u) 
#endif /* (RedLED2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RedLED2_PS                     (* (reg8 *) RedLED2__PS)
/* Data Register */
#define RedLED2_DR                     (* (reg8 *) RedLED2__DR)
/* Port Number */
#define RedLED2_PRT_NUM                (* (reg8 *) RedLED2__PRT) 
/* Connect to Analog Globals */                                                  
#define RedLED2_AG                     (* (reg8 *) RedLED2__AG)                       
/* Analog MUX bux enable */
#define RedLED2_AMUX                   (* (reg8 *) RedLED2__AMUX) 
/* Bidirectional Enable */                                                        
#define RedLED2_BIE                    (* (reg8 *) RedLED2__BIE)
/* Bit-mask for Aliased Register Access */
#define RedLED2_BIT_MASK               (* (reg8 *) RedLED2__BIT_MASK)
/* Bypass Enable */
#define RedLED2_BYP                    (* (reg8 *) RedLED2__BYP)
/* Port wide control signals */                                                   
#define RedLED2_CTL                    (* (reg8 *) RedLED2__CTL)
/* Drive Modes */
#define RedLED2_DM0                    (* (reg8 *) RedLED2__DM0) 
#define RedLED2_DM1                    (* (reg8 *) RedLED2__DM1)
#define RedLED2_DM2                    (* (reg8 *) RedLED2__DM2) 
/* Input Buffer Disable Override */
#define RedLED2_INP_DIS                (* (reg8 *) RedLED2__INP_DIS)
/* LCD Common or Segment Drive */
#define RedLED2_LCD_COM_SEG            (* (reg8 *) RedLED2__LCD_COM_SEG)
/* Enable Segment LCD */
#define RedLED2_LCD_EN                 (* (reg8 *) RedLED2__LCD_EN)
/* Slew Rate Control */
#define RedLED2_SLW                    (* (reg8 *) RedLED2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RedLED2_PRTDSI__CAPS_SEL       (* (reg8 *) RedLED2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RedLED2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RedLED2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RedLED2_PRTDSI__OE_SEL0        (* (reg8 *) RedLED2__PRTDSI__OE_SEL0) 
#define RedLED2_PRTDSI__OE_SEL1        (* (reg8 *) RedLED2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RedLED2_PRTDSI__OUT_SEL0       (* (reg8 *) RedLED2__PRTDSI__OUT_SEL0) 
#define RedLED2_PRTDSI__OUT_SEL1       (* (reg8 *) RedLED2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RedLED2_PRTDSI__SYNC_OUT       (* (reg8 *) RedLED2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RedLED2__SIO_CFG)
    #define RedLED2_SIO_HYST_EN        (* (reg8 *) RedLED2__SIO_HYST_EN)
    #define RedLED2_SIO_REG_HIFREQ     (* (reg8 *) RedLED2__SIO_REG_HIFREQ)
    #define RedLED2_SIO_CFG            (* (reg8 *) RedLED2__SIO_CFG)
    #define RedLED2_SIO_DIFF           (* (reg8 *) RedLED2__SIO_DIFF)
#endif /* (RedLED2__SIO_CFG) */

/* Interrupt Registers */
#if defined(RedLED2__INTSTAT)
    #define RedLED2_INTSTAT            (* (reg8 *) RedLED2__INTSTAT)
    #define RedLED2_SNAP               (* (reg8 *) RedLED2__SNAP)
    
	#define RedLED2_0_INTTYPE_REG 		(* (reg8 *) RedLED2__0__INTTYPE)
#endif /* (RedLED2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RedLED2_H */


/* [] END OF FILE */
