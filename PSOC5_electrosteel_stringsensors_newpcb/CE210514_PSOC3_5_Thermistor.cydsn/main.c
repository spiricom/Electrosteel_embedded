/*****************************************************************************
* File Name: main.c
*
* Version: 3.0
*
* Description:
*   
* 
* Note:
* 	The main project includes the ADC and other components required for the
*   temperature measurement. The Thermistor component is a complete firmware component
*   as decribed in the component datahseet and application note
******************************************************************************
* Copyright (C) 2015, Cypress Semiconductor Corporation.
******************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*****************************************************************************/
#include <device.h>
#include "removeOffsetNoise.h"
#include "measurement.h"
#include <stdio.h>

#define myBufferSize 32
#define REFERENCE_RESISTOR 20000


uint8_t stringCapSensorsOnOff[1];
uint8_t stringCapSensorsRaw[16];
uint8_t thresholdArray[10] = {15, 15, 15, 15, 15, 15, 15, 15, 15, 15};
uint8 myArray[myBufferSize];
int32_t linearPotValue32Bit[4];
uint8_t i = 0;
uint8_t counter = 0;
uint8_t returnedData[myBufferSize];
int32_t temper;
int previousButtons[11];
int octave = 0;
void scanLinearResistor(uint8_t channel);


CY_ISR(button_press_ISR) {     /* No need to clear any interrupt source; interrupt component should be      * configured for RISING_EDGE mode.      */     /* Read the debouncer status reg just to clear it, no need to check its      * contents in this application.      */  
 //FiltReg_Read(); 
    //
}

uint16_t ADC_values[12];

int main(void)
{
    
	char printBuf[16]={'\0'};


	CYGlobalIntEnable; 
	ADC_1_Start();
	AMux_1_Start();


    SPIM_1_Start();
    SPIM_1_Start();
    Opamp_1_Start();
    Opamp_2_Start();
    Opamp_1_Sleep();

   // VDAC8_1_Start();
   // VDAC8_2_Start();
    
    CapSense_Start();     
    
    CyDelay(500);
    CapSense_InitializeAllBaselines();
    uint8_t myArrayCounter = 0;
    
    CapSense_ScanEnabledWidgets();  


	for(;;)
    {
        CapSense_ClearSensors();
        
        for (i = 0; i < 2; i++)
        {
           scanLinearResistor(i);
        }

        uint8_t byteCounter = 0;

        CapSense_UpdateEnabledBaselines();
        CapSense_ScanEnabledWidgets();  
        
        int isSensorOn1 = (CapSense_sensorRaw[0] - CapSense_sensorBaseline[0]) > thresholdArray[0];
        if (isSensorOn1)
        {
            //LED_1_Write(1);
        }
        else
        {
            //LED_1_Write(0);
        }

        counter = 0;
        
        for (i = 0; i < 2; i++)
        {
            myArray[counter++] = ((uint16_t) linearPotValue32Bit[i]) >> 8;
            myArray[counter++] = linearPotValue32Bit[i] & 0xff;
        }



        
        myArray[4] = 0;
        myArray[5] = 0;
        //int octButtons = Status_Reg_1_Read();
        //int currentButtons[11];
        
        //for (i = 0; i < 4; i++)
        //{
           //currentButtons[i] = ((octButtons >> i) & 1);
           // if ((previousButtons[i] == 1) &&  (currentButtons[i] == 0))
            //{
           //     octave = i;
            //}
          //  previousButtons[i] = currentButtons[i];
        //}
        //int fretButtons = Status_Reg_2_Read();
        

        

        
        
        while(CapSense_IsBusy() != 0)  
        {
            ;//wait until scan is complete
        }  
        for (i = 0; i < 8; i++)
        {
           int isSensorOn = (CapSense_sensorRaw[i] - CapSense_sensorBaseline[i]) > thresholdArray[i];
            myArray[4] |= (isSensorOn << i);
        }
        for (i = 8; i < 10; i++)
        {
           int isSensorOn = (CapSense_sensorRaw[i] - CapSense_sensorBaseline[i]) > thresholdArray[i];
            myArray[5] |= (isSensorOn << (i - 8));
        }
        
        //send data over SPI to Genera boards
         for (int i = 0; i < myBufferSize; i++)
        {         

            SPIM_1_WriteTxData(myArray[i]);
            /*
            if ((SPIM_1_RX_STATUS_REG & SPIM_1_STS_RX_FIFO_NOT_EMPTY))
            {
                returnedData[i] = CY_GET_REG8(SPIM_1_RXDATA_PTR);
            }
            */
        }
        
        /*
        //fill end of array with data from Genera 1 to send to Genera 2 
        for (int i = 0; i < 7; i++)
        {
            myArray[i + 9] = returnedData[i];
        }
        */
        //send and receive data over SPI from Genera 2
        //for (int i = 0; i < myBufferSize; i++)
        //{    

            //SPIS_1_WriteTxData(myArray[i]);
            //if ((SPIM_2_RX_STATUS_REG & SPIM_2_STS_RX_FIFO_NOT_EMPTY))
            //{
           //     returnedData[i] = CY_GET_REG8(SPIM_2_RXDATA_PTR);
           // }
        //}
        /*
        //fill end of array with data from Genera 2 to send to Genera 1 
        for (int i = 0; i < 7; i++)
        {
            myArray[i + 9] = returnedData[i];
        }
        */
        
        /*
        if ((EZI2C_GetActivity() & EZI2C_STATUS_BUSY) == 0)
        {
           for (uint8_t i = 0; i < 16; i++)
            {
                myArray[i] = stringCapSensorsRaw[i];
            }
            myArray[16] = CapSense_sensorOnMask[0];
            
            counter = 17;
            for (i = 0; i < 4; i++)
            {
                myArray[counter++] = ((uint16_t) linearPotValue32Bit[i]) >> 8;
                myArray[counter++] = linearPotValue32Bit[i] & 0xff;
            }
        }
        */
        
     }
}

void scanLinearResistor(uint8_t channel)
{  
        int32 iVtherm = 0;
        int32 iVref = 0;
        int32 iRes = 0;
        int32 offset = 0;
        
        //select the high/low pins
        if (channel == 0)
        {
            Opamp_2_Sleep();
            Opamp_1_Wakeup();
        }
        else
        {   
            Opamp_1_Sleep();
            Opamp_2_Wakeup();
        }
    
        //select the wiper pins
        AMux_1_FastSelect(channel * 2);
        ADC_1_StartConvert();
        ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
        iVtherm = ADC_1_GetResult32();
        
        	/* Get the offset voltage*/
	    AMux_1_FastSelect(4);
        ADC_1_StartConvert();
        ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
        offset = ADC_1_GetResult32();
        
        iVtherm =  iVtherm - offset;
	
        AMux_1_FastSelect((channel * 2) + 1);
        ADC_1_StartConvert();
        ADC_1_IsEndConversion(ADC_1_WAIT_FOR_RESULT);
        iVref = ADC_1_GetResult32();
        
        iVref =  iVref - offset;
        
        //iRes = Thermistor_GetResistance(iVtherm, iVref); //check if more efficient than my version
        if ((iVref > 10000) && (iVtherm < 100))
        {
            iRes = 65535;
        }
        else
        
        {
            iRes = (int32)(((float)iVref / iVtherm) * REFERENCE_RESISTOR);
        }
        
        linearPotValue32Bit[channel] = iRes;
}


/* [] END OF FILE */
