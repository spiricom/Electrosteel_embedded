/*******************************************************************************
* File Name: GreenLED2.h  
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

#if !defined(CY_PINS_GreenLED2_H) /* Pins GreenLED2_H */
#define CY_PINS_GreenLED2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "GreenLED2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 GreenLED2__PORT == 15 && ((GreenLED2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    GreenLED2_Write(uint8 value);
void    GreenLED2_SetDriveMode(uint8 mode);
uint8   GreenLED2_ReadDataReg(void);
uint8   GreenLED2_Read(void);
void    GreenLED2_SetInterruptMode(uint16 position, uint16 mode);
uint8   GreenLED2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the GreenLED2_SetDriveMode() function.
     *  @{
     */
        #define GreenLED2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define GreenLED2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define GreenLED2_DM_RES_UP          PIN_DM_RES_UP
        #define GreenLED2_DM_RES_DWN         PIN_DM_RES_DWN
        #define GreenLED2_DM_OD_LO           PIN_DM_OD_LO
        #define GreenLED2_DM_OD_HI           PIN_DM_OD_HI
        #define GreenLED2_DM_STRONG          PIN_DM_STRONG
        #define GreenLED2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define GreenLED2_MASK               GreenLED2__MASK
#define GreenLED2_SHIFT              GreenLED2__SHIFT
#define GreenLED2_WIDTH              1u

/* Interrupt constants */
#if defined(GreenLED2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in GreenLED2_SetInterruptMode() function.
     *  @{
     */
        #define GreenLED2_INTR_NONE      (uint16)(0x0000u)
        #define GreenLED2_INTR_RISING    (uint16)(0x0001u)
        #define GreenLED2_INTR_FALLING   (uint16)(0x0002u)
        #define GreenLED2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define GreenLED2_INTR_MASK      (0x01u) 
#endif /* (GreenLED2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define GreenLED2_PS                     (* (reg8 *) GreenLED2__PS)
/* Data Register */
#define GreenLED2_DR                     (* (reg8 *) GreenLED2__DR)
/* Port Number */
#define GreenLED2_PRT_NUM                (* (reg8 *) GreenLED2__PRT) 
/* Connect to Analog Globals */                                                  
#define GreenLED2_AG                     (* (reg8 *) GreenLED2__AG)                       
/* Analog MUX bux enable */
#define GreenLED2_AMUX                   (* (reg8 *) GreenLED2__AMUX) 
/* Bidirectional Enable */                                                        
#define GreenLED2_BIE                    (* (reg8 *) GreenLED2__BIE)
/* Bit-mask for Aliased Register Access */
#define GreenLED2_BIT_MASK               (* (reg8 *) GreenLED2__BIT_MASK)
/* Bypass Enable */
#define GreenLED2_BYP                    (* (reg8 *) GreenLED2__BYP)
/* Port wide control signals */                                                   
#define GreenLED2_CTL                    (* (reg8 *) GreenLED2__CTL)
/* Drive Modes */
#define GreenLED2_DM0                    (* (reg8 *) GreenLED2__DM0) 
#define GreenLED2_DM1                    (* (reg8 *) GreenLED2__DM1)
#define GreenLED2_DM2                    (* (reg8 *) GreenLED2__DM2) 
/* Input Buffer Disable Override */
#define GreenLED2_INP_DIS                (* (reg8 *) GreenLED2__INP_DIS)
/* LCD Common or Segment Drive */
#define GreenLED2_LCD_COM_SEG            (* (reg8 *) GreenLED2__LCD_COM_SEG)
/* Enable Segment LCD */
#define GreenLED2_LCD_EN                 (* (reg8 *) GreenLED2__LCD_EN)
/* Slew Rate Control */
#define GreenLED2_SLW                    (* (reg8 *) GreenLED2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define GreenLED2_PRTDSI__CAPS_SEL       (* (reg8 *) GreenLED2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define GreenLED2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) GreenLED2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define GreenLED2_PRTDSI__OE_SEL0        (* (reg8 *) GreenLED2__PRTDSI__OE_SEL0) 
#define GreenLED2_PRTDSI__OE_SEL1        (* (reg8 *) GreenLED2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define GreenLED2_PRTDSI__OUT_SEL0       (* (reg8 *) GreenLED2__PRTDSI__OUT_SEL0) 
#define GreenLED2_PRTDSI__OUT_SEL1       (* (reg8 *) GreenLED2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define GreenLED2_PRTDSI__SYNC_OUT       (* (reg8 *) GreenLED2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(GreenLED2__SIO_CFG)
    #define GreenLED2_SIO_HYST_EN        (* (reg8 *) GreenLED2__SIO_HYST_EN)
    #define GreenLED2_SIO_REG_HIFREQ     (* (reg8 *) GreenLED2__SIO_REG_HIFREQ)
    #define GreenLED2_SIO_CFG            (* (reg8 *) GreenLED2__SIO_CFG)
    #define GreenLED2_SIO_DIFF           (* (reg8 *) GreenLED2__SIO_DIFF)
#endif /* (GreenLED2__SIO_CFG) */

/* Interrupt Registers */
#if defined(GreenLED2__INTSTAT)
    #define GreenLED2_INTSTAT            (* (reg8 *) GreenLED2__INTSTAT)
    #define GreenLED2_SNAP               (* (reg8 *) GreenLED2__SNAP)
    
	#define GreenLED2_0_INTTYPE_REG 		(* (reg8 *) GreenLED2__0__INTTYPE)
#endif /* (GreenLED2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_GreenLED2_H */


/* [] END OF FILE */
