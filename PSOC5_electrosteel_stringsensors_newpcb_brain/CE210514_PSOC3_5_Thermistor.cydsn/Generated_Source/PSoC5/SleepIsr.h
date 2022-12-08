/*******************************************************************************
* File Name: SleepIsr.h
* Version 1.70
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
#if !defined(CY_ISR_SleepIsr_H)
#define CY_ISR_SleepIsr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void SleepIsr_Start(void);
void SleepIsr_StartEx(cyisraddress address);
void SleepIsr_Stop(void);

CY_ISR_PROTO(SleepIsr_Interrupt);

void SleepIsr_SetVector(cyisraddress address);
cyisraddress SleepIsr_GetVector(void);

void SleepIsr_SetPriority(uint8 priority);
uint8 SleepIsr_GetPriority(void);

void SleepIsr_Enable(void);
uint8 SleepIsr_GetState(void);
void SleepIsr_Disable(void);

void SleepIsr_SetPending(void);
void SleepIsr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the SleepIsr ISR. */
#define SleepIsr_INTC_VECTOR            ((reg32 *) SleepIsr__INTC_VECT)

/* Address of the SleepIsr ISR priority. */
#define SleepIsr_INTC_PRIOR             ((reg8 *) SleepIsr__INTC_PRIOR_REG)

/* Priority of the SleepIsr interrupt. */
#define SleepIsr_INTC_PRIOR_NUMBER      SleepIsr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable SleepIsr interrupt. */
#define SleepIsr_INTC_SET_EN            ((reg32 *) SleepIsr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the SleepIsr interrupt. */
#define SleepIsr_INTC_CLR_EN            ((reg32 *) SleepIsr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the SleepIsr interrupt state to pending. */
#define SleepIsr_INTC_SET_PD            ((reg32 *) SleepIsr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the SleepIsr interrupt. */
#define SleepIsr_INTC_CLR_PD            ((reg32 *) SleepIsr__INTC_CLR_PD_REG)


#endif /* CY_ISR_SleepIsr_H */


/* [] END OF FILE */
