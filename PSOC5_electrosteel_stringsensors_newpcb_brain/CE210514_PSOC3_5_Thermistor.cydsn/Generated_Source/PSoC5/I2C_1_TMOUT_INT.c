/*******************************************************************************
* File Name: I2C_1_TMOUT_INT.c
* Version 3.50
*
* Description:
*  This file provides the source code of Interrupt Service Routine (ISR)
*  for the timeout feature of the I2C component.
*
*  Note:
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "I2C_1_PVT.h"



/*******************************************************************************
*  Place your includes, defines and code here
*******************************************************************************/
/* `#START I2C_1_TMOUT_ISR_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: I2C_1_TimeoutReset
********************************************************************************
*
* Summary:
*  Resets the component into the known state (default) and enables it.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No
*
*******************************************************************************/
void I2C_1_TimeoutReset(void) 
{
    /* Reset component into known state (default) */
    I2C_1_Stop();

    /* `#START I2C_1_TMOUT_ISR_BEFORE_BUF_RESET` */

    /* `#END` */
    
#ifdef I2C_1_TIMEOUT_RESET_CALLBACK
    I2C_1_TimeoutReset_Callback();
#endif /* I2C_1_TIMEOUT_RESET_CALLBACK */

#if (I2C_1_MODE_SLAVE_ENABLED)
    /* Clear status and buffers */
    I2C_1_SlaveClearReadBuf();
    I2C_1_SlaveClearWriteBuf();
    (void) I2C_1_SlaveClearReadStatus();
    (void) I2C_1_SlaveClearWriteStatus();
#endif /* (I2C_1_MODE_SLAVE_ENABLED) */

#if (I2C_1_MODE_MASTER_ENABLED)
    /* Clear status and buffers */
    I2C_1_MasterClearReadBuf();
    I2C_1_MasterClearWriteBuf();
    (void) I2C_1_MasterClearStatus();
#endif /* (I2C_1_MODE_MASTER_ENABLED) */

    /* Enable component operation */
    I2C_1_Enable();
    I2C_1_EnableInt();
}


#if (I2C_1_TIMEOUT_UDB_ENABLED)
    /*******************************************************************************
    * Function Name: I2C_1_TMOUT_ISR
    ********************************************************************************
    *
    * Summary:
    *  The handler of the I2C timeout interrupt.
    *  Triggers when SCL or SDA remain in the low state greater than a defined
    *  timeout. Resets the component into the known state and enables it for
    *  the following operations.
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
    CY_ISR(I2C_1_TMOUT_ISR)
    {
    #ifdef I2C_1_TMOUT_ISR_ENTRY_CALLBACK
        I2C_1_TMOUT_ISR_EntryCallback();
    #endif /* I2C_1_TMOUT_ISR_ENTRY_CALLBACK */
        
        I2C_1_TimeoutReset();

    #ifdef I2C_1_TMOUT_ISR_EXIT_CALLBACK
        I2C_1_TMOUT_ISR_ExitCallback();
    #endif /* I2C_1_TMOUT_ISR_EXIT_CALLBACK*/
    }
#endif /* (I2C_1_TIMEOUT_UDB_ENABLED) */


/* [] END OF FILE */
