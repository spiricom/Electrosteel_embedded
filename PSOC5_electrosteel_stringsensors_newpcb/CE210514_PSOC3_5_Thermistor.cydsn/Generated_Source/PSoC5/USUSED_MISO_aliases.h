/*******************************************************************************
* File Name: USUSED_MISO.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_USUSED_MISO_ALIASES_H) /* Pins USUSED_MISO_ALIASES_H */
#define CY_PINS_USUSED_MISO_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define USUSED_MISO_0			(USUSED_MISO__0__PC)
#define USUSED_MISO_0_INTR	((uint16)((uint16)0x0001u << USUSED_MISO__0__SHIFT))

#define USUSED_MISO_INTR_ALL	 ((uint16)(USUSED_MISO_0_INTR))

#endif /* End Pins USUSED_MISO_ALIASES_H */


/* [] END OF FILE */
