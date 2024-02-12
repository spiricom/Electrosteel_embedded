/*******************************************************************************
* File Name: VH.h  
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

#if !defined(CY_PINS_VH_H) /* Pins VH_H */
#define CY_PINS_VH_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "VH_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 VH__PORT == 15 && ((VH__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    VH_Write(uint8 value);
void    VH_SetDriveMode(uint8 mode);
uint8   VH_ReadDataReg(void);
uint8   VH_Read(void);
void    VH_SetInterruptMode(uint16 position, uint16 mode);
uint8   VH_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the VH_SetDriveMode() function.
     *  @{
     */
        #define VH_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define VH_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define VH_DM_RES_UP          PIN_DM_RES_UP
        #define VH_DM_RES_DWN         PIN_DM_RES_DWN
        #define VH_DM_OD_LO           PIN_DM_OD_LO
        #define VH_DM_OD_HI           PIN_DM_OD_HI
        #define VH_DM_STRONG          PIN_DM_STRONG
        #define VH_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define VH_MASK               VH__MASK
#define VH_SHIFT              VH__SHIFT
#define VH_WIDTH              1u

/* Interrupt constants */
#if defined(VH__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VH_SetInterruptMode() function.
     *  @{
     */
        #define VH_INTR_NONE      (uint16)(0x0000u)
        #define VH_INTR_RISING    (uint16)(0x0001u)
        #define VH_INTR_FALLING   (uint16)(0x0002u)
        #define VH_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define VH_INTR_MASK      (0x01u) 
#endif /* (VH__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VH_PS                     (* (reg8 *) VH__PS)
/* Data Register */
#define VH_DR                     (* (reg8 *) VH__DR)
/* Port Number */
#define VH_PRT_NUM                (* (reg8 *) VH__PRT) 
/* Connect to Analog Globals */                                                  
#define VH_AG                     (* (reg8 *) VH__AG)                       
/* Analog MUX bux enable */
#define VH_AMUX                   (* (reg8 *) VH__AMUX) 
/* Bidirectional Enable */                                                        
#define VH_BIE                    (* (reg8 *) VH__BIE)
/* Bit-mask for Aliased Register Access */
#define VH_BIT_MASK               (* (reg8 *) VH__BIT_MASK)
/* Bypass Enable */
#define VH_BYP                    (* (reg8 *) VH__BYP)
/* Port wide control signals */                                                   
#define VH_CTL                    (* (reg8 *) VH__CTL)
/* Drive Modes */
#define VH_DM0                    (* (reg8 *) VH__DM0) 
#define VH_DM1                    (* (reg8 *) VH__DM1)
#define VH_DM2                    (* (reg8 *) VH__DM2) 
/* Input Buffer Disable Override */
#define VH_INP_DIS                (* (reg8 *) VH__INP_DIS)
/* LCD Common or Segment Drive */
#define VH_LCD_COM_SEG            (* (reg8 *) VH__LCD_COM_SEG)
/* Enable Segment LCD */
#define VH_LCD_EN                 (* (reg8 *) VH__LCD_EN)
/* Slew Rate Control */
#define VH_SLW                    (* (reg8 *) VH__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VH_PRTDSI__CAPS_SEL       (* (reg8 *) VH__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VH_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VH__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VH_PRTDSI__OE_SEL0        (* (reg8 *) VH__PRTDSI__OE_SEL0) 
#define VH_PRTDSI__OE_SEL1        (* (reg8 *) VH__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VH_PRTDSI__OUT_SEL0       (* (reg8 *) VH__PRTDSI__OUT_SEL0) 
#define VH_PRTDSI__OUT_SEL1       (* (reg8 *) VH__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VH_PRTDSI__SYNC_OUT       (* (reg8 *) VH__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(VH__SIO_CFG)
    #define VH_SIO_HYST_EN        (* (reg8 *) VH__SIO_HYST_EN)
    #define VH_SIO_REG_HIFREQ     (* (reg8 *) VH__SIO_REG_HIFREQ)
    #define VH_SIO_CFG            (* (reg8 *) VH__SIO_CFG)
    #define VH_SIO_DIFF           (* (reg8 *) VH__SIO_DIFF)
#endif /* (VH__SIO_CFG) */

/* Interrupt Registers */
#if defined(VH__INTSTAT)
    #define VH_INTSTAT            (* (reg8 *) VH__INTSTAT)
    #define VH_SNAP               (* (reg8 *) VH__SNAP)
    
	#define VH_0_INTTYPE_REG 		(* (reg8 *) VH__0__INTTYPE)
#endif /* (VH__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_VH_H */


/* [] END OF FILE */
