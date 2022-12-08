/***************************************************************************//**
* \file .h
* \version 3.20
*
* \brief
*  This file provides private function prototypes and constants for the 
*  USBFS component. It is not intended to be used in the user project.
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_USBFS_USB_1_pvt_H)
#define CY_USBFS_USB_1_pvt_H

#include "USB_1.h"
   
#ifdef USB_1_ENABLE_AUDIO_CLASS
    #include "USB_1_audio.h"
#endif /* USB_1_ENABLE_AUDIO_CLASS */

#ifdef USB_1_ENABLE_CDC_CLASS
    #include "USB_1_cdc.h"
#endif /* USB_1_ENABLE_CDC_CLASS */

#if (USB_1_ENABLE_MIDI_CLASS)
    #include "USB_1_midi.h"
#endif /* (USB_1_ENABLE_MIDI_CLASS) */

#if (USB_1_ENABLE_MSC_CLASS)
    #include "USB_1_msc.h"
#endif /* (USB_1_ENABLE_MSC_CLASS) */

#if (USB_1_EP_MANAGEMENT_DMA)
    #if (CY_PSOC4)
        #include <CyDMA.h>
    #else
        #include <CyDmac.h>
        #if ((USB_1_EP_MANAGEMENT_DMA_AUTO) && (USB_1_EP_DMA_AUTO_OPT == 0u))
            #include "USB_1_EP_DMA_Done_isr.h"
            #include "USB_1_EP8_DMA_Done_SR.h"
            #include "USB_1_EP17_DMA_Done_SR.h"
        #endif /* ((USB_1_EP_MANAGEMENT_DMA_AUTO) && (USB_1_EP_DMA_AUTO_OPT == 0u)) */
    #endif /* (CY_PSOC4) */
#endif /* (USB_1_EP_MANAGEMENT_DMA) */

#if (USB_1_DMA1_ACTIVE)
    #include "USB_1_ep1_dma.h"
    #define USB_1_EP1_DMA_CH     (USB_1_ep1_dma_CHANNEL)
#endif /* (USB_1_DMA1_ACTIVE) */

#if (USB_1_DMA2_ACTIVE)
    #include "USB_1_ep2_dma.h"
    #define USB_1_EP2_DMA_CH     (USB_1_ep2_dma_CHANNEL)
#endif /* (USB_1_DMA2_ACTIVE) */

#if (USB_1_DMA3_ACTIVE)
    #include "USB_1_ep3_dma.h"
    #define USB_1_EP3_DMA_CH     (USB_1_ep3_dma_CHANNEL)
#endif /* (USB_1_DMA3_ACTIVE) */

#if (USB_1_DMA4_ACTIVE)
    #include "USB_1_ep4_dma.h"
    #define USB_1_EP4_DMA_CH     (USB_1_ep4_dma_CHANNEL)
#endif /* (USB_1_DMA4_ACTIVE) */

#if (USB_1_DMA5_ACTIVE)
    #include "USB_1_ep5_dma.h"
    #define USB_1_EP5_DMA_CH     (USB_1_ep5_dma_CHANNEL)
#endif /* (USB_1_DMA5_ACTIVE) */

#if (USB_1_DMA6_ACTIVE)
    #include "USB_1_ep6_dma.h"
    #define USB_1_EP6_DMA_CH     (USB_1_ep6_dma_CHANNEL)
#endif /* (USB_1_DMA6_ACTIVE) */

#if (USB_1_DMA7_ACTIVE)
    #include "USB_1_ep7_dma.h"
    #define USB_1_EP7_DMA_CH     (USB_1_ep7_dma_CHANNEL)
#endif /* (USB_1_DMA7_ACTIVE) */

#if (USB_1_DMA8_ACTIVE)
    #include "USB_1_ep8_dma.h"
    #define USB_1_EP8_DMA_CH     (USB_1_ep8_dma_CHANNEL)
#endif /* (USB_1_DMA8_ACTIVE) */


/***************************************
*     Private Variables
***************************************/

/* Generated external references for descriptors. */
extern const uint8 CYCODE USB_1_DEVICE0_DESCR[18u];
extern const uint8 CYCODE USB_1_DEVICE0_CONFIGURATION0_DESCR[101u];
extern const T_USB_1_EP_SETTINGS_BLOCK CYCODE USB_1_DEVICE0_CONFIGURATION0_EP_SETTINGS_TABLE[2u];
extern const uint8 CYCODE USB_1_DEVICE0_CONFIGURATION0_INTERFACE_CLASS[2u];
extern const T_USB_1_LUT CYCODE USB_1_DEVICE0_CONFIGURATION0_TABLE[5u];
extern const T_USB_1_LUT CYCODE USB_1_DEVICE0_TABLE[3u];
extern const T_USB_1_LUT CYCODE USB_1_TABLE[1u];
extern const uint8 CYCODE USB_1_SN_STRING_DESCRIPTOR[2];
extern const uint8 CYCODE USB_1_STRING_DESCRIPTORS[219u];


extern const uint8 CYCODE USB_1_MSOS_DESCRIPTOR[USB_1_MSOS_DESCRIPTOR_LENGTH];
extern const uint8 CYCODE USB_1_MSOS_CONFIGURATION_DESCR[USB_1_MSOS_CONF_DESCR_LENGTH];
#if defined(USB_1_ENABLE_IDSN_STRING)
    extern uint8 USB_1_idSerialNumberStringDescriptor[USB_1_IDSN_DESCR_LENGTH];
#endif /* (USB_1_ENABLE_IDSN_STRING) */

extern volatile uint8 USB_1_interfaceNumber;
extern volatile uint8 USB_1_interfaceSetting[USB_1_MAX_INTERFACES_NUMBER];
extern volatile uint8 USB_1_interfaceSettingLast[USB_1_MAX_INTERFACES_NUMBER];
extern volatile uint8 USB_1_deviceAddress;
extern volatile uint8 USB_1_interfaceStatus[USB_1_MAX_INTERFACES_NUMBER];
extern const uint8 CYCODE *USB_1_interfaceClass;

extern volatile T_USB_1_EP_CTL_BLOCK USB_1_EP[USB_1_MAX_EP];
extern volatile T_USB_1_TD USB_1_currentTD;

#if (USB_1_EP_MANAGEMENT_DMA)
    #if (CY_PSOC4)
        extern const uint8 USB_1_DmaChan[USB_1_MAX_EP];
    #else
        extern uint8 USB_1_DmaChan[USB_1_MAX_EP];
        extern uint8 USB_1_DmaTd  [USB_1_MAX_EP];
    #endif /* (CY_PSOC4) */
#endif /* (USB_1_EP_MANAGEMENT_DMA) */

#if (USB_1_EP_MANAGEMENT_DMA_AUTO)
#if (CY_PSOC4)
    extern uint8  USB_1_DmaEpBurstCnt   [USB_1_MAX_EP];
    extern uint8  USB_1_DmaEpLastBurstEl[USB_1_MAX_EP];

    extern uint8  USB_1_DmaEpBurstCntBackup  [USB_1_MAX_EP];
    extern uint32 USB_1_DmaEpBufferAddrBackup[USB_1_MAX_EP];
    
    extern const uint8 USB_1_DmaReqOut     [USB_1_MAX_EP];    
    extern const uint8 USB_1_DmaBurstEndOut[USB_1_MAX_EP];
#else
    #if (USB_1_EP_DMA_AUTO_OPT == 0u)
        extern uint8 USB_1_DmaNextTd[USB_1_MAX_EP];
        extern volatile uint16 USB_1_inLength [USB_1_MAX_EP];
        extern volatile uint8  USB_1_inBufFull[USB_1_MAX_EP];
        extern const uint8 USB_1_epX_TD_TERMOUT_EN[USB_1_MAX_EP];
        extern const uint8 *USB_1_inDataPointer[USB_1_MAX_EP];
    #endif /* (USB_1_EP_DMA_AUTO_OPT == 0u) */
#endif /* CY_PSOC4 */
#endif /* (USB_1_EP_MANAGEMENT_DMA_AUTO) */

extern volatile uint8 USB_1_ep0Toggle;
extern volatile uint8 USB_1_lastPacketSize;
extern volatile uint8 USB_1_ep0Mode;
extern volatile uint8 USB_1_ep0Count;
extern volatile uint16 USB_1_transferByteCount;


/***************************************
*     Private Function Prototypes
***************************************/
void  USB_1_ReInitComponent(void)            ;
void  USB_1_HandleSetup(void)                ;
void  USB_1_HandleIN(void)                   ;
void  USB_1_HandleOUT(void)                  ;
void  USB_1_LoadEP0(void)                    ;
uint8 USB_1_InitControlRead(void)            ;
uint8 USB_1_InitControlWrite(void)           ;
void  USB_1_ControlReadDataStage(void)       ;
void  USB_1_ControlReadStatusStage(void)     ;
void  USB_1_ControlReadPrematureStatus(void) ;
uint8 USB_1_InitControlWrite(void)           ;
uint8 USB_1_InitZeroLengthControlTransfer(void) ;
void  USB_1_ControlWriteDataStage(void)      ;
void  USB_1_ControlWriteStatusStage(void)    ;
void  USB_1_ControlWritePrematureStatus(void);
uint8 USB_1_InitNoDataControlTransfer(void)  ;
void  USB_1_NoDataControlStatusStage(void)   ;
void  USB_1_InitializeStatusBlock(void)      ;
void  USB_1_UpdateStatusBlock(uint8 completionCode) ;
uint8 USB_1_DispatchClassRqst(void)          ;

void USB_1_Config(uint8 clearAltSetting) ;
void USB_1_ConfigAltChanged(void)        ;
void USB_1_ConfigReg(void)               ;
void USB_1_EpStateInit(void)             ;


const T_USB_1_LUT CYCODE *USB_1_GetConfigTablePtr(uint8 confIndex);
const T_USB_1_LUT CYCODE *USB_1_GetDeviceTablePtr(void)           ;
#if (USB_1_BOS_ENABLE)
    const T_USB_1_LUT CYCODE *USB_1_GetBOSPtr(void)               ;
#endif /* (USB_1_BOS_ENABLE) */
const uint8 CYCODE *USB_1_GetInterfaceClassTablePtr(void)                    ;
uint8 USB_1_ClearEndpointHalt(void)                                          ;
uint8 USB_1_SetEndpointHalt(void)                                            ;
uint8 USB_1_ValidateAlternateSetting(void)                                   ;

void USB_1_SaveConfig(void)      ;
void USB_1_RestoreConfig(void)   ;

#if (CY_PSOC3 || CY_PSOC5LP)
    #if (USB_1_EP_MANAGEMENT_DMA_AUTO && (USB_1_EP_DMA_AUTO_OPT == 0u))
        void USB_1_LoadNextInEP(uint8 epNumber, uint8 mode)  ;
    #endif /* (USB_1_EP_MANAGEMENT_DMA_AUTO && (USB_1_EP_DMA_AUTO_OPT == 0u)) */
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

#if defined(USB_1_ENABLE_IDSN_STRING)
    void USB_1_ReadDieID(uint8 descr[])  ;
#endif /* USB_1_ENABLE_IDSN_STRING */

#if defined(USB_1_ENABLE_HID_CLASS)
    uint8 USB_1_DispatchHIDClassRqst(void) ;
#endif /* (USB_1_ENABLE_HID_CLASS) */

#if defined(USB_1_ENABLE_AUDIO_CLASS)
    uint8 USB_1_DispatchAUDIOClassRqst(void) ;
#endif /* (USB_1_ENABLE_AUDIO_CLASS) */

#if defined(USB_1_ENABLE_CDC_CLASS)
    uint8 USB_1_DispatchCDCClassRqst(void) ;
#endif /* (USB_1_ENABLE_CDC_CLASS) */

#if (USB_1_ENABLE_MSC_CLASS)
    #if (USB_1_HANDLE_MSC_REQUESTS)
        uint8 USB_1_DispatchMSCClassRqst(void) ;
    #endif /* (USB_1_HANDLE_MSC_REQUESTS) */
#endif /* (USB_1_ENABLE_MSC_CLASS */

CY_ISR_PROTO(USB_1_EP_0_ISR);
CY_ISR_PROTO(USB_1_BUS_RESET_ISR);

#if (USB_1_SOF_ISR_ACTIVE)
    CY_ISR_PROTO(USB_1_SOF_ISR);
#endif /* (USB_1_SOF_ISR_ACTIVE) */

#if (USB_1_EP1_ISR_ACTIVE)
    CY_ISR_PROTO(USB_1_EP_1_ISR);
#endif /* (USB_1_EP1_ISR_ACTIVE) */

#if (USB_1_EP2_ISR_ACTIVE)
    CY_ISR_PROTO(USB_1_EP_2_ISR);
#endif /* (USB_1_EP2_ISR_ACTIVE) */

#if (USB_1_EP3_ISR_ACTIVE)
    CY_ISR_PROTO(USB_1_EP_3_ISR);
#endif /* (USB_1_EP3_ISR_ACTIVE) */

#if (USB_1_EP4_ISR_ACTIVE)
    CY_ISR_PROTO(USB_1_EP_4_ISR);
#endif /* (USB_1_EP4_ISR_ACTIVE) */

#if (USB_1_EP5_ISR_ACTIVE)
    CY_ISR_PROTO(USB_1_EP_5_ISR);
#endif /* (USB_1_EP5_ISR_ACTIVE) */

#if (USB_1_EP6_ISR_ACTIVE)
    CY_ISR_PROTO(USB_1_EP_6_ISR);
#endif /* (USB_1_EP6_ISR_ACTIVE) */

#if (USB_1_EP7_ISR_ACTIVE)
    CY_ISR_PROTO(USB_1_EP_7_ISR);
#endif /* (USB_1_EP7_ISR_ACTIVE) */

#if (USB_1_EP8_ISR_ACTIVE)
    CY_ISR_PROTO(USB_1_EP_8_ISR);
#endif /* (USB_1_EP8_ISR_ACTIVE) */

#if (USB_1_EP_MANAGEMENT_DMA)
    CY_ISR_PROTO(USB_1_ARB_ISR);
#endif /* (USB_1_EP_MANAGEMENT_DMA) */

#if (USB_1_DP_ISR_ACTIVE)
    CY_ISR_PROTO(USB_1_DP_ISR);
#endif /* (USB_1_DP_ISR_ACTIVE) */

#if (CY_PSOC4)
    CY_ISR_PROTO(USB_1_INTR_HI_ISR);
    CY_ISR_PROTO(USB_1_INTR_MED_ISR);
    CY_ISR_PROTO(USB_1_INTR_LO_ISR);
    #if (USB_1_LPM_ACTIVE)
        CY_ISR_PROTO(USB_1_LPM_ISR);
    #endif /* (USB_1_LPM_ACTIVE) */
#endif /* (CY_PSOC4) */

#if (USB_1_EP_MANAGEMENT_DMA_AUTO)
#if (CY_PSOC4)
    #if (USB_1_DMA1_ACTIVE)
        void USB_1_EP1_DMA_DONE_ISR(void);
    #endif /* (USB_1_DMA1_ACTIVE) */

    #if (USB_1_DMA2_ACTIVE)
        void USB_1_EP2_DMA_DONE_ISR(void);
    #endif /* (USB_1_DMA2_ACTIVE) */

    #if (USB_1_DMA3_ACTIVE)
        void USB_1_EP3_DMA_DONE_ISR(void);
    #endif /* (USB_1_DMA3_ACTIVE) */

    #if (USB_1_DMA4_ACTIVE)
        void USB_1_EP4_DMA_DONE_ISR(void);
    #endif /* (USB_1_DMA4_ACTIVE) */

    #if (USB_1_DMA5_ACTIVE)
        void USB_1_EP5_DMA_DONE_ISR(void);
    #endif /* (USB_1_DMA5_ACTIVE) */

    #if (USB_1_DMA6_ACTIVE)
        void USB_1_EP6_DMA_DONE_ISR(void);
    #endif /* (USB_1_DMA6_ACTIVE) */

    #if (USB_1_DMA7_ACTIVE)
        void USB_1_EP7_DMA_DONE_ISR(void);
    #endif /* (USB_1_DMA7_ACTIVE) */

    #if (USB_1_DMA8_ACTIVE)
        void USB_1_EP8_DMA_DONE_ISR(void);
    #endif /* (USB_1_DMA8_ACTIVE) */

#else
    #if (USB_1_EP_DMA_AUTO_OPT == 0u)
        CY_ISR_PROTO(USB_1_EP_DMA_DONE_ISR);
    #endif /* (USB_1_EP_DMA_AUTO_OPT == 0u) */
#endif /* (CY_PSOC4) */
#endif /* (USB_1_EP_MANAGEMENT_DMA_AUTO) */


/***************************************
*         Request Handlers
***************************************/

uint8 USB_1_HandleStandardRqst(void) ;
uint8 USB_1_DispatchClassRqst(void)  ;
uint8 USB_1_HandleVendorRqst(void)   ;


/***************************************
*    HID Internal references
***************************************/

#if defined(USB_1_ENABLE_HID_CLASS)
    void USB_1_FindReport(void)            ;
    void USB_1_FindReportDescriptor(void)  ;
    void USB_1_FindHidClassDecriptor(void) ;
#endif /* USB_1_ENABLE_HID_CLASS */


/***************************************
*    MIDI Internal references
***************************************/

#if defined(USB_1_ENABLE_MIDI_STREAMING)
    void USB_1_MIDI_IN_EP_Service(void)  ;
#endif /* (USB_1_ENABLE_MIDI_STREAMING) */


/***************************************
*    CDC Internal references
***************************************/

#if defined(USB_1_ENABLE_CDC_CLASS)

    typedef struct
    {
        uint8  bRequestType;
        uint8  bNotification;
        uint8  wValue;
        uint8  wValueMSB;
        uint8  wIndex;
        uint8  wIndexMSB;
        uint8  wLength;
        uint8  wLengthMSB;
        uint8  wSerialState;
        uint8  wSerialStateMSB;
    } t_USB_1_cdc_notification;

    uint8 USB_1_GetInterfaceComPort(uint8 interface) ;
    uint8 USB_1_Cdc_EpInit( const T_USB_1_EP_SETTINGS_BLOCK CYCODE *pEP, uint8 epNum, uint8 cdcComNums) ;

    extern volatile uint8  USB_1_cdc_dataInEpList[USB_1_MAX_MULTI_COM_NUM];
    extern volatile uint8  USB_1_cdc_dataOutEpList[USB_1_MAX_MULTI_COM_NUM];
    extern volatile uint8  USB_1_cdc_commInEpList[USB_1_MAX_MULTI_COM_NUM];
#endif /* (USB_1_ENABLE_CDC_CLASS) */


#endif /* CY_USBFS_USB_1_pvt_H */


/* [] END OF FILE */
