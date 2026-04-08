/*******************************************************************************
* File Name: SPIM_3_PM.c
* Version 2.50
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPIM_3_PVT.h"

static SPIM_3_BACKUP_STRUCT SPIM_3_backup =
{
    SPIM_3_DISABLED,
    SPIM_3_BITCTR_INIT,
};


/*******************************************************************************
* Function Name: SPIM_3_SaveConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SPIM_3_SaveConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPIM_3_RestoreConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SPIM_3_RestoreConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPIM_3_Sleep
********************************************************************************
*
* Summary:
*  Prepare SPIM Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SPIM_3_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPIM_3_Sleep(void) 
{
    /* Save components enable state */
    SPIM_3_backup.enableState = ((uint8) SPIM_3_IS_ENABLED);

    SPIM_3_Stop();
}


/*******************************************************************************
* Function Name: SPIM_3_Wakeup
********************************************************************************
*
* Summary:
*  Prepare SPIM Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SPIM_3_backup - used when non-retention registers are restored.
*  SPIM_3_txBufferWrite - modified every function call - resets to
*  zero.
*  SPIM_3_txBufferRead - modified every function call - resets to
*  zero.
*  SPIM_3_rxBufferWrite - modified every function call - resets to
*  zero.
*  SPIM_3_rxBufferRead - modified every function call - resets to
*  zero.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPIM_3_Wakeup(void) 
{
    #if(SPIM_3_RX_SOFTWARE_BUF_ENABLED)
        SPIM_3_rxBufferFull  = 0u;
        SPIM_3_rxBufferRead  = 0u;
        SPIM_3_rxBufferWrite = 0u;
    #endif /* (SPIM_3_RX_SOFTWARE_BUF_ENABLED) */

    #if(SPIM_3_TX_SOFTWARE_BUF_ENABLED)
        SPIM_3_txBufferFull  = 0u;
        SPIM_3_txBufferRead  = 0u;
        SPIM_3_txBufferWrite = 0u;
    #endif /* (SPIM_3_TX_SOFTWARE_BUF_ENABLED) */

    /* Clear any data from the RX and TX FIFO */
    SPIM_3_ClearFIFO();

    /* Restore components block enable state */
    if(0u != SPIM_3_backup.enableState)
    {
        SPIM_3_Enable();
    }
}


/* [] END OF FILE */
