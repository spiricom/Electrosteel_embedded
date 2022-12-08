/***************************************************************************//**
* \file USB_1_audio.c
* \version 3.20
*
* \brief
*  This file contains the USB AUDIO Class request handler.
*
* Related Document:
*  Universal Serial Bus Device Class Definition for Audio Devices Release 1.0
*
********************************************************************************
* \copyright
* Copyright 2008-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "USB_1_audio.h"
#include "USB_1_pvt.h"


#if defined(USB_1_ENABLE_AUDIO_CLASS)

/***************************************
* Custom Declarations
***************************************/

/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */


#if !defined(USER_SUPPLIED_AUDIO_HANDLER)

/***************************************
*    AUDIO Variables
***************************************/

#if defined(USB_1_ENABLE_AUDIO_STREAMING)
    /** Contains the current audio sample frequency. It is set by the host using a SET_CUR request to the endpoint.*/
    volatile uint8 USB_1_currentSampleFrequency[USB_1_MAX_EP][USB_1_SAMPLE_FREQ_LEN];
    /** Used as a flag for the user code, to inform it that the host has been sent a request 
     * to change the sample frequency. The sample frequency will be sent on the next OUT transaction. 
     * It contains the endpoint address when set. The following code is recommended for 
     * detecting new sample frequency in main code:
     * \snippet  /USBFS_sut_02.cydsn/main.c Detecting new Sample Frequency
     *     
     * The USBFS_transferState variable is checked to make sure that the transfer completes. */
    volatile uint8 USB_1_frequencyChanged;
    /** Contains the mute configuration set by the host.*/
    volatile uint8 USB_1_currentMute;
    /** Contains the volume level set by the host.*/
    volatile uint8 USB_1_currentVolume[USB_1_VOLUME_LEN];
    volatile uint8 USB_1_minimumVolume[USB_1_VOLUME_LEN] = {USB_1_VOL_MIN_LSB,
                                                                                  USB_1_VOL_MIN_MSB};
    volatile uint8 USB_1_maximumVolume[USB_1_VOLUME_LEN] = {USB_1_VOL_MAX_LSB,
                                                                                  USB_1_VOL_MAX_MSB};
    volatile uint8 USB_1_resolutionVolume[USB_1_VOLUME_LEN] = {USB_1_VOL_RES_LSB,
                                                                                     USB_1_VOL_RES_MSB};
#endif /*  USB_1_ENABLE_AUDIO_STREAMING */


/*******************************************************************************
* Function Name: USB_1_DispatchAUDIOClassRqst
****************************************************************************//**
*
*  This routine dispatches class requests
*
* \return
*  Results of Audio Class request handling: 
*  - USB_1_TRUE  - request was handled without errors
*  - USB_1_FALSE - error occurs during handling of request     
*
* \globalvars
*   USB_1_currentSampleFrequency: Contains the current audio Sample
*       Frequency. It is set by the Host using SET_CUR request to the endpoint.
*   USB_1_frequencyChanged: This variable is used as a flag for the
*       user code, to be aware that Host has been sent request for changing
*       Sample Frequency. Sample frequency will be sent on the next OUT
*       transaction. It is contains endpoint address when set. The following
*       code is recommended for detecting new Sample Frequency in main code:
*       
*  \snippet  /USBFS_sut_02.cydsn/main.c Detecting new Sample Frequency
*      
*   USB_1_transferState variable is checked to be sure that transfer
*              completes.
*   USB_1_currentMute: Contains mute configuration set by Host.
*   USB_1_currentVolume: Contains volume level set by Host.
*
* \reentrant
*  No.
*
*******************************************************************************/
uint8 USB_1_DispatchAUDIOClassRqst(void) 
{
    uint8 requestHandled = USB_1_FALSE;
    
    uint8 RqstRcpt = (uint8)(USB_1_bmRequestTypeReg & USB_1_RQST_RCPT_MASK);
#if defined(USB_1_ENABLE_AUDIO_STREAMING)
    uint8 wValueHi = (uint8) USB_1_wValueHiReg;
    uint8 epNumber = (uint8) USB_1_wIndexLoReg & USB_1_DIR_UNUSED;
#endif /* (USB_1_ENABLE_AUDIO_STREAMING) */
    
    /* Check request direction: D2H or H2D. */
    if (0u != (USB_1_bmRequestTypeReg & USB_1_RQST_DIR_D2H))
    {
        /* Handle direction from device to host. */
        
        if (USB_1_RQST_RCPT_EP == RqstRcpt)
        {
            /* Request recipient is to endpoint. */
            switch (USB_1_bRequestReg)
            {
                case USB_1_GET_CUR:
                #if defined(USB_1_ENABLE_AUDIO_STREAMING)
                    if (wValueHi == USB_1_SAMPLING_FREQ_CONTROL)
                    {
                         /* point Control Selector is Sampling Frequency */
                        USB_1_currentTD.wCount = USB_1_SAMPLE_FREQ_LEN;
                        USB_1_currentTD.pData  = USB_1_currentSampleFrequency[epNumber];
                        
                        requestHandled   = USB_1_InitControlRead();
                    }
                #endif /* (USB_1_ENABLE_AUDIO_STREAMING) */
                
                    /* `#START AUDIO_READ_REQUESTS` Place other request handler here */

                    /* `#END` */
                
                #ifdef USB_1_DISPATCH_AUDIO_CLASS_AUDIO_READ_REQUESTS_CALLBACK    
                    USB_1_DispatchAUDIOClass_AUDIO_READ_REQUESTS_Callback();
                #endif /* (USB_1_DISPATCH_AUDIO_CLASS_AUDIO_READ_REQUESTS_CALLBACK) */                   
                break;
                
                default:
                    /* Do not handle this request unless callback is defined. */
                    break;
            }
        
        }
        else if (USB_1_RQST_RCPT_IFC == RqstRcpt)
        {
            /* Request recipient is interface or entity ID. */
            switch (USB_1_bRequestReg)
            {
                case USB_1_GET_CUR:
                #if defined(USB_1_ENABLE_AUDIO_STREAMING)
                    if (wValueHi == USB_1_MUTE_CONTROL)
                    {
                        /* `#START MUTE_CONTROL_GET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                    #ifdef USB_1_DISPATCH_AUDIO_CLASS_MUTE_CONTROL_GET_REQUEST_CALLBACK
                        USB_1_DispatchAUDIOClass_MUTE_CONTROL_GET_REQUEST_Callback();
                    #endif /* (USB_1_DISPATCH_AUDIO_CLASS_MUTE_CONTROL_GET_REQUEST_CALLBACK) */

                        /* Entity ID Control Selector is MUTE */
                        USB_1_currentTD.wCount = 1u;
                        USB_1_currentTD.pData  = &USB_1_currentMute;
                        
                        requestHandled = USB_1_InitControlRead();
                    }
                    else if (wValueHi == USB_1_VOLUME_CONTROL)
                    {
                        /* `#START VOLUME_CONTROL_GET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                    #ifdef USB_1_DISPATCH_AUDIO_CLASS_VOLUME_CONTROL_GET_REQUEST_CALLBACK
                        USB_1_DispatchAUDIOClass_VOLUME_CONTROL_GET_REQUEST_Callback();
                    #endif /* (USB_1_DISPATCH_AUDIO_CLASS_VOLUME_CONTROL_GET_REQUEST_CALLBACK) */

                        /* Entity ID Control Selector is VOLUME, */
                        USB_1_currentTD.wCount = USB_1_VOLUME_LEN;
                        USB_1_currentTD.pData  = USB_1_currentVolume;
                        
                        requestHandled = USB_1_InitControlRead();
                    }
                    else
                    {
                        /* `#START OTHER_GET_CUR_REQUESTS` Place other request handler here */

                        /* `#END` */

                    #ifdef USB_1_DISPATCH_AUDIO_CLASS_OTHER_GET_CUR_REQUESTS_CALLBACK
                        USB_1_DispatchAUDIOClass_OTHER_GET_CUR_REQUESTS_Callback();
                    #endif /* (USB_1_DISPATCH_AUDIO_CLASS_OTHER_GET_CUR_REQUESTS_CALLBACK) */
                    }
                    break;
                    
                case USB_1_GET_MIN:
                    if (wValueHi == USB_1_VOLUME_CONTROL)
                    {
                        /* Entity ID Control Selector is VOLUME, */
                        USB_1_currentTD.wCount = USB_1_VOLUME_LEN;
                        USB_1_currentTD.pData  = &USB_1_minimumVolume[0];
                        
                        requestHandled = USB_1_InitControlRead();
                    }
                    break;
                    
                case USB_1_GET_MAX:
                    if (wValueHi == USB_1_VOLUME_CONTROL)
                    {
                        /* Entity ID Control Selector is VOLUME, */
                        USB_1_currentTD.wCount = USB_1_VOLUME_LEN;
                        USB_1_currentTD.pData  = &USB_1_maximumVolume[0];
                        
                        requestHandled = USB_1_InitControlRead();
                    }
                    break;
                    
                case USB_1_GET_RES:
                    if (wValueHi == USB_1_VOLUME_CONTROL)
                    {
                         /* Entity ID Control Selector is VOLUME, */
                        USB_1_currentTD.wCount = USB_1_VOLUME_LEN;
                        USB_1_currentTD.pData  = &USB_1_resolutionVolume[0];
                        
                        requestHandled   = USB_1_InitControlRead();
                    }
                    break;
                    
                /* The contents of the status message is reserved for future use.
                * For the time being, a null packet should be returned in the data stage of the
                * control transfer, and the received null packet should be ACKed.
                */
                case USB_1_GET_STAT:
                    USB_1_currentTD.wCount = 0u;    
                    
                    requestHandled = USB_1_InitControlWrite();

                #endif /* (USB_1_ENABLE_AUDIO_STREAMING) */
                
                    /* `#START AUDIO_WRITE_REQUESTS` Place other request handler here */

                    /* `#END` */
                
                #ifdef USB_1_DISPATCH_AUDIO_CLASS_AUDIO_WRITE_REQUESTS_CALLBACK
                    USB_1_DispatchAUDIOClass_AUDIO_WRITE_REQUESTS_Callback();
                #endif /* (USB_1_DISPATCH_AUDIO_CLASS_AUDIO_WRITE_REQUESTS_CALLBACK) */
                    break;
                
                default:
                    /* Do not handle this request. */
                    break;
            }
        }
        else
        {   
            /* Do not handle other requests recipients. */
        }
    }
    else
    {
        /* Handle direction from host to device. */
        
        if (USB_1_RQST_RCPT_EP == RqstRcpt)
        {
            /* Request recipient is endpoint. */
            switch (USB_1_bRequestReg)
            {
                case USB_1_SET_CUR:
                #if defined(USB_1_ENABLE_AUDIO_STREAMING)
                    if (wValueHi == USB_1_SAMPLING_FREQ_CONTROL)
                    {
                         /* point Control Selector is Sampling Frequency */
                        USB_1_currentTD.wCount = USB_1_SAMPLE_FREQ_LEN;
                        USB_1_currentTD.pData  = USB_1_currentSampleFrequency[epNumber];
                        USB_1_frequencyChanged = (uint8) epNumber;
                        
                        requestHandled   = USB_1_InitControlWrite();
                    }
                #endif /* (USB_1_ENABLE_AUDIO_STREAMING) */

                    /* `#START AUDIO_SAMPLING_FREQ_REQUESTS` Place other request handler here */

                    /* `#END` */

                #ifdef USB_1_DISPATCH_AUDIO_CLASS_AUDIO_SAMPLING_FREQ_REQUESTS_CALLBACK
                    USB_1_DispatchAUDIOClass_AUDIO_SAMPLING_FREQ_REQUESTS_Callback();
                #endif /* (USB_1_DISPATCH_AUDIO_CLASS_AUDIO_SAMPLING_FREQ_REQUESTS_CALLBACK) */
                    break;
                
                default:
                    /* Do not handle this request. */
                    break;
            }
        }
        else if(USB_1_RQST_RCPT_IFC == RqstRcpt)
        {
            /* Request recipient is interface or entity ID. */
            switch (USB_1_bRequestReg)
            {
                case USB_1_SET_CUR:
                #if defined(USB_1_ENABLE_AUDIO_STREAMING)
                    if (wValueHi == USB_1_MUTE_CONTROL)
                    {
                        /* `#START MUTE_SET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                    #ifdef USB_1_DISPATCH_AUDIO_CLASS_MUTE_SET_REQUEST_CALLBACK
                        USB_1_DispatchAUDIOClass_MUTE_SET_REQUEST_Callback();
                    #endif /* (USB_1_DISPATCH_AUDIO_CLASS_MUTE_SET_REQUEST_CALLBACK) */

                        /* Entity ID Control Selector is MUTE */
                        USB_1_currentTD.wCount = 1u;
                        USB_1_currentTD.pData  = &USB_1_currentMute;
                        
                        requestHandled = USB_1_InitControlWrite();
                    }
                    else if (wValueHi == USB_1_VOLUME_CONTROL)
                    {
                        /* `#START VOLUME_CONTROL_SET_REQUEST` Place multi-channel handler here */

                        /* `#END` */

                    #ifdef USB_1_DISPATCH_AUDIO_CLASS_VOLUME_CONTROL_SET_REQUEST_CALLBACK
                        USB_1_DispatchAUDIOClass_VOLUME_CONTROL_SET_REQUEST_Callback();
                    #endif /* (USB_1_DISPATCH_AUDIO_CLASS_VOLUME_CONTROL_SET_REQUEST_CALLBACK) */

                        /* Entity ID Control Selector is VOLUME */
                        USB_1_currentTD.wCount = USB_1_VOLUME_LEN;
                        USB_1_currentTD.pData  = USB_1_currentVolume;
                        
                        requestHandled = USB_1_InitControlWrite();
                    }
                    else
                    {
                        /* `#START OTHER_SET_CUR_REQUESTS` Place other request handler here */

                        /* `#END` */

                    #ifdef USB_1_DISPATCH_AUDIO_CLASS_OTHER_SET_CUR_REQUESTS_CALLBACK
                        USB_1_DispatchAUDIOClass_OTHER_SET_CUR_REQUESTS_Callback();
                    #endif /* (USB_1_DISPATCH_AUDIO_CLASS_OTHER_SET_CUR_REQUESTS_CALLBACK) */
                    }
                #endif /*  USB_1_ENABLE_AUDIO_STREAMING */
                
                
                    /* `#START AUDIO_CONTROL_SEL_REQUESTS` Place other request handler here */

                    /* `#END` */
                    
                #ifdef USB_1_DISPATCH_AUDIO_CLASS_AUDIO_CONTROL_SEL_REQUESTS_CALLBACK
                    USB_1_DispatchAUDIOClass_AUDIO_CONTROL_SEL_REQUESTS_Callback();
                #endif /* (USB_1_DISPATCH_AUDIO_CLASS_AUDIO_CONTROL_SEL_REQUESTS_CALLBACK) */
                break;

                default:
                    /* Do not handle this request. */
                break;
            }
        }
        else
        {
            /* Do not handle other requests recipients. */
        }
    }

    return (requestHandled);
}
#endif /* (USER_SUPPLIED_AUDIO_HANDLER) */


/*******************************************************************************
* Additional user functions supporting AUDIO Requests
********************************************************************************/

/* `#START AUDIO_FUNCTIONS` Place any additional functions here */

/* `#END` */

#endif  /* (USB_1_ENABLE_AUDIO_CLASS) */


/* [] END OF FILE */
