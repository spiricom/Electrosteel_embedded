/*******************************************************************************
* File Name: UNUSED_PIN.h  
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

#if !defined(CY_PINS_UNUSED_PIN_ALIASES_H) /* Pins UNUSED_PIN_ALIASES_H */
#define CY_PINS_UNUSED_PIN_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define UNUSED_PIN_0			(UNUSED_PIN__0__PC)
#define UNUSED_PIN_0_INTR	((uint16)((uint16)0x0001u << UNUSED_PIN__0__SHIFT))

#define UNUSED_PIN_INTR_ALL	 ((uint16)(UNUSED_PIN_0_INTR))

#endif /* End Pins UNUSED_PIN_ALIASES_H */


/* [] END OF FILE */
