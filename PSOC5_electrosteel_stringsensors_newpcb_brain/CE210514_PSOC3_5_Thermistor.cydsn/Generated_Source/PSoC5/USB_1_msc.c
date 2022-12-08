/***************************************************************************//**
* \file USB_1_cdc.c
* \version 3.20
*
* \brief
*  This file contains the USB MSC Class request handler and global API for MSC 
*  class.
*
* Related Document:
*  Universal Serial Bus Class Definitions for Communication Devices Version 1.1
*
********************************************************************************
* \copyright
* Copyright 2012-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USB_1_msc.h"
#include "USB_1_pvt.h"


#if (USB_1_HANDLE_MSC_REQUESTS)

/***************************************
*          Internal variables
***************************************/

static uint8 USB_1_lunCount = USB_1_MSC_LUN_NUMBER;


/*******************************************************************************
* Function Name: USB_1_DispatchMSCClassRqst
****************************************************************************//**
*   
*  \internal 
*  This routine dispatches MSC class requests.
*
* \return
*  Status of request processing: handled or not handled.
*
* \globalvars
*  USB_1_lunCount - stores number of LUN (logical units).
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USB_1_DispatchMSCClassRqst(void) 
{
    uint8 requestHandled = USB_1_FALSE;
    
    /* Get request data. */
    uint16 value  = USB_1_GET_UINT16(USB_1_wValueHiReg,  USB_1_wValueLoReg);
    uint16 dataLength = USB_1_GET_UINT16(USB_1_wLengthHiReg, USB_1_wLengthLoReg);
       
    /* Check request direction: D2H or H2D. */
    if (0u != (USB_1_bmRequestTypeReg & USB_1_RQST_DIR_D2H))
    {
        /* Handle direction from device to host. */
        
        if (USB_1_MSC_GET_MAX_LUN == USB_1_bRequestReg)
        {
            /* Check request fields. */
            if ((value  == USB_1_MSC_GET_MAX_LUN_WVALUE) &&
                (dataLength == USB_1_MSC_GET_MAX_LUN_WLENGTH))
            {
                /* Reply to Get Max LUN request: setup control read. */
                USB_1_currentTD.pData = &USB_1_lunCount;
                USB_1_currentTD.count =  USB_1_MSC_GET_MAX_LUN_WLENGTH;
                
                requestHandled  = USB_1_InitControlRead();
            }
        }
    }
    else
    {
        /* Handle direction from host to device. */
        
        if (USB_1_MSC_RESET == USB_1_bRequestReg)
        {
            /* Check request fields. */
            if ((value  == USB_1_MSC_RESET_WVALUE) &&
                (dataLength == USB_1_MSC_RESET_WLENGTH))
            {
                /* Handle to Bulk-Only Reset request: no data control transfer. */
                USB_1_currentTD.count = USB_1_MSC_RESET_WLENGTH;
                
            #ifdef USB_1_DISPATCH_MSC_CLASS_MSC_RESET_RQST_CALLBACK
                USB_1_DispatchMSCClass_MSC_RESET_RQST_Callback();
            #endif /* (USB_1_DISPATCH_MSC_CLASS_MSC_RESET_RQST_CALLBACK) */
                
                requestHandled = USB_1_InitNoDataControlTransfer();
            }
        }
    }
    
    return (requestHandled);
}


/*******************************************************************************
* Function Name: USB_1_MSC_SetLunCount
****************************************************************************//**
*
*  This function sets the number of logical units supported in the application. 
*  The default number of logical units is set in the component customizer.
*
*  \param lunCount: Count of the logical units. Valid range is between 1 and 16.
*
*
* \globalvars
*  USB_1_lunCount - stores number of LUN (logical units).
*
* \reentrant
*  No.
*
*******************************************************************************/
void USB_1_MSC_SetLunCount(uint8 lunCount) 
{
    USB_1_lunCount = (lunCount - 1u);
}


/*******************************************************************************
* Function Name: USB_1_MSC_GetLunCount
****************************************************************************//**
*
*  This function returns the number of logical units.
*
* \return
*   Number of the logical units.
*
* \globalvars
*  USB_1_lunCount - stores number of LUN (logical units).
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USB_1_MSC_GetLunCount(void) 
{
    return (USB_1_lunCount + 1u);
}   

#endif /* (USB_1_HANDLE_MSC_REQUESTS) */


/* [] END OF FILE */
