/*******************************************************************************
* File Name: .h
* Version 2.50
*
* Description:
*  This private header file contains internal definitions for the SPIM
*  component. Do not use these definitions directly in your application.
*
* Note:
*
********************************************************************************
* Copyright 2012-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIM_PVT_SPIM_3_H)
#define CY_SPIM_PVT_SPIM_3_H

#include "SPIM_3.h"


/**********************************
*   Functions with external linkage
**********************************/


/**********************************
*   Variables with external linkage
**********************************/

extern volatile uint8 SPIM_3_swStatusTx;
extern volatile uint8 SPIM_3_swStatusRx;

#if(SPIM_3_TX_SOFTWARE_BUF_ENABLED)
    extern volatile uint8 SPIM_3_txBuffer[SPIM_3_TX_BUFFER_SIZE];
    extern volatile uint8 SPIM_3_txBufferRead;
    extern volatile uint8 SPIM_3_txBufferWrite;
    extern volatile uint8 SPIM_3_txBufferFull;
#endif /* (SPIM_3_TX_SOFTWARE_BUF_ENABLED) */

#if(SPIM_3_RX_SOFTWARE_BUF_ENABLED)
    extern volatile uint8 SPIM_3_rxBuffer[SPIM_3_RX_BUFFER_SIZE];
    extern volatile uint8 SPIM_3_rxBufferRead;
    extern volatile uint8 SPIM_3_rxBufferWrite;
    extern volatile uint8 SPIM_3_rxBufferFull;
#endif /* (SPIM_3_RX_SOFTWARE_BUF_ENABLED) */

#endif /* CY_SPIM_PVT_SPIM_3_H */


/* [] END OF FILE */
