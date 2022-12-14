/*******************************************************************************
* File Name: USB_1_Vbus_ps.h  
* Version 1.90
*
* Description:
*  This file containts Status Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_STATUS_REG_USB_1_Vbus_ps_H) /* CY_STATUS_REG_USB_1_Vbus_ps_H */
#define CY_STATUS_REG_USB_1_Vbus_ps_H

#include "cyfitter.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))
    #include "cytypes.h"
    #include "CyLib.h"
#else
    #include "syslib/cy_syslib.h"
#endif

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 statusState;

} USB_1_Vbus_ps_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8 USB_1_Vbus_ps_Read(void) ;
void USB_1_Vbus_ps_InterruptEnable(void) ;
void USB_1_Vbus_ps_InterruptDisable(void) ;
void USB_1_Vbus_ps_WriteMask(uint8 mask) ;
uint8 USB_1_Vbus_ps_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define USB_1_Vbus_ps_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define USB_1_Vbus_ps_INPUTS              1


/***************************************
*             Registers
***************************************/

/* Status Register */
#define USB_1_Vbus_ps_Status             (* (reg8 *) USB_1_Vbus_ps_sts_sts_reg__STATUS_REG )
#define USB_1_Vbus_ps_Status_PTR         (  (reg8 *) USB_1_Vbus_ps_sts_sts_reg__STATUS_REG )
#define USB_1_Vbus_ps_Status_Mask        (* (reg8 *) USB_1_Vbus_ps_sts_sts_reg__MASK_REG )
#define USB_1_Vbus_ps_Status_Aux_Ctrl    (* (reg8 *) USB_1_Vbus_ps_sts_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_USB_1_Vbus_ps_H */


/* [] END OF FILE */
