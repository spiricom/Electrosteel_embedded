/*******************************************************************************
* File Name: Decoder_1_isrDtr.h
* Version 1.71
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Decoder_1_isrDtr_H)
#define CY_ISR_Decoder_1_isrDtr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Decoder_1_isrDtr_Start(void);
void Decoder_1_isrDtr_StartEx(cyisraddress address);
void Decoder_1_isrDtr_Stop(void);

CY_ISR_PROTO(Decoder_1_isrDtr_Interrupt);

void Decoder_1_isrDtr_SetVector(cyisraddress address);
cyisraddress Decoder_1_isrDtr_GetVector(void);

void Decoder_1_isrDtr_SetPriority(uint8 priority);
uint8 Decoder_1_isrDtr_GetPriority(void);

void Decoder_1_isrDtr_Enable(void);
uint8 Decoder_1_isrDtr_GetState(void);
void Decoder_1_isrDtr_Disable(void);

void Decoder_1_isrDtr_SetPending(void);
void Decoder_1_isrDtr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Decoder_1_isrDtr ISR. */
#define Decoder_1_isrDtr_INTC_VECTOR            ((reg32 *) Decoder_1_isrDtr__INTC_VECT)

/* Address of the Decoder_1_isrDtr ISR priority. */
#define Decoder_1_isrDtr_INTC_PRIOR             ((reg8 *) Decoder_1_isrDtr__INTC_PRIOR_REG)

/* Priority of the Decoder_1_isrDtr interrupt. */
#define Decoder_1_isrDtr_INTC_PRIOR_NUMBER      Decoder_1_isrDtr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Decoder_1_isrDtr interrupt. */
#define Decoder_1_isrDtr_INTC_SET_EN            ((reg32 *) Decoder_1_isrDtr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Decoder_1_isrDtr interrupt. */
#define Decoder_1_isrDtr_INTC_CLR_EN            ((reg32 *) Decoder_1_isrDtr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Decoder_1_isrDtr interrupt state to pending. */
#define Decoder_1_isrDtr_INTC_SET_PD            ((reg32 *) Decoder_1_isrDtr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Decoder_1_isrDtr interrupt. */
#define Decoder_1_isrDtr_INTC_CLR_PD            ((reg32 *) Decoder_1_isrDtr__INTC_CLR_PD_REG)


#endif /* CY_ISR_Decoder_1_isrDtr_H */


/* [] END OF FILE */
