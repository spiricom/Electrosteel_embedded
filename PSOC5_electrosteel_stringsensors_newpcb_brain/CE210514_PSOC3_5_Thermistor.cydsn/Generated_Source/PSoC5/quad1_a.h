/*******************************************************************************
* File Name: quad1_a.h  
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

#if !defined(CY_PINS_quad1_a_H) /* Pins quad1_a_H */
#define CY_PINS_quad1_a_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "quad1_a_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 quad1_a__PORT == 15 && ((quad1_a__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    quad1_a_Write(uint8 value);
void    quad1_a_SetDriveMode(uint8 mode);
uint8   quad1_a_ReadDataReg(void);
uint8   quad1_a_Read(void);
void    quad1_a_SetInterruptMode(uint16 position, uint16 mode);
uint8   quad1_a_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the quad1_a_SetDriveMode() function.
     *  @{
     */
        #define quad1_a_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define quad1_a_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define quad1_a_DM_RES_UP          PIN_DM_RES_UP
        #define quad1_a_DM_RES_DWN         PIN_DM_RES_DWN
        #define quad1_a_DM_OD_LO           PIN_DM_OD_LO
        #define quad1_a_DM_OD_HI           PIN_DM_OD_HI
        #define quad1_a_DM_STRONG          PIN_DM_STRONG
        #define quad1_a_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define quad1_a_MASK               quad1_a__MASK
#define quad1_a_SHIFT              quad1_a__SHIFT
#define quad1_a_WIDTH              1u

/* Interrupt constants */
#if defined(quad1_a__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in quad1_a_SetInterruptMode() function.
     *  @{
     */
        #define quad1_a_INTR_NONE      (uint16)(0x0000u)
        #define quad1_a_INTR_RISING    (uint16)(0x0001u)
        #define quad1_a_INTR_FALLING   (uint16)(0x0002u)
        #define quad1_a_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define quad1_a_INTR_MASK      (0x01u) 
#endif /* (quad1_a__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define quad1_a_PS                     (* (reg8 *) quad1_a__PS)
/* Data Register */
#define quad1_a_DR                     (* (reg8 *) quad1_a__DR)
/* Port Number */
#define quad1_a_PRT_NUM                (* (reg8 *) quad1_a__PRT) 
/* Connect to Analog Globals */                                                  
#define quad1_a_AG                     (* (reg8 *) quad1_a__AG)                       
/* Analog MUX bux enable */
#define quad1_a_AMUX                   (* (reg8 *) quad1_a__AMUX) 
/* Bidirectional Enable */                                                        
#define quad1_a_BIE                    (* (reg8 *) quad1_a__BIE)
/* Bit-mask for Aliased Register Access */
#define quad1_a_BIT_MASK               (* (reg8 *) quad1_a__BIT_MASK)
/* Bypass Enable */
#define quad1_a_BYP                    (* (reg8 *) quad1_a__BYP)
/* Port wide control signals */                                                   
#define quad1_a_CTL                    (* (reg8 *) quad1_a__CTL)
/* Drive Modes */
#define quad1_a_DM0                    (* (reg8 *) quad1_a__DM0) 
#define quad1_a_DM1                    (* (reg8 *) quad1_a__DM1)
#define quad1_a_DM2                    (* (reg8 *) quad1_a__DM2) 
/* Input Buffer Disable Override */
#define quad1_a_INP_DIS                (* (reg8 *) quad1_a__INP_DIS)
/* LCD Common or Segment Drive */
#define quad1_a_LCD_COM_SEG            (* (reg8 *) quad1_a__LCD_COM_SEG)
/* Enable Segment LCD */
#define quad1_a_LCD_EN                 (* (reg8 *) quad1_a__LCD_EN)
/* Slew Rate Control */
#define quad1_a_SLW                    (* (reg8 *) quad1_a__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define quad1_a_PRTDSI__CAPS_SEL       (* (reg8 *) quad1_a__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define quad1_a_PRTDSI__DBL_SYNC_IN    (* (reg8 *) quad1_a__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define quad1_a_PRTDSI__OE_SEL0        (* (reg8 *) quad1_a__PRTDSI__OE_SEL0) 
#define quad1_a_PRTDSI__OE_SEL1        (* (reg8 *) quad1_a__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define quad1_a_PRTDSI__OUT_SEL0       (* (reg8 *) quad1_a__PRTDSI__OUT_SEL0) 
#define quad1_a_PRTDSI__OUT_SEL1       (* (reg8 *) quad1_a__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define quad1_a_PRTDSI__SYNC_OUT       (* (reg8 *) quad1_a__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(quad1_a__SIO_CFG)
    #define quad1_a_SIO_HYST_EN        (* (reg8 *) quad1_a__SIO_HYST_EN)
    #define quad1_a_SIO_REG_HIFREQ     (* (reg8 *) quad1_a__SIO_REG_HIFREQ)
    #define quad1_a_SIO_CFG            (* (reg8 *) quad1_a__SIO_CFG)
    #define quad1_a_SIO_DIFF           (* (reg8 *) quad1_a__SIO_DIFF)
#endif /* (quad1_a__SIO_CFG) */

/* Interrupt Registers */
#if defined(quad1_a__INTSTAT)
    #define quad1_a_INTSTAT            (* (reg8 *) quad1_a__INTSTAT)
    #define quad1_a_SNAP               (* (reg8 *) quad1_a__SNAP)
    
	#define quad1_a_0_INTTYPE_REG 		(* (reg8 *) quad1_a__0__INTTYPE)
#endif /* (quad1_a__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_quad1_a_H */


/* [] END OF FILE */
