/*******************************************************************************
* File Name: ShiftReg_3_PM.c
* Version 2.30
*
* Description:
*  This file provides the API source code for sleep mode support for Shift
*  Register component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ShiftReg_3.h"

static ShiftReg_3_BACKUP_STRUCT ShiftReg_3_backup =
{
    ShiftReg_3_DISABLED,

    ((uint32) ShiftReg_3_DEFAULT_A0),
    ((uint32) ShiftReg_3_DEFAULT_A1),

    #if(CY_UDB_V0)
        ((uint32) ShiftReg_3_INT_SRC),
    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: ShiftReg_3_SaveConfig
********************************************************************************
*
* Summary:
*  Saves Shift Register configuration.
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
void ShiftReg_3_SaveConfig(void) 
{
    /* Store working registers A0 and A1 */
    ShiftReg_3_backup.saveSrA0Reg   = CY_GET_REG32(ShiftReg_3_SHIFT_REG_LSB_PTR);
    ShiftReg_3_backup.saveSrA1Reg   = CY_GET_REG32(ShiftReg_3_SHIFT_REG_VALUE_LSB_PTR);

    #if(CY_UDB_V0)
        ShiftReg_3_backup.saveSrIntMask = ShiftReg_3_SR_STATUS_MASK;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: ShiftReg_3_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ShiftReg_3_RestoreConfig(void) 
{
    /* Restore working registers A0 and A1 */
    CY_SET_REG32(ShiftReg_3_SHIFT_REG_LSB_PTR, ShiftReg_3_backup.saveSrA0Reg);
    CY_SET_REG32(ShiftReg_3_SHIFT_REG_VALUE_LSB_PTR, ShiftReg_3_backup.saveSrA1Reg);

    #if(CY_UDB_V0)
        ShiftReg_3_SR_STATUS_MASK = ((uint8) ShiftReg_3_backup.saveSrIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: ShiftReg_3_Sleep
********************************************************************************
*
* Summary:
*  Prepare the component to enter a Sleep mode.
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
void ShiftReg_3_Sleep(void) 
{
    ShiftReg_3_backup.enableState = ((uint8) ShiftReg_3_IS_ENABLED);

    ShiftReg_3_Stop();
    ShiftReg_3_SaveConfig();
}


/*******************************************************************************
* Function Name: ShiftReg_3_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ShiftReg_3_Wakeup(void) 
{
    ShiftReg_3_RestoreConfig();

    if(0u != ShiftReg_3_backup.enableState)
    {
        ShiftReg_3_Enable();
    }
}


/* [] END OF FILE */
