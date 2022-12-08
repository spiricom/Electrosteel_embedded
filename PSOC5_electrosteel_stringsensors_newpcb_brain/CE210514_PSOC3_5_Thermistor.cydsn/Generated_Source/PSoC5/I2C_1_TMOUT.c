/*******************************************************************************
* File Name: I2C_1_TMOUT.c
* Version 3.50
*
* Description:
*  This file provides the source code of APIs for the timeout feature of
*  the I2C component.
*
* Note:
*
*******************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "I2C_1_PVT.h"


/*******************************************************************************
* Function Name: I2C_1_TimeoutInit
********************************************************************************
*
* Summary:
*  Initialize the timeout timer hardware.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void I2C_1_TimeoutInit(void) 
{
#if (I2C_1_TIMEOUT_UDB_ENABLED)
    uint8 enableInterrupts;

    /* Configure timeout interrupt */
    CyIntDisable    (I2C_1_TMOUT_ISR_NUMBER);
    CyIntSetPriority(I2C_1_TMOUT_ISR_NUMBER, I2C_1_TMOUT_ISR_PRIORITY);
    #if (I2C_1_INTERN_TMOUT_INTR_HANDLER)
        (void) CyIntSetVector(I2C_1_TMOUT_ISR_NUMBER, &I2C_1_TMOUT_ISR);
    #endif /* (I2C_1_INTERN_TMOUT_INTR_HANDLER) */

    I2C_1_TimeoutSetIntrMode(I2C_1_DEFAULT_TMOUT_INTR_MASK);

    /* Configure interrupt sources */
    enableInterrupts = CyEnterCriticalSection();
    I2C_1_TMOUT_INTR_ENABLE_REG |= I2C_1_TMOUT_ENABLE_INTR;
    CyExitCriticalSection(enableInterrupts);

    #if (I2C_1_TIMEOUT_SCL_TMOUT_ENABLED)
        I2C_1_TMOUT_SCL_ADDER_REG = I2C_1_DEFAULT_TMOUT_ADDER;

        /* Configure F0 and F1 operation */
        enableInterrupts = CyEnterCriticalSection();
        I2C_1_TMOUT_SCL_AUX_CTRL_REG |= I2C_1_TMOUT_FIFO_SINGLE_REG;
        CyExitCriticalSection(enableInterrupts);
    #endif /* (I2C_1_TIMEOUT_SCL_TMOUT_ENABLED) */


    #if (I2C_1_TIMEOUT_SDA_TMOUT_ENABLED)
        I2C_1_TMOUT_SDA_ADDER_REG = I2C_1_DEFAULT_TMOUT_ADDER;

        /* Configure F0 and F1 operation */
        enableInterrupts = CyEnterCriticalSection();
        I2C_1_TMOUT_SDA_AUX_CTRL_REG |= I2C_1_TMOUT_FIFO_SINGLE_REG;
        CyExitCriticalSection(enableInterrupts);
    #endif /* (I2C_1_TIMEOUT_SDA_TMOUT_ENABLED) */


    #if (I2C_1_TIMEOUT_PRESCALER_ENABLED)
        I2C_1_TimeoutSetPrescalerPeriod(I2C_1_DEFAULT_TMOUT_PRESCALER_PRD);

        /* Enable counter for prescaler */
        enableInterrupts = CyEnterCriticalSection();
    #if (I2C_1_TIMEOUT_SCL_TMOUT_ENABLED)
        I2C_1_SCL_PRESCALER_AUX_CTRL_REG |= I2C_1_TMOUT_PRESCALER_CNT7_EN;
    #endif /* (I2C_1_TIMEOUT_SCL_TMOUT_ENABLED) */

    #if (I2C_1_TIMEOUT_SDA_TMOUT_ENABLED)
        I2C_1_SDA_PRESCALER_AUX_CTRL_REG |= I2C_1_TMOUT_PRESCALER_CNT7_EN;
    #endif /* (I2C_1_TIMEOUT_SDA_TMOUT_ENABLED) */
        CyExitCriticalSection(enableInterrupts);

    #endif /* (I2C_1_TIMEOUT_PRESCALER_ENABLED)  */
#endif     /* (I2C_1_TIMEOUT_UDB_ENABLED)        */

    /* Set default parameters */
    I2C_1_TimeoutSetPeriod(I2C_1_DEFAULT_TMOUT_PERIOD);
    I2C_1_TimeoutSetIntrMode(I2C_1_DEFAULT_TMOUT_INTR_MASK);
}


/*******************************************************************************
* Function Name: I2C_1_TimeoutEnable
********************************************************************************
*
* Summary:
*  Enables the timeout interrupt and timer. The timeout timer starts operation
*  depending on the bus event.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void I2C_1_TimeoutEnable(void) 
{
#if (I2C_1_TIMEOUT_UDB_ENABLED)
    I2C_1_TMOUT_CTRL_REG |= I2C_1_TMOUT_CTRL_ENABLE;
#endif /* (I2C_1_TIMEOUT_UDB_ENABLED) */

    I2C_1_TimeoutEnableInt(); /* Enable interrupt on timeout event */
}


/*******************************************************************************
* Function Name: I2C_1_TimeoutStop
********************************************************************************
*
* Summary:
*   Disables the timeout timer hardware. Disable interrupt and clear pending
*   if exist.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void I2C_1_TimeoutStop(void) 
{
    I2C_1_TimeoutDisableInt();
    I2C_1_TimeoutClearPendingInt();

    /* Re-arm timeout */
#if (I2C_1_TIMEOUT_FF_ENABLED)
    I2C_1_TimeoutClearStatus(I2C_1_TMOUT_SR_PINS_TMOUT_MASK);
#else
    I2C_1_TMOUT_CTRL_REG &= (uint8) ~I2C_1_TMOUT_CTRL_ENABLE;
#endif /* (I2C_1_TIMEOUT_UDB_ENABLED) */
}


/*******************************************************************************
* Function Name: I2C_1_TimeoutSetPeriod
********************************************************************************
*
* Summary:
*  Sets period of the scl and sda timeout counters.
*
* Parameters:
*  period:  the period of the scl and sda timeout. This number depends on
*           BUSCLK for FF implementation on PSOC5LP and on input
*           clock (16*DataRate) for UDB implementation.
*
* Return:
*  None.
*
*******************************************************************************/
void I2C_1_TimeoutSetPeriod(uint16 period) 
{
#if (I2C_1_TIMEOUT_FF_ENABLED)
    I2C_1_TMOUT_CFG0_REG = LO8(period);
    I2C_1_TMOUT_CFG1_REG = HI8(period);

#else
    #if (I2C_1_TIMEOUT_SCL_TMOUT_ENABLED)
        I2C_1_TMOUT_SCL_PRD0_REG = LO8(period);
        I2C_1_TMOUT_SCL_PRD1_REG = HI8(period);
    #endif /* (I2C_1_TIMEOUT_SCL_TMOUT_ENABLED) */

    #if (I2C_1_TIMEOUT_SDA_TMOUT_ENABLED)
        I2C_1_TMOUT_SDA_PRD0_REG = LO8(period);
        I2C_1_TMOUT_SDA_PRD1_REG = HI8(period);
    #endif /* (I2C_1_TIMEOUT_SDA_TMOUT_ENABLED)  */
#endif     /* (I2C_1_FF_TIMEOUT_ENABLED) */
}


/*******************************************************************************
* Function Name: I2C_1_TimeoutSetPeriod
********************************************************************************
*
* Summary:
*  Returns a period of the scl and sda timeout counters.
*
* Parameters:
*  None.
*
* Return:
*  Returns a period of the scl and sda timeout.
*
*******************************************************************************/
uint16 I2C_1_TimeoutGetPeriod(void) 
{
    uint16 period;

#if (I2C_1_TIMEOUT_FF_ENABLED)
    period  = ((uint16) I2C_1_TMOUT_CFG1_REG) << 8u;
    period |= I2C_1_TMOUT_CFG0_REG;

#else
    #if (I2C_1_TIMEOUT_SCL_TMOUT_ENABLED)
        period  = ((uint16) I2C_1_TMOUT_SCL_PRD1_REG) << 8u;
        period |= I2C_1_TMOUT_SCL_PRD0_REG;
    #else
        period  = ((uint16) I2C_1_TMOUT_SDA_PRD1_REG) << 8u;
        period |= I2C_1_TMOUT_SDA_PRD0_REG;
    #endif /* (I2C_1_TIMEOUT_SDA_TMOUT_ENABLED) */
#endif /* (I2C_1_FF_TIMEOUT_ENABLED) */

    return(period);
}


#if (I2C_1_TIMEOUT_UDB_ENABLED && I2C_1_TIMEOUT_PRESCALER_ENABLED)
    /*******************************************************************************
    * Function Name: I2C_1_TimeoutSetPrescalerPeriod
    ********************************************************************************
    *
    * Summary:
    *  Sets a prescaler value to increase the divider possibility for the UDB
    *  timeout feature.
    *
    * Parameters:
    *  period: The prescaler period value.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void I2C_1_TimeoutSetPrescalerPeriod(uint8 period)
                                                    
    {
    #if (I2C_1_TIMEOUT_SCL_TMOUT_ENABLED)
        I2C_1_SCL_PRESCALER_PRD_REG = period;
    #endif /* (I2C_1_TIMEOUT_SCL_TMOUT_ENABLED) */

    #if (I2C_1_TIMEOUT_SDA_TMOUT_ENABLED)
        I2C_1_SDA_PRESCALER_PRD_REG = period;
    #endif /* (I2C_1_TIMEOUT_SDA_TMOUT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: I2C_1_TimeoutGetPrescalerPeriod
    ********************************************************************************
    *
    * Summary:
    *  Returns a prescaler value.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Returns a prescaler value.
    *
    *******************************************************************************/
    uint8 I2C_1_TimeoutGetPrescalerPeriod(void)
                                                    
    {
    #if (I2C_1_TIMEOUT_SCL_TMOUT_ENABLED)
        return (I2C_1_SCL_PRESCALER_PRD_REG);
    #else
        return (I2C_1_SDA_PRESCALER_PRD_REG);
    #endif /* (I2C_1_TIMEOUT_SCL_TMOUT_ENABLED) */
    }
#endif /* (I2C_1_TIMEOUT_PRESCALER_ENABLED) */


/*******************************************************************************
* Function Name: I2C_1_TimeoutSaveConfig
********************************************************************************
*
* Summary:
*  Saves the configuration of the timeout timer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void I2C_1_TimeoutSaveConfig(void) 
{
    I2C_1_backup.tmoutCfg  = I2C_1_TimeoutGetPeriod();
    I2C_1_backup.tmoutIntr = I2C_1_TimeoutGetIntrMode();
}


/*******************************************************************************
* Function Name: I2C_1_TimeoutRestoreConfig
********************************************************************************
*
* Summary:
*  Restores the configuration of the timeout timer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void I2C_1_TimeoutRestoreConfig(void) 
{
    I2C_1_TimeoutSetPeriod  (I2C_1_backup.tmoutCfg);
    I2C_1_TimeoutSetIntrMode(I2C_1_backup.tmoutIntr);
}


/* [] END OF FILE */
