/*******************************************************************************
* File Name: otherUnused.h  
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

#if !defined(CY_PINS_otherUnused_H) /* Pins otherUnused_H */
#define CY_PINS_otherUnused_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "otherUnused_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 otherUnused__PORT == 15 && ((otherUnused__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    otherUnused_Write(uint8 value);
void    otherUnused_SetDriveMode(uint8 mode);
uint8   otherUnused_ReadDataReg(void);
uint8   otherUnused_Read(void);
void    otherUnused_SetInterruptMode(uint16 position, uint16 mode);
uint8   otherUnused_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the otherUnused_SetDriveMode() function.
     *  @{
     */
        #define otherUnused_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define otherUnused_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define otherUnused_DM_RES_UP          PIN_DM_RES_UP
        #define otherUnused_DM_RES_DWN         PIN_DM_RES_DWN
        #define otherUnused_DM_OD_LO           PIN_DM_OD_LO
        #define otherUnused_DM_OD_HI           PIN_DM_OD_HI
        #define otherUnused_DM_STRONG          PIN_DM_STRONG
        #define otherUnused_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define otherUnused_MASK               otherUnused__MASK
#define otherUnused_SHIFT              otherUnused__SHIFT
#define otherUnused_WIDTH              1u

/* Interrupt constants */
#if defined(otherUnused__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in otherUnused_SetInterruptMode() function.
     *  @{
     */
        #define otherUnused_INTR_NONE      (uint16)(0x0000u)
        #define otherUnused_INTR_RISING    (uint16)(0x0001u)
        #define otherUnused_INTR_FALLING   (uint16)(0x0002u)
        #define otherUnused_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define otherUnused_INTR_MASK      (0x01u) 
#endif /* (otherUnused__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define otherUnused_PS                     (* (reg8 *) otherUnused__PS)
/* Data Register */
#define otherUnused_DR                     (* (reg8 *) otherUnused__DR)
/* Port Number */
#define otherUnused_PRT_NUM                (* (reg8 *) otherUnused__PRT) 
/* Connect to Analog Globals */                                                  
#define otherUnused_AG                     (* (reg8 *) otherUnused__AG)                       
/* Analog MUX bux enable */
#define otherUnused_AMUX                   (* (reg8 *) otherUnused__AMUX) 
/* Bidirectional Enable */                                                        
#define otherUnused_BIE                    (* (reg8 *) otherUnused__BIE)
/* Bit-mask for Aliased Register Access */
#define otherUnused_BIT_MASK               (* (reg8 *) otherUnused__BIT_MASK)
/* Bypass Enable */
#define otherUnused_BYP                    (* (reg8 *) otherUnused__BYP)
/* Port wide control signals */                                                   
#define otherUnused_CTL                    (* (reg8 *) otherUnused__CTL)
/* Drive Modes */
#define otherUnused_DM0                    (* (reg8 *) otherUnused__DM0) 
#define otherUnused_DM1                    (* (reg8 *) otherUnused__DM1)
#define otherUnused_DM2                    (* (reg8 *) otherUnused__DM2) 
/* Input Buffer Disable Override */
#define otherUnused_INP_DIS                (* (reg8 *) otherUnused__INP_DIS)
/* LCD Common or Segment Drive */
#define otherUnused_LCD_COM_SEG            (* (reg8 *) otherUnused__LCD_COM_SEG)
/* Enable Segment LCD */
#define otherUnused_LCD_EN                 (* (reg8 *) otherUnused__LCD_EN)
/* Slew Rate Control */
#define otherUnused_SLW                    (* (reg8 *) otherUnused__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define otherUnused_PRTDSI__CAPS_SEL       (* (reg8 *) otherUnused__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define otherUnused_PRTDSI__DBL_SYNC_IN    (* (reg8 *) otherUnused__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define otherUnused_PRTDSI__OE_SEL0        (* (reg8 *) otherUnused__PRTDSI__OE_SEL0) 
#define otherUnused_PRTDSI__OE_SEL1        (* (reg8 *) otherUnused__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define otherUnused_PRTDSI__OUT_SEL0       (* (reg8 *) otherUnused__PRTDSI__OUT_SEL0) 
#define otherUnused_PRTDSI__OUT_SEL1       (* (reg8 *) otherUnused__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define otherUnused_PRTDSI__SYNC_OUT       (* (reg8 *) otherUnused__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(otherUnused__SIO_CFG)
    #define otherUnused_SIO_HYST_EN        (* (reg8 *) otherUnused__SIO_HYST_EN)
    #define otherUnused_SIO_REG_HIFREQ     (* (reg8 *) otherUnused__SIO_REG_HIFREQ)
    #define otherUnused_SIO_CFG            (* (reg8 *) otherUnused__SIO_CFG)
    #define otherUnused_SIO_DIFF           (* (reg8 *) otherUnused__SIO_DIFF)
#endif /* (otherUnused__SIO_CFG) */

/* Interrupt Registers */
#if defined(otherUnused__INTSTAT)
    #define otherUnused_INTSTAT            (* (reg8 *) otherUnused__INTSTAT)
    #define otherUnused_SNAP               (* (reg8 *) otherUnused__SNAP)
    
	#define otherUnused_0_INTTYPE_REG 		(* (reg8 *) otherUnused__0__INTTYPE)
#endif /* (otherUnused__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_otherUnused_H */


/* [] END OF FILE */
