/*******************************************************************************
* File Name: VHout.h  
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

#if !defined(CY_PINS_VHout_H) /* Pins VHout_H */
#define CY_PINS_VHout_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "VHout_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 VHout__PORT == 15 && ((VHout__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    VHout_Write(uint8 value);
void    VHout_SetDriveMode(uint8 mode);
uint8   VHout_ReadDataReg(void);
uint8   VHout_Read(void);
void    VHout_SetInterruptMode(uint16 position, uint16 mode);
uint8   VHout_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the VHout_SetDriveMode() function.
     *  @{
     */
        #define VHout_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define VHout_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define VHout_DM_RES_UP          PIN_DM_RES_UP
        #define VHout_DM_RES_DWN         PIN_DM_RES_DWN
        #define VHout_DM_OD_LO           PIN_DM_OD_LO
        #define VHout_DM_OD_HI           PIN_DM_OD_HI
        #define VHout_DM_STRONG          PIN_DM_STRONG
        #define VHout_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define VHout_MASK               VHout__MASK
#define VHout_SHIFT              VHout__SHIFT
#define VHout_WIDTH              1u

/* Interrupt constants */
#if defined(VHout__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VHout_SetInterruptMode() function.
     *  @{
     */
        #define VHout_INTR_NONE      (uint16)(0x0000u)
        #define VHout_INTR_RISING    (uint16)(0x0001u)
        #define VHout_INTR_FALLING   (uint16)(0x0002u)
        #define VHout_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define VHout_INTR_MASK      (0x01u) 
#endif /* (VHout__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VHout_PS                     (* (reg8 *) VHout__PS)
/* Data Register */
#define VHout_DR                     (* (reg8 *) VHout__DR)
/* Port Number */
#define VHout_PRT_NUM                (* (reg8 *) VHout__PRT) 
/* Connect to Analog Globals */                                                  
#define VHout_AG                     (* (reg8 *) VHout__AG)                       
/* Analog MUX bux enable */
#define VHout_AMUX                   (* (reg8 *) VHout__AMUX) 
/* Bidirectional Enable */                                                        
#define VHout_BIE                    (* (reg8 *) VHout__BIE)
/* Bit-mask for Aliased Register Access */
#define VHout_BIT_MASK               (* (reg8 *) VHout__BIT_MASK)
/* Bypass Enable */
#define VHout_BYP                    (* (reg8 *) VHout__BYP)
/* Port wide control signals */                                                   
#define VHout_CTL                    (* (reg8 *) VHout__CTL)
/* Drive Modes */
#define VHout_DM0                    (* (reg8 *) VHout__DM0) 
#define VHout_DM1                    (* (reg8 *) VHout__DM1)
#define VHout_DM2                    (* (reg8 *) VHout__DM2) 
/* Input Buffer Disable Override */
#define VHout_INP_DIS                (* (reg8 *) VHout__INP_DIS)
/* LCD Common or Segment Drive */
#define VHout_LCD_COM_SEG            (* (reg8 *) VHout__LCD_COM_SEG)
/* Enable Segment LCD */
#define VHout_LCD_EN                 (* (reg8 *) VHout__LCD_EN)
/* Slew Rate Control */
#define VHout_SLW                    (* (reg8 *) VHout__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VHout_PRTDSI__CAPS_SEL       (* (reg8 *) VHout__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VHout_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VHout__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VHout_PRTDSI__OE_SEL0        (* (reg8 *) VHout__PRTDSI__OE_SEL0) 
#define VHout_PRTDSI__OE_SEL1        (* (reg8 *) VHout__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VHout_PRTDSI__OUT_SEL0       (* (reg8 *) VHout__PRTDSI__OUT_SEL0) 
#define VHout_PRTDSI__OUT_SEL1       (* (reg8 *) VHout__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VHout_PRTDSI__SYNC_OUT       (* (reg8 *) VHout__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(VHout__SIO_CFG)
    #define VHout_SIO_HYST_EN        (* (reg8 *) VHout__SIO_HYST_EN)
    #define VHout_SIO_REG_HIFREQ     (* (reg8 *) VHout__SIO_REG_HIFREQ)
    #define VHout_SIO_CFG            (* (reg8 *) VHout__SIO_CFG)
    #define VHout_SIO_DIFF           (* (reg8 *) VHout__SIO_DIFF)
#endif /* (VHout__SIO_CFG) */

/* Interrupt Registers */
#if defined(VHout__INTSTAT)
    #define VHout_INTSTAT            (* (reg8 *) VHout__INTSTAT)
    #define VHout_SNAP               (* (reg8 *) VHout__SNAP)
    
	#define VHout_0_INTTYPE_REG 		(* (reg8 *) VHout__0__INTTYPE)
#endif /* (VHout__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_VHout_H */


/* [] END OF FILE */
