/*******************************************************************************
* File Name: testpin4.h  
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

#if !defined(CY_PINS_testpin4_H) /* Pins testpin4_H */
#define CY_PINS_testpin4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "testpin4_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 testpin4__PORT == 15 && ((testpin4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    testpin4_Write(uint8 value);
void    testpin4_SetDriveMode(uint8 mode);
uint8   testpin4_ReadDataReg(void);
uint8   testpin4_Read(void);
void    testpin4_SetInterruptMode(uint16 position, uint16 mode);
uint8   testpin4_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the testpin4_SetDriveMode() function.
     *  @{
     */
        #define testpin4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define testpin4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define testpin4_DM_RES_UP          PIN_DM_RES_UP
        #define testpin4_DM_RES_DWN         PIN_DM_RES_DWN
        #define testpin4_DM_OD_LO           PIN_DM_OD_LO
        #define testpin4_DM_OD_HI           PIN_DM_OD_HI
        #define testpin4_DM_STRONG          PIN_DM_STRONG
        #define testpin4_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define testpin4_MASK               testpin4__MASK
#define testpin4_SHIFT              testpin4__SHIFT
#define testpin4_WIDTH              1u

/* Interrupt constants */
#if defined(testpin4__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in testpin4_SetInterruptMode() function.
     *  @{
     */
        #define testpin4_INTR_NONE      (uint16)(0x0000u)
        #define testpin4_INTR_RISING    (uint16)(0x0001u)
        #define testpin4_INTR_FALLING   (uint16)(0x0002u)
        #define testpin4_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define testpin4_INTR_MASK      (0x01u) 
#endif /* (testpin4__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define testpin4_PS                     (* (reg8 *) testpin4__PS)
/* Data Register */
#define testpin4_DR                     (* (reg8 *) testpin4__DR)
/* Port Number */
#define testpin4_PRT_NUM                (* (reg8 *) testpin4__PRT) 
/* Connect to Analog Globals */                                                  
#define testpin4_AG                     (* (reg8 *) testpin4__AG)                       
/* Analog MUX bux enable */
#define testpin4_AMUX                   (* (reg8 *) testpin4__AMUX) 
/* Bidirectional Enable */                                                        
#define testpin4_BIE                    (* (reg8 *) testpin4__BIE)
/* Bit-mask for Aliased Register Access */
#define testpin4_BIT_MASK               (* (reg8 *) testpin4__BIT_MASK)
/* Bypass Enable */
#define testpin4_BYP                    (* (reg8 *) testpin4__BYP)
/* Port wide control signals */                                                   
#define testpin4_CTL                    (* (reg8 *) testpin4__CTL)
/* Drive Modes */
#define testpin4_DM0                    (* (reg8 *) testpin4__DM0) 
#define testpin4_DM1                    (* (reg8 *) testpin4__DM1)
#define testpin4_DM2                    (* (reg8 *) testpin4__DM2) 
/* Input Buffer Disable Override */
#define testpin4_INP_DIS                (* (reg8 *) testpin4__INP_DIS)
/* LCD Common or Segment Drive */
#define testpin4_LCD_COM_SEG            (* (reg8 *) testpin4__LCD_COM_SEG)
/* Enable Segment LCD */
#define testpin4_LCD_EN                 (* (reg8 *) testpin4__LCD_EN)
/* Slew Rate Control */
#define testpin4_SLW                    (* (reg8 *) testpin4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define testpin4_PRTDSI__CAPS_SEL       (* (reg8 *) testpin4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define testpin4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) testpin4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define testpin4_PRTDSI__OE_SEL0        (* (reg8 *) testpin4__PRTDSI__OE_SEL0) 
#define testpin4_PRTDSI__OE_SEL1        (* (reg8 *) testpin4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define testpin4_PRTDSI__OUT_SEL0       (* (reg8 *) testpin4__PRTDSI__OUT_SEL0) 
#define testpin4_PRTDSI__OUT_SEL1       (* (reg8 *) testpin4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define testpin4_PRTDSI__SYNC_OUT       (* (reg8 *) testpin4__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(testpin4__SIO_CFG)
    #define testpin4_SIO_HYST_EN        (* (reg8 *) testpin4__SIO_HYST_EN)
    #define testpin4_SIO_REG_HIFREQ     (* (reg8 *) testpin4__SIO_REG_HIFREQ)
    #define testpin4_SIO_CFG            (* (reg8 *) testpin4__SIO_CFG)
    #define testpin4_SIO_DIFF           (* (reg8 *) testpin4__SIO_DIFF)
#endif /* (testpin4__SIO_CFG) */

/* Interrupt Registers */
#if defined(testpin4__INTSTAT)
    #define testpin4_INTSTAT            (* (reg8 *) testpin4__INTSTAT)
    #define testpin4_SNAP               (* (reg8 *) testpin4__SNAP)
    
	#define testpin4_0_INTTYPE_REG 		(* (reg8 *) testpin4__0__INTTYPE)
#endif /* (testpin4__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_testpin4_H */


/* [] END OF FILE */
