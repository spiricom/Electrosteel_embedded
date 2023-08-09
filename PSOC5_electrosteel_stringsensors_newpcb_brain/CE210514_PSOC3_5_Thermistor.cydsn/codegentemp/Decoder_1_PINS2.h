/*******************************************************************************
* File Name: Decoder_1_PINS2.h  
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

#if !defined(CY_PINS_Decoder_1_PINS2_H) /* Pins Decoder_1_PINS2_H */
#define CY_PINS_Decoder_1_PINS2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Decoder_1_PINS2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Decoder_1_PINS2__PORT == 15 && ((Decoder_1_PINS2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Decoder_1_PINS2_Write(uint8 value);
void    Decoder_1_PINS2_SetDriveMode(uint8 mode);
uint8   Decoder_1_PINS2_ReadDataReg(void);
uint8   Decoder_1_PINS2_Read(void);
void    Decoder_1_PINS2_SetInterruptMode(uint16 position, uint16 mode);
uint8   Decoder_1_PINS2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Decoder_1_PINS2_SetDriveMode() function.
     *  @{
     */
        #define Decoder_1_PINS2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Decoder_1_PINS2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Decoder_1_PINS2_DM_RES_UP          PIN_DM_RES_UP
        #define Decoder_1_PINS2_DM_RES_DWN         PIN_DM_RES_DWN
        #define Decoder_1_PINS2_DM_OD_LO           PIN_DM_OD_LO
        #define Decoder_1_PINS2_DM_OD_HI           PIN_DM_OD_HI
        #define Decoder_1_PINS2_DM_STRONG          PIN_DM_STRONG
        #define Decoder_1_PINS2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Decoder_1_PINS2_MASK               Decoder_1_PINS2__MASK
#define Decoder_1_PINS2_SHIFT              Decoder_1_PINS2__SHIFT
#define Decoder_1_PINS2_WIDTH              2u

/* Interrupt constants */
#if defined(Decoder_1_PINS2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Decoder_1_PINS2_SetInterruptMode() function.
     *  @{
     */
        #define Decoder_1_PINS2_INTR_NONE      (uint16)(0x0000u)
        #define Decoder_1_PINS2_INTR_RISING    (uint16)(0x0001u)
        #define Decoder_1_PINS2_INTR_FALLING   (uint16)(0x0002u)
        #define Decoder_1_PINS2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Decoder_1_PINS2_INTR_MASK      (0x01u) 
#endif /* (Decoder_1_PINS2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Decoder_1_PINS2_PS                     (* (reg8 *) Decoder_1_PINS2__PS)
/* Data Register */
#define Decoder_1_PINS2_DR                     (* (reg8 *) Decoder_1_PINS2__DR)
/* Port Number */
#define Decoder_1_PINS2_PRT_NUM                (* (reg8 *) Decoder_1_PINS2__PRT) 
/* Connect to Analog Globals */                                                  
#define Decoder_1_PINS2_AG                     (* (reg8 *) Decoder_1_PINS2__AG)                       
/* Analog MUX bux enable */
#define Decoder_1_PINS2_AMUX                   (* (reg8 *) Decoder_1_PINS2__AMUX) 
/* Bidirectional Enable */                                                        
#define Decoder_1_PINS2_BIE                    (* (reg8 *) Decoder_1_PINS2__BIE)
/* Bit-mask for Aliased Register Access */
#define Decoder_1_PINS2_BIT_MASK               (* (reg8 *) Decoder_1_PINS2__BIT_MASK)
/* Bypass Enable */
#define Decoder_1_PINS2_BYP                    (* (reg8 *) Decoder_1_PINS2__BYP)
/* Port wide control signals */                                                   
#define Decoder_1_PINS2_CTL                    (* (reg8 *) Decoder_1_PINS2__CTL)
/* Drive Modes */
#define Decoder_1_PINS2_DM0                    (* (reg8 *) Decoder_1_PINS2__DM0) 
#define Decoder_1_PINS2_DM1                    (* (reg8 *) Decoder_1_PINS2__DM1)
#define Decoder_1_PINS2_DM2                    (* (reg8 *) Decoder_1_PINS2__DM2) 
/* Input Buffer Disable Override */
#define Decoder_1_PINS2_INP_DIS                (* (reg8 *) Decoder_1_PINS2__INP_DIS)
/* LCD Common or Segment Drive */
#define Decoder_1_PINS2_LCD_COM_SEG            (* (reg8 *) Decoder_1_PINS2__LCD_COM_SEG)
/* Enable Segment LCD */
#define Decoder_1_PINS2_LCD_EN                 (* (reg8 *) Decoder_1_PINS2__LCD_EN)
/* Slew Rate Control */
#define Decoder_1_PINS2_SLW                    (* (reg8 *) Decoder_1_PINS2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Decoder_1_PINS2_PRTDSI__CAPS_SEL       (* (reg8 *) Decoder_1_PINS2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Decoder_1_PINS2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Decoder_1_PINS2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Decoder_1_PINS2_PRTDSI__OE_SEL0        (* (reg8 *) Decoder_1_PINS2__PRTDSI__OE_SEL0) 
#define Decoder_1_PINS2_PRTDSI__OE_SEL1        (* (reg8 *) Decoder_1_PINS2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Decoder_1_PINS2_PRTDSI__OUT_SEL0       (* (reg8 *) Decoder_1_PINS2__PRTDSI__OUT_SEL0) 
#define Decoder_1_PINS2_PRTDSI__OUT_SEL1       (* (reg8 *) Decoder_1_PINS2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Decoder_1_PINS2_PRTDSI__SYNC_OUT       (* (reg8 *) Decoder_1_PINS2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Decoder_1_PINS2__SIO_CFG)
    #define Decoder_1_PINS2_SIO_HYST_EN        (* (reg8 *) Decoder_1_PINS2__SIO_HYST_EN)
    #define Decoder_1_PINS2_SIO_REG_HIFREQ     (* (reg8 *) Decoder_1_PINS2__SIO_REG_HIFREQ)
    #define Decoder_1_PINS2_SIO_CFG            (* (reg8 *) Decoder_1_PINS2__SIO_CFG)
    #define Decoder_1_PINS2_SIO_DIFF           (* (reg8 *) Decoder_1_PINS2__SIO_DIFF)
#endif /* (Decoder_1_PINS2__SIO_CFG) */

/* Interrupt Registers */
#if defined(Decoder_1_PINS2__INTSTAT)
    #define Decoder_1_PINS2_INTSTAT            (* (reg8 *) Decoder_1_PINS2__INTSTAT)
    #define Decoder_1_PINS2_SNAP               (* (reg8 *) Decoder_1_PINS2__SNAP)
    
	#define Decoder_1_PINS2_0_INTTYPE_REG 		(* (reg8 *) Decoder_1_PINS2__0__INTTYPE)
	#define Decoder_1_PINS2_1_INTTYPE_REG 		(* (reg8 *) Decoder_1_PINS2__1__INTTYPE)
#endif /* (Decoder_1_PINS2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Decoder_1_PINS2_H */


/* [] END OF FILE */
