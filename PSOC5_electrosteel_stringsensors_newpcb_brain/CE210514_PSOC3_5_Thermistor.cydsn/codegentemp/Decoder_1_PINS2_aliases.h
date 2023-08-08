/*******************************************************************************
* File Name: Decoder_1_PINS2.h  
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

#if !defined(CY_PINS_Decoder_1_PINS2_ALIASES_H) /* Pins Decoder_1_PINS2_ALIASES_H */
#define CY_PINS_Decoder_1_PINS2_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Decoder_1_PINS2_0			(Decoder_1_PINS2__0__PC)
#define Decoder_1_PINS2_0_INTR	((uint16)((uint16)0x0001u << Decoder_1_PINS2__0__SHIFT))

#define Decoder_1_PINS2_1			(Decoder_1_PINS2__1__PC)
#define Decoder_1_PINS2_1_INTR	((uint16)((uint16)0x0001u << Decoder_1_PINS2__1__SHIFT))

#define Decoder_1_PINS2_INTR_ALL	 ((uint16)(Decoder_1_PINS2_0_INTR| Decoder_1_PINS2_1_INTR))
#define Decoder_1_PINS2_A			(Decoder_1_PINS2__A__PC)
#define Decoder_1_PINS2_A_INTR	((uint16)((uint16)0x0001u << Decoder_1_PINS2__0__SHIFT))

#define Decoder_1_PINS2_B			(Decoder_1_PINS2__B__PC)
#define Decoder_1_PINS2_B_INTR	((uint16)((uint16)0x0001u << Decoder_1_PINS2__1__SHIFT))

#endif /* End Pins Decoder_1_PINS2_ALIASES_H */


/* [] END OF FILE */
