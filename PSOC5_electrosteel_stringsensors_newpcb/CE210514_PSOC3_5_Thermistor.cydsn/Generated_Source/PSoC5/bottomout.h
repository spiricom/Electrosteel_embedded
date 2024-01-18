/*******************************************************************************
* File Name: bottomout.h  
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

#if !defined(CY_PINS_bottomout_H) /* Pins bottomout_H */
#define CY_PINS_bottomout_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "bottomout_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 bottomout__PORT == 15 && ((bottomout__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    bottomout_Write(uint8 value);
void    bottomout_SetDriveMode(uint8 mode);
uint8   bottomout_ReadDataReg(void);
uint8   bottomout_Read(void);
void    bottomout_SetInterruptMode(uint16 position, uint16 mode);
uint8   bottomout_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the bottomout_SetDriveMode() function.
     *  @{
     */
        #define bottomout_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define bottomout_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define bottomout_DM_RES_UP          PIN_DM_RES_UP
        #define bottomout_DM_RES_DWN         PIN_DM_RES_DWN
        #define bottomout_DM_OD_LO           PIN_DM_OD_LO
        #define bottomout_DM_OD_HI           PIN_DM_OD_HI
        #define bottomout_DM_STRONG          PIN_DM_STRONG
        #define bottomout_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define bottomout_MASK               bottomout__MASK
#define bottomout_SHIFT              bottomout__SHIFT
#define bottomout_WIDTH              1u

/* Interrupt constants */
#if defined(bottomout__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in bottomout_SetInterruptMode() function.
     *  @{
     */
        #define bottomout_INTR_NONE      (uint16)(0x0000u)
        #define bottomout_INTR_RISING    (uint16)(0x0001u)
        #define bottomout_INTR_FALLING   (uint16)(0x0002u)
        #define bottomout_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define bottomout_INTR_MASK      (0x01u) 
#endif /* (bottomout__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define bottomout_PS                     (* (reg8 *) bottomout__PS)
/* Data Register */
#define bottomout_DR                     (* (reg8 *) bottomout__DR)
/* Port Number */
#define bottomout_PRT_NUM                (* (reg8 *) bottomout__PRT) 
/* Connect to Analog Globals */                                                  
#define bottomout_AG                     (* (reg8 *) bottomout__AG)                       
/* Analog MUX bux enable */
#define bottomout_AMUX                   (* (reg8 *) bottomout__AMUX) 
/* Bidirectional Enable */                                                        
#define bottomout_BIE                    (* (reg8 *) bottomout__BIE)
/* Bit-mask for Aliased Register Access */
#define bottomout_BIT_MASK               (* (reg8 *) bottomout__BIT_MASK)
/* Bypass Enable */
#define bottomout_BYP                    (* (reg8 *) bottomout__BYP)
/* Port wide control signals */                                                   
#define bottomout_CTL                    (* (reg8 *) bottomout__CTL)
/* Drive Modes */
#define bottomout_DM0                    (* (reg8 *) bottomout__DM0) 
#define bottomout_DM1                    (* (reg8 *) bottomout__DM1)
#define bottomout_DM2                    (* (reg8 *) bottomout__DM2) 
/* Input Buffer Disable Override */
#define bottomout_INP_DIS                (* (reg8 *) bottomout__INP_DIS)
/* LCD Common or Segment Drive */
#define bottomout_LCD_COM_SEG            (* (reg8 *) bottomout__LCD_COM_SEG)
/* Enable Segment LCD */
#define bottomout_LCD_EN                 (* (reg8 *) bottomout__LCD_EN)
/* Slew Rate Control */
#define bottomout_SLW                    (* (reg8 *) bottomout__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define bottomout_PRTDSI__CAPS_SEL       (* (reg8 *) bottomout__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define bottomout_PRTDSI__DBL_SYNC_IN    (* (reg8 *) bottomout__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define bottomout_PRTDSI__OE_SEL0        (* (reg8 *) bottomout__PRTDSI__OE_SEL0) 
#define bottomout_PRTDSI__OE_SEL1        (* (reg8 *) bottomout__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define bottomout_PRTDSI__OUT_SEL0       (* (reg8 *) bottomout__PRTDSI__OUT_SEL0) 
#define bottomout_PRTDSI__OUT_SEL1       (* (reg8 *) bottomout__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define bottomout_PRTDSI__SYNC_OUT       (* (reg8 *) bottomout__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(bottomout__SIO_CFG)
    #define bottomout_SIO_HYST_EN        (* (reg8 *) bottomout__SIO_HYST_EN)
    #define bottomout_SIO_REG_HIFREQ     (* (reg8 *) bottomout__SIO_REG_HIFREQ)
    #define bottomout_SIO_CFG            (* (reg8 *) bottomout__SIO_CFG)
    #define bottomout_SIO_DIFF           (* (reg8 *) bottomout__SIO_DIFF)
#endif /* (bottomout__SIO_CFG) */

/* Interrupt Registers */
#if defined(bottomout__INTSTAT)
    #define bottomout_INTSTAT            (* (reg8 *) bottomout__INTSTAT)
    #define bottomout_SNAP               (* (reg8 *) bottomout__SNAP)
    
	#define bottomout_0_INTTYPE_REG 		(* (reg8 *) bottomout__0__INTTYPE)
#endif /* (bottomout__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_bottomout_H */


/* [] END OF FILE */
