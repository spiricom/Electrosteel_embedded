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

#define barBufferSize 8
#define touchBufferSize 4
#define REFERENCE_RESISTOR 32000


uint8_t stringCapSensorsOnOff[1];
uint8_t stringCapSensorsRaw[16];
uint8_t thresholdArray[12] = {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15};
uint8 barArray[barBufferSize];
uint8 touchArray[touchBufferSize];
int32_t linearPotValue32Bit[4];
uint8_t i = 0;
uint8_t counter = 0;

int32_t temper;
int previousButtons[11];
int octave = 0;
void scanLinearResistor(void);


CY_ISR(button_press_ISR) {     /* No need to clear any interrupt source; interrupt component should be      * configured for RISING_EDGE mode.      */     /* Read the debouncer status reg just to clear it, no need to check its      * contents in this application.      */  
 //FiltReg_Read(); 
    //
}

uint16_t ADC_values[12];
uint8_t currentResistor = 0;
uint8_t scanState = 0;
int32 iVtherm = 0;
int32 iVref = 0;
int32 iRes = 0;
int32 offset = 0;


int main(void)
{
    
	char printBuf[16]={'\0'};


	CYGlobalIntEnable; 
	ADC_1_Start();
	AMux_1_Start();


    SPIM_1_Start();
    SPIM_2_Start();
    //SPIS_1_Start();
    Opamp_1_Start();
    Opamp_2_Start();
    //Opamp_3_Start();
    //Opamp_4_Start();
    
    Opamp_1_Sleep();

   // VDAC8_1_Start();
   // VDAC8_2_Start();
    
    CapSense_Start();     
    
    CyDelay(1000);
    CapSense_InitializeAllBaselines();
    uint8_t myArrayCounter = 0;
    
    CapSense_ScanEnabledWidgets();  

    //select the high/low pins
    if (currentResistor == 0)
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
    AMux_1_FastSelect(currentResistor * 2);
    ADC_1_StartConvert();
    scanState = 0;
	for(;;)
    {
        CapSense_ClearSensors();
        

        scanLinearResistor();


        uint8_t byteCounter = 0;

        CapSense_UpdateEnabledBaselines();
        CapSense_ScanEnabledWidgets();  
        
        int isSensorOn1 = (CapSense_sensorRaw[0] - CapSense_sensorBaseline[0]) > thresholdArray[0];
        if (isSensorOn1)
        {
            LED_1_Write(1);
        }
        else
        {
            LED_1_Write(0);
        }

        counter = 0;
        
        for (i = 0; i < 2; i++)
        {
            barArray[counter++] = ((uint16_t) linearPotValue32Bit[i]) >> 8;
            barArray[counter++] = linearPotValue32Bit[i] & 0xff;
        }



        barArray[4] = 0;
        barArray[5] = 0;
        barArray[6] = 254;
        barArray[7] = 253;
        
        touchArray[0] = 0;
        touchArray[1] = 0;
        touchArray[2] = 254;
        touchArray[3] = 253;

        
        while(CapSense_IsBusy() != 0)  
        {
            ;//wait until scan is complete
        }  
        for (i = 0; i < 8; i++)
        {
           int isSensorOn = (CapSense_sensorRaw[i] - CapSense_sensorBaseline[i]) > thresholdArray[i];
            touchArray[0] |= (isSensorOn << i);
            barArray[4] |= (isSensorOn << i);

        }
        for (i = 8; i < 12; i++)
        {
           int isSensorOn = (CapSense_sensorRaw[i] - CapSense_sensorBaseline[i]) > thresholdArray[i];
            touchArray[1] |= (isSensorOn << (i - 8));
            barArray[5] |= (isSensorOn << (i - 8));
        }        
        
        //send data over SPI to Genera boards
         for (int i = 0; i < touchBufferSize; i++)
        {         

            SPIM_1_WriteTxData(touchArray[i]);

        }
        
        //send data over SPI to brain and synth boards
         for (int i = 0; i < barBufferSize; i++)
        {         

            SPIM_2_WriteTxData(barArray[i]);

        }

      
        
     }
}



void scanLinearResistor(void)
{  
        if (ADC_1_IsEndConversion(ADC_1_RETURN_STATUS))
        {
            if (scanState == 0)
            {
                iVtherm = ADC_1_GetResult32();
            	/* Get the offset voltage*/
                /*
        	    AMux_1_FastSelect(4);
                ADC_1_StartConvert();
                scanState = 2;
            }
            else if (scanState == 1)
            {
                offset = ADC_1_GetResult32();
                iVtherm =  iVtherm - offset;
    	*/
                AMux_1_FastSelect((currentResistor * 2) + 1);
                ADC_1_StartConvert();
                scanState = 2;
            }
            else if (scanState == 2)
            {
                iVref = ADC_1_GetResult32();
                iVref =  iVref - offset;
            
                //iRes = Thermistor_GetResistance(iVtherm, iVref); //check if more efficient than my version
                if ((iVref > 210000) && (iVtherm < 200000))
                {
                    iRes = 65535;
                }
                else
                
                {
                    float tempres = ((float)iVref / (float)iVtherm);
                    iRes = (int32)(tempres * REFERENCE_RESISTOR);
                }
                if (iRes > 65535)
                {
                    iRes = 65535;
                }
                linearPotValue32Bit[currentResistor] = iRes;
                currentResistor = !currentResistor;
                
                                //select the high/low pins
                if (currentResistor == 0)
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
                AMux_1_FastSelect(currentResistor * 2);
                ADC_1_StartConvert();
                scanState = 0;
            }
        }
}


/* [] END OF FILE */
