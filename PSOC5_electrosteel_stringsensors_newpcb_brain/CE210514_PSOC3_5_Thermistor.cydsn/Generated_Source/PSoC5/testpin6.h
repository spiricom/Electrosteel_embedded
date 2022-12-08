/*******************************************************************************
* File Name: testpin6.h  
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

#if !defined(CY_PINS_testpin6_H) /* Pins testpin6_H */
#define CY_PINS_testpin6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "testpin6_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 testpin6__PORT == 15 && ((testpin6__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    testpin6_Write(uint8 value);
void    testpin6_SetDriveMode(uint8 mode);
uint8   testpin6_ReadDataReg(void);
uint8   testpin6_Read(void);
void    testpin6_SetInterruptMode(uint16 position, uint16 mode);
uint8   testpin6_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the testpin6_SetDriveMode() function.
     *  @{
     */
        #define testpin6_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define testpin6_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define testpin6_DM_RES_UP          PIN_DM_RES_UP
        #define testpin6_DM_RES_DWN         PIN_DM_RES_DWN
        #define testpin6_DM_OD_LO           PIN_DM_OD_LO
        #define testpin6_DM_OD_HI           PIN_DM_OD_HI
        #define testpin6_DM_STRONG          PIN_DM_STRONG
        #define testpin6_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define testpin6_MASK               testpin6__MASK
#define testpin6_SHIFT              testpin6__SHIFT
#define testpin6_WIDTH              1u

/* Interrupt constants */
#if defined(testpin6__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in testpin6_SetInterruptMode() function.
     *  @{
     */
        #define testpin6_INTR_NONE      (uint16)(0x0000u)
        #define testpin6_INTR_RISING    (uint16)(0x0001u)
        #define testpin6_INTR_FALLING   (uint16)(0x0002u)
        #define testpin6_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define testpin6_INTR_MASK      (0x01u) 
#endif /* (testpin6__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define testpin6_PS                     (* (reg8 *) testpin6__PS)
/* Data Register */
#define testpin6_DR                     (* (reg8 *) testpin6__DR)
/* Port Number */
#define testpin6_PRT_NUM                (* (reg8 *) testpin6__PRT) 
/* Connect to Analog Globals */                                                  
#define testpin6_AG                     (* (reg8 *) testpin6__AG)                       
/* Analog MUX bux enable */
#define testpin6_AMUX                   (* (reg8 *) testpin6__AMUX) 
/* Bidirectional Enable */                                                        
#define testpin6_BIE                    (* (reg8 *) testpin6__BIE)
/* Bit-mask for Aliased Register Access */
#define testpin6_BIT_MASK               (* (reg8 *) testpin6__BIT_MASK)
/* Bypass Enable */
#define testpin6_BYP                    (* (reg8 *) testpin6__BYP)
/* Port wide control signals */                                                   
#define testpin6_CTL                    (* (reg8 *) testpin6__CTL)
/* Drive Modes */
#define testpin6_DM0                    (* (reg8 *) testpin6__DM0) 
#define testpin6_DM1                    (* (reg8 *) testpin6__DM1)
#define testpin6_DM2                    (* (reg8 *) testpin6__DM2) 
/* Input Buffer Disable Override */
#define testpin6_INP_DIS                (* (reg8 *) testpin6__INP_DIS)
/* LCD Common or Segment Drive */
#define testpin6_LCD_COM_SEG            (* (reg8 *) testpin6__LCD_COM_SEG)
/* Enable Segment LCD */
#define testpin6_LCD_EN                 (* (reg8 *) testpin6__LCD_EN)
/* Slew Rate Control */
#define testpin6_SLW                    (* (reg8 *) testpin6__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define testpin6_PRTDSI__CAPS_SEL       (* (reg8 *) testpin6__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define testpin6_PRTDSI__DBL_SYNC_IN    (* (reg8 *) testpin6__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define testpin6_PRTDSI__OE_SEL0        (* (reg8 *) testpin6__PRTDSI__OE_SEL0) 
#define testpin6_PRTDSI__OE_SEL1        (* (reg8 *) testpin6__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define testpin6_PRTDSI__OUT_SEL0       (* (reg8 *) testpin6__PRTDSI__OUT_SEL0) 
#define testpin6_PRTDSI__OUT_SEL1       (* (reg8 *) testpin6__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define testpin6_PRTDSI__SYNC_OUT       (* (reg8 *) testpin6__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(testpin6__SIO_CFG)
    #define testpin6_SIO_HYST_EN        (* (reg8 *) testpin6__SIO_HYST_EN)
    #define testpin6_SIO_REG_HIFREQ     (* (reg8 *) testpin6__SIO_REG_HIFREQ)
    #define testpin6_SIO_CFG            (* (reg8 *) testpin6__SIO_CFG)
    #define testpin6_SIO_DIFF           (* (reg8 *) testpin6__SIO_DIFF)
#endif /* (testpin6__SIO_CFG) */

/* Interrupt Registers */
#if defined(testpin6__INTSTAT)
    #define testpin6_INTSTAT            (* (reg8 *) testpin6__INTSTAT)
    #define testpin6_SNAP               (* (reg8 *) testpin6__SNAP)
    
	#define testpin6_0_INTTYPE_REG 		(* (reg8 *) testpin6__0__INTTYPE)
#endif /* (testpin6__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_testpin6_H */


/* [] END OF FILE */
