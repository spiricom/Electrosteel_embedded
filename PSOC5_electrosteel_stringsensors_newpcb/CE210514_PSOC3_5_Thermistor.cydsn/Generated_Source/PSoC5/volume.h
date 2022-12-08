/*******************************************************************************
* File Name: volume.h  
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

#if !defined(CY_PINS_volume_H) /* Pins volume_H */
#define CY_PINS_volume_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "volume_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 volume__PORT == 15 && ((volume__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    volume_Write(uint8 value);
void    volume_SetDriveMode(uint8 mode);
uint8   volume_ReadDataReg(void);
uint8   volume_Read(void);
void    volume_SetInterruptMode(uint16 position, uint16 mode);
uint8   volume_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the volume_SetDriveMode() function.
     *  @{
     */
        #define volume_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define volume_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define volume_DM_RES_UP          PIN_DM_RES_UP
        #define volume_DM_RES_DWN         PIN_DM_RES_DWN
        #define volume_DM_OD_LO           PIN_DM_OD_LO
        #define volume_DM_OD_HI           PIN_DM_OD_HI
        #define volume_DM_STRONG          PIN_DM_STRONG
        #define volume_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define volume_MASK               volume__MASK
#define volume_SHIFT              volume__SHIFT
#define volume_WIDTH              1u

/* Interrupt constants */
#if defined(volume__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in volume_SetInterruptMode() function.
     *  @{
     */
        #define volume_INTR_NONE      (uint16)(0x0000u)
        #define volume_INTR_RISING    (uint16)(0x0001u)
        #define volume_INTR_FALLING   (uint16)(0x0002u)
        #define volume_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define volume_INTR_MASK      (0x01u) 
#endif /* (volume__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define volume_PS                     (* (reg8 *) volume__PS)
/* Data Register */
#define volume_DR                     (* (reg8 *) volume__DR)
/* Port Number */
#define volume_PRT_NUM                (* (reg8 *) volume__PRT) 
/* Connect to Analog Globals */                                                  
#define volume_AG                     (* (reg8 *) volume__AG)                       
/* Analog MUX bux enable */
#define volume_AMUX                   (* (reg8 *) volume__AMUX) 
/* Bidirectional Enable */                                                        
#define volume_BIE                    (* (reg8 *) volume__BIE)
/* Bit-mask for Aliased Register Access */
#define volume_BIT_MASK               (* (reg8 *) volume__BIT_MASK)
/* Bypass Enable */
#define volume_BYP                    (* (reg8 *) volume__BYP)
/* Port wide control signals */                                                   
#define volume_CTL                    (* (reg8 *) volume__CTL)
/* Drive Modes */
#define volume_DM0                    (* (reg8 *) volume__DM0) 
#define volume_DM1                    (* (reg8 *) volume__DM1)
#define volume_DM2                    (* (reg8 *) volume__DM2) 
/* Input Buffer Disable Override */
#define volume_INP_DIS                (* (reg8 *) volume__INP_DIS)
/* LCD Common or Segment Drive */
#define volume_LCD_COM_SEG            (* (reg8 *) volume__LCD_COM_SEG)
/* Enable Segment LCD */
#define volume_LCD_EN                 (* (reg8 *) volume__LCD_EN)
/* Slew Rate Control */
#define volume_SLW                    (* (reg8 *) volume__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define volume_PRTDSI__CAPS_SEL       (* (reg8 *) volume__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define volume_PRTDSI__DBL_SYNC_IN    (* (reg8 *) volume__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define volume_PRTDSI__OE_SEL0        (* (reg8 *) volume__PRTDSI__OE_SEL0) 
#define volume_PRTDSI__OE_SEL1        (* (reg8 *) volume__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define volume_PRTDSI__OUT_SEL0       (* (reg8 *) volume__PRTDSI__OUT_SEL0) 
#define volume_PRTDSI__OUT_SEL1       (* (reg8 *) volume__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define volume_PRTDSI__SYNC_OUT       (* (reg8 *) volume__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(volume__SIO_CFG)
    #define volume_SIO_HYST_EN        (* (reg8 *) volume__SIO_HYST_EN)
    #define volume_SIO_REG_HIFREQ     (* (reg8 *) volume__SIO_REG_HIFREQ)
    #define volume_SIO_CFG            (* (reg8 *) volume__SIO_CFG)
    #define volume_SIO_DIFF           (* (reg8 *) volume__SIO_DIFF)
#endif /* (volume__SIO_CFG) */

/* Interrupt Registers */
#if defined(volume__INTSTAT)
    #define volume_INTSTAT            (* (reg8 *) volume__INTSTAT)
    #define volume_SNAP               (* (reg8 *) volume__SNAP)
    
	#define volume_0_INTTYPE_REG 		(* (reg8 *) volume__0__INTTYPE)
#endif /* (volume__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_volume_H */


/* [] END OF FILE */
