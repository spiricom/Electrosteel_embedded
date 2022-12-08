/*******************************************************************************
* File Name: middle_wiper2.h  
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

#if !defined(CY_PINS_middle_wiper2_H) /* Pins middle_wiper2_H */
#define CY_PINS_middle_wiper2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "middle_wiper2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 middle_wiper2__PORT == 15 && ((middle_wiper2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    middle_wiper2_Write(uint8 value);
void    middle_wiper2_SetDriveMode(uint8 mode);
uint8   middle_wiper2_ReadDataReg(void);
uint8   middle_wiper2_Read(void);
void    middle_wiper2_SetInterruptMode(uint16 position, uint16 mode);
uint8   middle_wiper2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the middle_wiper2_SetDriveMode() function.
     *  @{
     */
        #define middle_wiper2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define middle_wiper2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define middle_wiper2_DM_RES_UP          PIN_DM_RES_UP
        #define middle_wiper2_DM_RES_DWN         PIN_DM_RES_DWN
        #define middle_wiper2_DM_OD_LO           PIN_DM_OD_LO
        #define middle_wiper2_DM_OD_HI           PIN_DM_OD_HI
        #define middle_wiper2_DM_STRONG          PIN_DM_STRONG
        #define middle_wiper2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define middle_wiper2_MASK               middle_wiper2__MASK
#define middle_wiper2_SHIFT              middle_wiper2__SHIFT
#define middle_wiper2_WIDTH              1u

/* Interrupt constants */
#if defined(middle_wiper2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in middle_wiper2_SetInterruptMode() function.
     *  @{
     */
        #define middle_wiper2_INTR_NONE      (uint16)(0x0000u)
        #define middle_wiper2_INTR_RISING    (uint16)(0x0001u)
        #define middle_wiper2_INTR_FALLING   (uint16)(0x0002u)
        #define middle_wiper2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define middle_wiper2_INTR_MASK      (0x01u) 
#endif /* (middle_wiper2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define middle_wiper2_PS                     (* (reg8 *) middle_wiper2__PS)
/* Data Register */
#define middle_wiper2_DR                     (* (reg8 *) middle_wiper2__DR)
/* Port Number */
#define middle_wiper2_PRT_NUM                (* (reg8 *) middle_wiper2__PRT) 
/* Connect to Analog Globals */                                                  
#define middle_wiper2_AG                     (* (reg8 *) middle_wiper2__AG)                       
/* Analog MUX bux enable */
#define middle_wiper2_AMUX                   (* (reg8 *) middle_wiper2__AMUX) 
/* Bidirectional Enable */                                                        
#define middle_wiper2_BIE                    (* (reg8 *) middle_wiper2__BIE)
/* Bit-mask for Aliased Register Access */
#define middle_wiper2_BIT_MASK               (* (reg8 *) middle_wiper2__BIT_MASK)
/* Bypass Enable */
#define middle_wiper2_BYP                    (* (reg8 *) middle_wiper2__BYP)
/* Port wide control signals */                                                   
#define middle_wiper2_CTL                    (* (reg8 *) middle_wiper2__CTL)
/* Drive Modes */
#define middle_wiper2_DM0                    (* (reg8 *) middle_wiper2__DM0) 
#define middle_wiper2_DM1                    (* (reg8 *) middle_wiper2__DM1)
#define middle_wiper2_DM2                    (* (reg8 *) middle_wiper2__DM2) 
/* Input Buffer Disable Override */
#define middle_wiper2_INP_DIS                (* (reg8 *) middle_wiper2__INP_DIS)
/* LCD Common or Segment Drive */
#define middle_wiper2_LCD_COM_SEG            (* (reg8 *) middle_wiper2__LCD_COM_SEG)
/* Enable Segment LCD */
#define middle_wiper2_LCD_EN                 (* (reg8 *) middle_wiper2__LCD_EN)
/* Slew Rate Control */
#define middle_wiper2_SLW                    (* (reg8 *) middle_wiper2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define middle_wiper2_PRTDSI__CAPS_SEL       (* (reg8 *) middle_wiper2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define middle_wiper2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) middle_wiper2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define middle_wiper2_PRTDSI__OE_SEL0        (* (reg8 *) middle_wiper2__PRTDSI__OE_SEL0) 
#define middle_wiper2_PRTDSI__OE_SEL1        (* (reg8 *) middle_wiper2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define middle_wiper2_PRTDSI__OUT_SEL0       (* (reg8 *) middle_wiper2__PRTDSI__OUT_SEL0) 
#define middle_wiper2_PRTDSI__OUT_SEL1       (* (reg8 *) middle_wiper2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define middle_wiper2_PRTDSI__SYNC_OUT       (* (reg8 *) middle_wiper2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(middle_wiper2__SIO_CFG)
    #define middle_wiper2_SIO_HYST_EN        (* (reg8 *) middle_wiper2__SIO_HYST_EN)
    #define middle_wiper2_SIO_REG_HIFREQ     (* (reg8 *) middle_wiper2__SIO_REG_HIFREQ)
    #define middle_wiper2_SIO_CFG            (* (reg8 *) middle_wiper2__SIO_CFG)
    #define middle_wiper2_SIO_DIFF           (* (reg8 *) middle_wiper2__SIO_DIFF)
#endif /* (middle_wiper2__SIO_CFG) */

/* Interrupt Registers */
#if defined(middle_wiper2__INTSTAT)
    #define middle_wiper2_INTSTAT            (* (reg8 *) middle_wiper2__INTSTAT)
    #define middle_wiper2_SNAP               (* (reg8 *) middle_wiper2__SNAP)
    
	#define middle_wiper2_0_INTTYPE_REG 		(* (reg8 *) middle_wiper2__0__INTTYPE)
#endif /* (middle_wiper2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_middle_wiper2_H */


/* [] END OF FILE */
