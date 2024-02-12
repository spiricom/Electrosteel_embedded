/*******************************************************************************
* File Name: AMuxSeq_2.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the AMuxSeq.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUXSEQ_AMuxSeq_2_H)
#define CY_AMUXSEQ_AMuxSeq_2_H

#include "cyfitter.h"
#include "cyfitter_cfg.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))    
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif /* ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define AMuxSeq_2_MUX_SINGLE 1
#define AMuxSeq_2_MUX_DIFF   2
#define AMuxSeq_2_MUXTYPE    2


/***************************************
*        Function Prototypes
***************************************/

void AMuxSeq_2_Start(void);
void AMuxSeq_2_Init(void);
void AMuxSeq_2_Stop(void);
#if (AMuxSeq_2_MUXTYPE == AMuxSeq_2_MUX_DIFF)
void AMuxSeq_2_Next(void);
void AMuxSeq_2_DisconnectAll(void);
#else
/* The Next and DisconnectAll functions are declared in cyfitter_cfg.h. */
/* void AMuxSeq_2_Next(void); */
/* void AMuxSeq_2_DisconnectAll(void); */
#endif
int8 AMuxSeq_2_GetChannel(void);


/***************************************
*           Global Variables
***************************************/

extern uint8 AMuxSeq_2_initVar;


/***************************************
*         Parameter Constants
***************************************/
#define AMuxSeq_2_CHANNELS 2


#endif /* CY_AMUXSEQ_AMuxSeq_2_H */


/* [] END OF FILE */
