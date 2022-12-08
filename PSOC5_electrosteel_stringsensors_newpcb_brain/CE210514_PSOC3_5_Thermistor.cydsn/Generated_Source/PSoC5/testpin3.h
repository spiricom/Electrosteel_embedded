/*******************************************************************************
* File Name: testpin3.h  
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

#if !defined(CY_PINS_testpin3_H) /* Pins testpin3_H */
#define CY_PINS_testpin3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "testpin3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 testpin3__PORT == 15 && ((testpin3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    testpin3_Write(uint8 value);
void    testpin3_SetDriveMode(uint8 mode);
uint8   testpin3_ReadDataReg(void);
uint8   testpin3_Read(void);
void    testpin3_SetInterruptMode(uint16 position, uint16 mode);
uint8   testpin3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the testpin3_SetDriveMode() function.
     *  @{
     */
        #define testpin3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define testpin3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define testpin3_DM_RES_UP          PIN_DM_RES_UP
        #define testpin3_DM_RES_DWN         PIN_DM_RES_DWN
        #define testpin3_DM_OD_LO           PIN_DM_OD_LO
        #define testpin3_DM_OD_HI           PIN_DM_OD_HI
        #define testpin3_DM_STRONG          PIN_DM_STRONG
        #define testpin3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define testpin3_MASK               testpin3__MASK
#define testpin3_SHIFT              testpin3__SHIFT
#define testpin3_WIDTH              1u

/* Interrupt constants */
#if defined(testpin3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in testpin3_SetInterruptMode() function.
     *  @{
     */
        #define testpin3_INTR_NONE      (uint16)(0x0000u)
        #define testpin3_INTR_RISING    (uint16)(0x0001u)
        #define testpin3_INTR_FALLING   (uint16)(0x0002u)
        #define testpin3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define testpin3_INTR_MASK      (0x01u) 
#endif /* (testpin3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define testpin3_PS                     (* (reg8 *) testpin3__PS)
/* Data Register */
#define testpin3_DR                     (* (reg8 *) testpin3__DR)
/* Port Number */
#define testpin3_PRT_NUM                (* (reg8 *) testpin3__PRT) 
/* Connect to Analog Globals */                                                  
#define testpin3_AG                     (* (reg8 *) testpin3__AG)                       
/* Analog MUX bux enable */
#define testpin3_AMUX                   (* (reg8 *) testpin3__AMUX) 
/* Bidirectional Enable */                                                        
#define testpin3_BIE                    (* (reg8 *) testpin3__BIE)
/* Bit-mask for Aliased Register Access */
#define testpin3_BIT_MASK               (* (reg8 *) testpin3__BIT_MASK)
/* Bypass Enable */
#define testpin3_BYP                    (* (reg8 *) testpin3__BYP)
/* Port wide control signals */                                                   
#define testpin3_CTL                    (* (reg8 *) testpin3__CTL)
/* Drive Modes */
#define testpin3_DM0                    (* (reg8 *) testpin3__DM0) 
#define testpin3_DM1                    (* (reg8 *) testpin3__DM1)
#define testpin3_DM2                    (* (reg8 *) testpin3__DM2) 
/* Input Buffer Disable Override */
#define testpin3_INP_DIS                (* (reg8 *) testpin3__INP_DIS)
/* LCD Common or Segment Drive */
#define testpin3_LCD_COM_SEG            (* (reg8 *) testpin3__LCD_COM_SEG)
/* Enable Segment LCD */
#define testpin3_LCD_EN                 (* (reg8 *) testpin3__LCD_EN)
/* Slew Rate Control */
#define testpin3_SLW                    (* (reg8 *) testpin3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define testpin3_PRTDSI__CAPS_SEL       (* (reg8 *) testpin3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define testpin3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) testpin3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define testpin3_PRTDSI__OE_SEL0        (* (reg8 *) testpin3__PRTDSI__OE_SEL0) 
#define testpin3_PRTDSI__OE_SEL1        (* (reg8 *) testpin3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define testpin3_PRTDSI__OUT_SEL0       (* (reg8 *) testpin3__PRTDSI__OUT_SEL0) 
#define testpin3_PRTDSI__OUT_SEL1       (* (reg8 *) testpin3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define testpin3_PRTDSI__SYNC_OUT       (* (reg8 *) testpin3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(testpin3__SIO_CFG)
    #define testpin3_SIO_HYST_EN        (* (reg8 *) testpin3__SIO_HYST_EN)
    #define testpin3_SIO_REG_HIFREQ     (* (reg8 *) testpin3__SIO_REG_HIFREQ)
    #define testpin3_SIO_CFG            (* (reg8 *) testpin3__SIO_CFG)
    #define testpin3_SIO_DIFF           (* (reg8 *) testpin3__SIO_DIFF)
#endif /* (testpin3__SIO_CFG) */

/* Interrupt Registers */
#if defined(testpin3__INTSTAT)
    #define testpin3_INTSTAT            (* (reg8 *) testpin3__INTSTAT)
    #define testpin3_SNAP               (* (reg8 *) testpin3__SNAP)
    
	#define testpin3_0_INTTYPE_REG 		(* (reg8 *) testpin3__0__INTTYPE)
#endif /* (testpin3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_testpin3_H */


/* [] END OF FILE */
