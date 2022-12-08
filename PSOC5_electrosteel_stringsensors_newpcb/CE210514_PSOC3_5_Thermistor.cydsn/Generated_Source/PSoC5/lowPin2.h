/*******************************************************************************
* File Name: lowPin2.h  
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

#if !defined(CY_PINS_lowPin2_H) /* Pins lowPin2_H */
#define CY_PINS_lowPin2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "lowPin2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 lowPin2__PORT == 15 && ((lowPin2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    lowPin2_Write(uint8 value);
void    lowPin2_SetDriveMode(uint8 mode);
uint8   lowPin2_ReadDataReg(void);
uint8   lowPin2_Read(void);
void    lowPin2_SetInterruptMode(uint16 position, uint16 mode);
uint8   lowPin2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the lowPin2_SetDriveMode() function.
     *  @{
     */
        #define lowPin2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define lowPin2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define lowPin2_DM_RES_UP          PIN_DM_RES_UP
        #define lowPin2_DM_RES_DWN         PIN_DM_RES_DWN
        #define lowPin2_DM_OD_LO           PIN_DM_OD_LO
        #define lowPin2_DM_OD_HI           PIN_DM_OD_HI
        #define lowPin2_DM_STRONG          PIN_DM_STRONG
        #define lowPin2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define lowPin2_MASK               lowPin2__MASK
#define lowPin2_SHIFT              lowPin2__SHIFT
#define lowPin2_WIDTH              1u

/* Interrupt constants */
#if defined(lowPin2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in lowPin2_SetInterruptMode() function.
     *  @{
     */
        #define lowPin2_INTR_NONE      (uint16)(0x0000u)
        #define lowPin2_INTR_RISING    (uint16)(0x0001u)
        #define lowPin2_INTR_FALLING   (uint16)(0x0002u)
        #define lowPin2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define lowPin2_INTR_MASK      (0x01u) 
#endif /* (lowPin2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define lowPin2_PS                     (* (reg8 *) lowPin2__PS)
/* Data Register */
#define lowPin2_DR                     (* (reg8 *) lowPin2__DR)
/* Port Number */
#define lowPin2_PRT_NUM                (* (reg8 *) lowPin2__PRT) 
/* Connect to Analog Globals */                                                  
#define lowPin2_AG                     (* (reg8 *) lowPin2__AG)                       
/* Analog MUX bux enable */
#define lowPin2_AMUX                   (* (reg8 *) lowPin2__AMUX) 
/* Bidirectional Enable */                                                        
#define lowPin2_BIE                    (* (reg8 *) lowPin2__BIE)
/* Bit-mask for Aliased Register Access */
#define lowPin2_BIT_MASK               (* (reg8 *) lowPin2__BIT_MASK)
/* Bypass Enable */
#define lowPin2_BYP                    (* (reg8 *) lowPin2__BYP)
/* Port wide control signals */                                                   
#define lowPin2_CTL                    (* (reg8 *) lowPin2__CTL)
/* Drive Modes */
#define lowPin2_DM0                    (* (reg8 *) lowPin2__DM0) 
#define lowPin2_DM1                    (* (reg8 *) lowPin2__DM1)
#define lowPin2_DM2                    (* (reg8 *) lowPin2__DM2) 
/* Input Buffer Disable Override */
#define lowPin2_INP_DIS                (* (reg8 *) lowPin2__INP_DIS)
/* LCD Common or Segment Drive */
#define lowPin2_LCD_COM_SEG            (* (reg8 *) lowPin2__LCD_COM_SEG)
/* Enable Segment LCD */
#define lowPin2_LCD_EN                 (* (reg8 *) lowPin2__LCD_EN)
/* Slew Rate Control */
#define lowPin2_SLW                    (* (reg8 *) lowPin2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define lowPin2_PRTDSI__CAPS_SEL       (* (reg8 *) lowPin2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define lowPin2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) lowPin2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define lowPin2_PRTDSI__OE_SEL0        (* (reg8 *) lowPin2__PRTDSI__OE_SEL0) 
#define lowPin2_PRTDSI__OE_SEL1        (* (reg8 *) lowPin2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define lowPin2_PRTDSI__OUT_SEL0       (* (reg8 *) lowPin2__PRTDSI__OUT_SEL0) 
#define lowPin2_PRTDSI__OUT_SEL1       (* (reg8 *) lowPin2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define lowPin2_PRTDSI__SYNC_OUT       (* (reg8 *) lowPin2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(lowPin2__SIO_CFG)
    #define lowPin2_SIO_HYST_EN        (* (reg8 *) lowPin2__SIO_HYST_EN)
    #define lowPin2_SIO_REG_HIFREQ     (* (reg8 *) lowPin2__SIO_REG_HIFREQ)
    #define lowPin2_SIO_CFG            (* (reg8 *) lowPin2__SIO_CFG)
    #define lowPin2_SIO_DIFF           (* (reg8 *) lowPin2__SIO_DIFF)
#endif /* (lowPin2__SIO_CFG) */

/* Interrupt Registers */
#if defined(lowPin2__INTSTAT)
    #define lowPin2_INTSTAT            (* (reg8 *) lowPin2__INTSTAT)
    #define lowPin2_SNAP               (* (reg8 *) lowPin2__SNAP)
    
	#define lowPin2_0_INTTYPE_REG 		(* (reg8 *) lowPin2__0__INTTYPE)
#endif /* (lowPin2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_lowPin2_H */


/* [] END OF FILE */
