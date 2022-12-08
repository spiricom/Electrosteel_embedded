/*******************************************************************************
* File Name: I2C_1_TMOUT.h
* Version 3.50
*
* Description:
*  This file provides constants and parameter values for the I2C component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_I2C_TMOUT_I2C_1_H)
#define CY_I2C_TMOUT_I2C_1_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"
#include "I2C_1.h"


/***************************************
*        Function Prototypes
***************************************/

void I2C_1_TimeoutInit(void)                 ;
void I2C_1_TimeoutEnable(void)               ;
void I2C_1_TimeoutStop(void)                 ;

void I2C_1_TimeoutReset(void)                ;

void I2C_1_TimeoutSaveConfig(void)           ;
void I2C_1_TimeoutRestoreConfig(void)        ;

void I2C_1_TimeoutSetPeriod(uint16 period)   ;
uint16 I2C_1_TimeoutGetPeriod(void)          ;

#if (I2C_1_TIMEOUT_PRESCALER_ENABLED)
    void  I2C_1_TimeoutSetPrescalerPeriod(uint8 period)
                                                        ;
    uint8 I2C_1_TimeoutGetPrescalerPeriod(void)
                                                        ;
#endif /* (I2C_1_TIMEOUT_PRESCALER_ENABLED) */

#if (I2C_1_TIMEOUT_FF_ENABLED)
    #define I2C_1_TimeoutEnableInt() \
            do{                                 \
                I2C_1_TMOUT_CSR_REG |= (uint8)  I2C_1_TMOUT_CSR_I2C_TMOUT_IE; \
            }while(0)

    #define I2C_1_TimeoutDisableInt() \
            do{                                  \
                I2C_1_TMOUT_CSR_REG &= (uint8) ~I2C_1_TMOUT_CSR_I2C_TMOUT_IE; \
            }while(0)

    #define I2C_1_TimeoutClearPendingInt()       CyIntClearPending(I2C_1_ISR_NUMBER)

    #define I2C_1_TimeoutSetIntrMode(intrSource) \
            do{                                             \
                I2C_1_TMOUT_CSR_REG |= ((intrSource) & I2C_1_TMOUT_CSR_INTR_MASK); \
            }while(0)

    #define I2C_1_TimeoutGetIntrMode()           (I2C_1_TMOUT_CSR_REG & \
                                                             I2C_1_TMOUT_CSR_INTR_MASK)

    #define I2C_1_TimeoutGetStatus()             (I2C_1_TMOUT_SR_REG)
    #define I2C_1_TimeoutClearStatus(intrStatus) {I2C_1_TMOUT_SR_REG = (intrStatus);}

#else
    CY_ISR_PROTO(I2C_1_TMOUT_ISR);    /* Timeout interrupt handler */

    #define I2C_1_TimeoutEnableInt()         CyIntEnable      (I2C_1_TMOUT_ISR_NUMBER)
    #define I2C_1_TimeoutDisableInt()        CyIntDisable     (I2C_1_TMOUT_ISR_NUMBER)
    #define I2C_1_TimeoutClearPendingInt()   CyIntClearPending(I2C_1_TMOUT_ISR_NUMBER)

    #define I2C_1_TimeoutSetIntrMode(intrSource) \
            do{                                             \
            I2C_1_TMOUT_INTR_MASK_REG = ((intrSource) & I2C_1_TMOUT_STS_INTR_MASK); \
            }while(0)

    #define I2C_1_TimeoutGetIntrMode() \
            (I2C_1_TMOUT_INTR_MASK_REG & I2C_1_TMOUT_STS_INTR_MASK)

    #define I2C_1_TimeoutGetStatus() \
            (I2C_1_TMOUT_STS_REG & I2C_1_TMOUT_STS_INTR_MASK)

    #define I2C_1_TimeoutClearStatus(intrStatus) /* There is no implementation for UDB version */

#endif /* (I2C_1_TIMEOUT_FF_ENABLED) */


/***************************************
*        API constants
***************************************/


/***************************************
*              Registers
***************************************/

#if (I2C_1_TIMEOUT_FF_ENABLED)
    /* I2C FF timeout hardware */
    #define I2C_1_TMOUT_CSR_REG  (*(reg8 *) I2C_1_I2C_FF__TMOUT_CSR)
    #define I2C_1_TMOUT_CSR_PTR  ( (reg8 *) I2C_1_I2C_FF__TMOUT_CSR)

    #define I2C_1_TMOUT_SR_REG   (*(reg8 *) I2C_1_I2C_FF__TMOUT_SR)
    #define I2C_1_TMOUT_SR_PTR   ( (reg8 *) I2C_1_I2C_FF__TMOUT_SR)

    #define I2C_1_TMOUT_CFG0_REG (*(reg8 *) I2C_1_I2C_FF__TMOUT_CFG0)
    #define I2C_1_TMOUT_CFG0_PTR ( (reg8 *) I2C_1_I2C_FF__TMOUT_CFG0)

    #define I2C_1_TMOUT_CFG1_REG (*(reg8 *) I2C_1_I2C_FF__TMOUT_CFG1)
    #define I2C_1_TMOUT_CFG1_PTR ( (reg8 *) I2C_1_I2C_FF__TMOUT_CFG1)

#else

    #define I2C_1_TMOUT_CTRL_REG \
                        (*(reg8 *) I2C_1_bTimeoutTimer_SyncCtl_CtrlReg__CONTROL_REG)
    #define I2C_1_TMOUT_CTRL_PTR \
                        ( (reg8 *) I2C_1_bTimeoutTimer_SyncCtl_CtrlReg__CONTROL_REG)

    #define I2C_1_TMOUT_STS_REG          (*(reg8 *) I2C_1_bTimeoutTimer_StsReg__STATUS_REG)
    #define I2C_1_TMOUT_STS_PTR          ( (reg8 *) I2C_1_bTimeoutTimer_StsReg__STATUS_REG)

    #define I2C_1_TMOUT_INTR_MASK_REG    (*(reg8 *) I2C_1_bTimeoutTimer_StsReg__MASK_REG)
    #define I2C_1_TMOUT_INTR_MASK_PTR    ( (reg8 *) I2C_1_bTimeoutTimer_StsReg__MASK_REG)

    #define I2C_1_TMOUT_INTR_ENABLE_REG  (*(reg8 *) I2C_1_bTimeoutTimer_StsReg__STATUS_AUX_CTL_REG)
    #define I2C_1_TMOUT_INTR_ENABLE_PTR  ( (reg8 *) I2C_1_bTimeoutTimer_StsReg__STATUS_AUX_CTL_REG)

    #if (I2C_1_TIMEOUT_SCL_TMOUT_ENABLED)
        #define I2C_1_TMOUT_SCL_PRD0_REG     (*(reg8 *) I2C_1_bTimeoutTimer_Scl_dpScl_u0__F0_REG)
        #define I2C_1_TMOUT_SCL_PRD0_PTR     ( (reg8 *) I2C_1_bTimeoutTimer_Scl_dpScl_u0__F0_REG)

        #define I2C_1_TMOUT_SCL_PRD1_REG     (*(reg8 *) I2C_1_bTimeoutTimer_Scl_dpScl_u0__F1_REG)
        #define I2C_1_TMOUT_SCL_PRD1_PTR     ( (reg8 *) I2C_1_bTimeoutTimer_Scl_dpScl_u0__F1_REG)

        #define I2C_1_TMOUT_SCL_ADDER_REG    (*(reg8 *) I2C_1_bTimeoutTimer_Scl_dpScl_u0__D0_REG)
        #define I2C_1_TMOUT_SCL_ADDER_PTR    ( (reg8 *) I2C_1_bTimeoutTimer_Scl_dpScl_u0__D0_REG)

        #define I2C_1_TMOUT_SCL_AUX_CTRL_REG \
                                                (*(reg8 *) I2C_1_bTimeoutTimer_Scl_dpScl_u0__DP_AUX_CTL_REG)
        #define I2C_1_TMOUT_SCL_AUX_CTRL_PTR \
                                                ( (reg8 *) I2C_1_bTimeoutTimer_Scl_dpScl_u0__DP_AUX_CTL_REG)

        #if (I2C_1_TIMEOUT_PRESCALER_ENABLED)
            #define I2C_1_SCL_PRESCALER_AUX_CTRL_REG \
                                    (*(reg8 *) I2C_1_bTimeoutTimer_SclPrescaler_prScl__CONTROL_AUX_CTL_REG)
            #define I2C_1_SCL_PRESCALER_AUX_CTRL_PTR \
                                    ( (reg8 *) I2C_1_bTimeoutTimer_SclPrescaler_prScl__CONTROL_AUX_CTL_REG)

            #define I2C_1_SCL_PRESCALER_PRD_REG  \
                                    (*(reg8 *) I2C_1_bTimeoutTimer_SclPrescaler_prScl__PERIOD_REG)
            #define I2C_1_SCL_PRESCALER_PRD_PTR  \
                                    ( (reg8 *) I2C_1_bTimeoutTimer_SclPrescaler_prScl__PERIOD_REG)

        #endif /* (I2C_1_TIMEOUT_PRESCALER_ENABLED) */
    #endif     /* (I2C_1_TIMEOUT_SCL_TMOUT_ENABLED) */

    #if (I2C_1_TIMEOUT_SDA_TMOUT_ENABLED)
        #define I2C_1_TMOUT_SDA_PRD0_REG     (*(reg8 *) I2C_1_bTimeoutTimer_Sda_dpSda_u0__F0_REG)
        #define I2C_1_TMOUT_SDA_PRD0_PTR     ( (reg8 *) I2C_1_bTimeoutTimer_Sda_dpSda_u0__F0_REG)

        #define I2C_1_TMOUT_SDA_PRD1_REG     (*(reg8 *) I2C_1_bTimeoutTimer_Sda_dpSda_u0__F1_REG)
        #define I2C_1_TMOUT_SDA_PRD1_PTR     ( (reg8 *) I2C_1_bTimeoutTimer_Sda_dpSda_u0__F1_REG)

        #define I2C_1_TMOUT_SDA_ADDER_REG    (*(reg8 *) I2C_1_bTimeoutTimer_Sda_dpSda_u0__D0_REG)
        #define I2C_1_TMOUT_SDA_ADDER_PTR    ( (reg8 *) I2C_1_bTimeoutTimer_Sda_dpSda_u0__D0_REG)

        #define I2C_1_TMOUT_SDA_AUX_CTRL_REG \
                                                (*(reg8 *) I2C_1_bTimeoutTimer_Sda_dpSda_u0__DP_AUX_CTL_REG)
        #define I2C_1_TMOUT_SDA_AUX_CTRL_PTR \
                                                ( (reg8 *) I2C_1_bTimeoutTimer_Sda_dpSda_u0__DP_AUX_CTL_REG)

        #if (I2C_1_TIMEOUT_PRESCALER_ENABLED)
            #define I2C_1_SDA_PRESCALER_AUX_CTRL_REG \
                                    (*(reg8 *) I2C_1_bTimeoutTimer_SdaPrescaler_prSda__CONTROL_AUX_CTL_REG)
            #define I2C_1_SDA_PRESCALER_AUX_CTRL_PTR \
                                    ( (reg8 *) I2C_1_bTimeoutTimer_SdaPrescaler_prSda__CONTROL_AUX_CTL_REG)

            #define I2C_1_SDA_PRESCALER_PRD_REG \
                                    (*(reg8 *) I2C_1_bTimeoutTimer_SdaPrescaler_prSda__PERIOD_REG)
            #define I2C_1_SDA_PRESCALER_PRD_PTR \
                                    ( (reg8 *) I2C_1_bTimeoutTimer_SdaPrescaler_prSda__PERIOD_REG)

        #endif /* (I2C_1_TIMEOUT_PRESCALER_ENABLED) */
    #endif /* (I2C_1_TIMEOUT_SDA_TMOUT_ENABLED) */

#endif /*(I2C_1_TIMEOUT_FF_ENABLED) */


/***************************************
*        Registers Constants
***************************************/

#if (I2C_1_TIMEOUT_FF_ENABLED)
    /* I2C_1_TMOUT_CSR */
    #define I2C_1_TMOUT_CSR_SDA_PIN_POS      (4u)
    #define I2C_1_TMOUT_CSR_SCL_PIN_POS      (3u)
    #define I2C_1_TMOUT_CSR_I2C_TMOUT_IE_POS (2u)
    #define I2C_1_TMOUT_CSR_SDA_TMOUT_IE_POS (1u)
    #define I2C_1_TMOUT_CSR_SCL_TMOUT_IE_POS (0u)
    #define I2C_1_TMOUT_CSR_SDA_PIN_STS  ((uint8) (0x01u << I2C_1_TMOUT_CSR_SDA_PIN_POS))
    #define I2C_1_TMOUT_CSR_SCL_PIN_STS  ((uint8) (0x01u << I2C_1_TMOUT_CSR_SCL_PIN_POS))
    #define I2C_1_TMOUT_CSR_I2C_TMOUT_IE ((uint8) (0x01u << I2C_1_TMOUT_CSR_I2C_TMOUT_IE_POS))
    #define I2C_1_TMOUT_CSR_SDA_TMOUT_IE ((uint8) (0x01u << I2C_1_TMOUT_CSR_SDA_TMOUT_IE_POS))
    #define I2C_1_TMOUT_CSR_SCL_TMOUT_IE ((uint8) (0x01u << I2C_1_TMOUT_CSR_SCL_TMOUT_IE_POS))
    #define I2C_1_TMOUT_CSR_INTR_MASK    ((uint8) (0x03u << I2C_1_TMOUT_CSR_SCL_TMOUT_IE_POS))

    /* I2C_1_TMOUT_SR */
    #define I2C_1_TMOUT_SR_SDA_PIN_TMOUT_POS (1u)
    #define I2C_1_TMOUT_SR_SCL_PIN_TMOUT_POS (0u)
    #define I2C_1_TMOUT_SR_SDA_PIN_TMOUT ((uint8) (0x01u << I2C_1_TMOUT_SR_SDA_PIN_TMOUT_STS_POS))
    #define I2C_1_TMOUT_SR_SCL_PIN_TMOUT ((uint8) (0x01u << I2C_1_TMOUT_SR_SCL_PIN_TMOUT_STS_POS))
    #define I2C_1_TMOUT_SR_PINS_TMOUT_MASK   ((uint8) (0x03u << I2C_1_TMOUT_SR_SCL_PIN_TMOUT_POS))

    /*I2C_1_TMOUT_CFG0 and I2C_1_TMOUT_CFG1 */
    #define I2C_1_TMOUT_CFG0__MASK   (0xFFu)
    #define I2C_1_TMOUT_CFG1__MASK   (0x0Fu)

#else

    /* Interrupt setup */
    #define I2C_1_TMOUT_ISR_NUMBER   ((uint8) I2C_1_I2C_TMOUT__INTC_NUMBER)
    #define I2C_1_TMOUT_ISR_PRIORITY ((uint8) I2C_1_I2C_TMOUT__INTC_PRIOR_NUM)

    /* Timeout STATUS register constants */
    #define I2C_1_TMOUT_CTRL_ENABLE_POS  (0u)
    #define I2C_1_TMOUT_CTRL_ENABLE      ((uint8) (0x01u << I2C_1_TMOUT_CTRL_ENABLE_POS))

    /* Timeout STATUS register constants */
    #define I2C_1_TMOUT_STS_SDA_PIN_POS  (3u)
    #define I2C_1_TMOUT_STS_SCL_PIN_POS  (4u)
    #define I2C_1_TMOUT_STS_SDA_INTR_POS (1u)
    #define I2C_1_TMOUT_STS_SCL_INTR_POS (0u)
    #define I2C_1_TMOUT_STS_SCL_PINS     ((uint8) (0x01u << I2C_1_TMOUT_STS_SDA_PIN_POS))
    #define I2C_1_TMOUT_STS_SDA_PIN      ((uint8) (0x01u << I2C_1_TMOUT_STS_SCL_PIN_POS))
    #define I2C_1_TMOUT_STS_SCL_INTR     ((uint8) (0x01u << I2C_1_TMOUT_STS_SDA_INTR_POS))
    #define I2C_1_TMOUT_STS_SDA_INTR     ((uint8) (0x01u << I2C_1_TMOUT_STS_SCL_INTR_POS))
    #define I2C_1_TMOUT_STS_INTR_MASK    ((uint8) (0x03u << I2C_1_TMOUT_STS_SCL_INTR_POS))

    /* AUX_CTL bits definition */
    #define I2C_1_TMOUT_FIFO_SINGLE_REG      (0x03u) /* Makes f0 and f1 as single reg */
    #define I2C_1_TMOUT_PRESCALER_CNT7_EN    (0x20u) /* Enable 7-bit counter */
    #define I2C_1_TMOUT_ENABLE_INTR          (0x10u) /* Enable interrupt from status register */

#endif /* (I2C_1_TIMEOUT_FF_ENABLED) */


/***************************************
*        Marco
***************************************/

#if (I2C_1_TIMEOUT_FF_ENABLED)
    /* Returns true if timeout functionality is enabled */
    #define I2C_1_IS_TIMEOUT_ENABLED (0u != (I2C_1_TMOUT_CSR_REG & \
                                                        I2C_1_TMOUT_CSR_I2C_TMOUT_IE))

#else
    /* Returns true if timeout functionality is enabled */
    #define I2C_1_IS_TIMEOUT_ENABLED (0u != (I2C_1_TMOUT_CTRL_ENABLE & \
                                                        I2C_1_TMOUT_CTRL_REG))
#endif /* (I2C_1_TIMEOUT_FF_ENABLED) */


/***************************************
*     Default register init constants
***************************************/

#define I2C_1_DEFAULT_TMOUT_PERIOD   ((I2C_1_TIMEOUT_FF_ENABLED) ? \
                                                    ((uint16) 39999u) : ((uint16) 39999u))
#define I2C_1_DEFAULT_TMOUT_PRESCALER_PRD    (3u)
#define I2C_1_DEFAULT_TMOUT_INTR_MASK        ((uint8) (I2C_1_TIMEOUT_SDA_TMOUT_ENABLE << 1u) | \
                                                                  I2C_1_TIMEOUT_SCL_TMOUT_ENABLE)
#define I2C_1_DEFAULT_TMOUT_ADDER    (0xFFu)

#endif /* (CY_I2C_TMOUT_I2C_1_H) */


/* [] END OF FILE */
