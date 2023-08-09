/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "CyFlash.h"
#include "Bootloader.h"
uint8_t myData[300]; //flash row plus ecc row since ecc is disabled (can be used as normal flash)
uint8_t sendArray[32];
uint8_t receiveArray[32];
uint8_t receivePosition = 0;
uint8_t computedChecksumByte = 0;
uint8_t receivedChecksumByte = 0;

uint16_t dataPosition = 0;
uint16_t outputDataPosition = 0;
uint16_t rowNumber = 0;
uint8_t arrayNumber = 0;
uint16_t rowSize = 0;
uint8_t ackCode = 0;
uint8_t eccflash[ CYDEV_FLS_ROW_SIZE + CYDEV_ECC_ROW_SIZE];
uint8_t LEDstate = 0;
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    //CyDelay(15000);
    //if we are here from a hard power reset, jump to bootloadable firmware
    uint8_t runType = Bootloader_GET_RUN_TYPE;
    if (runType != Bootloader_SCHEDULE_BTLDR)
    {
        /* Schedule Bootloadable to start after a reset */
        Bootloader_SET_RUN_TYPE(Bootloader_SCHEDULE_BTLDB);
        CySoftwareReset();
    }
    else
    {
        //needs user-supplied memory allocation to handle flash writes
        CySetFlashEEBuffer(eccflash); 
        SPIM_1_Start();
       // Bootloader_InitCallback(User_Callback_Function);
        /* Place your initialization/startup code here (e.g. MyInst_Start()) */
        for (int i = 0; i < 30; i++)
        {
            sendArray[i] = 55;
        }
        sendArray[30] = 254;
        sendArray[31] = 253;
        LED2_Write(0);
        LED3_Write(0);
        LED4_Write(0);
        LED1_Write(0);
        RedLED_Write(0);
        RedLED2_Write(0);
        GreenLED_Write(0);
        GreenLED2_Write(0);
        //CyFlash_Start(); 
        while(1)
        {
            //send out some nonsense with the magic bytes at the end
            SPIM_1_PutArray(sendArray, 32);
            while(!(SPIM_1_ReadTxStatus() & SPIM_1_STS_SPI_DONE));
            
            while(SPIM_1_GetRxBufferSize())
            {
                receiveArray[receivePosition] = SPIM_1_ReadRxData();
                receivePosition = (receivePosition + 1) & 31;
                
            }
            SPIM_1_ClearRxBuffer();
            //collect 30-byte packets over SPI and shove them into myData
            if ((receiveArray[0] == 251) && (receiveArray[31] == 254))
            {
                
               
                for (int i = 0; i < 30; i++)
                {
                    if (dataPosition == 0) 
                    {
                        arrayNumber = receiveArray[i+1];   
                        computedChecksumByte += receiveArray[i+1];
                    }
                    else if (dataPosition == 1)
                    {   
                        rowNumber = receiveArray[i+1]<<8;
                        computedChecksumByte += receiveArray[i+1];
                    }
                    else if (dataPosition == 2)
                    {   
                        rowNumber += receiveArray[i+1];
                        computedChecksumByte += receiveArray[i+1];
                    }
                    else if (dataPosition == 3)
                    {   
                        rowSize = receiveArray[i+1]<<8;
                        computedChecksumByte += receiveArray[i+1];
                    }
                    else if (dataPosition == 4)
                    {   
                        rowSize += receiveArray[i+1];
                        computedChecksumByte += receiveArray[i+1];
                    }
                    else if (dataPosition == 293)
                    {
                        receivedChecksumByte = receiveArray[i+1];
                    }
                    else
                    {
                        myData[outputDataPosition] = receiveArray[i+1];
                        computedChecksumByte += receiveArray[i+1];
                        outputDataPosition++;
                    }
                    dataPosition++;
                    //when packet length reaches 288 (or dataposition reaches 295 since it includes the array
                    //and row number, size, and checksum too), write the next row if the checksum checks out
                    if (dataPosition > 293)
                    {
                        outputDataPosition = 0;
                        dataPosition = 0;
                        
                        //2s-complement of checksum
                        computedChecksumByte = ( uint8 )1u + ( uint8 )(~computedChecksumByte);
                        
                        if (computedChecksumByte == receivedChecksumByte)
                        {
                            ackCode = CyWriteRowFull(arrayNumber, rowNumber, myData, 288);
                        }
                        else
                        {
                            //checksum failed - quit bootloader, requires power cycling to reset
                            LED2_Write(0);
                            LED3_Write(0);
                            LED4_Write(0);
                            LED1_Write(0);
                            RedLED_Write(1);
                            RedLED2_Write(1);
                            GreenLED_Write(0);
                            GreenLED2_Write(0);
                            Bootloader_SET_RUN_TYPE(Bootloader_SCHEDULE_BTLDB);
                            while(1)
                            {
                                ;
                            }
                        }
                            
                        CyFlushCache();
                        computedChecksumByte = 0;
                        LEDstate = (rowNumber >> 3) & 1;
                    }
                }
            }
            
            else if ((receiveArray[0] == 249)&& (receiveArray[31] == 254))
            {
                //this is the signal that the sending is done. Let's restart the brain!
                Bootloader_SET_RUN_TYPE(Bootloader_SCHEDULE_BTLDB);
                SPIM_1_Stop();
                CySoftwareReset();
            }
            
            //just for checking things, write the data we received back to the host. Makes it easier to see on a logic analyzer that things are working
            for (int i = 1; i < 30; i++)
            {
                sendArray[i] = receiveArray[i];
            }

            if (arrayNumber == 0)
            {
                LED1_Write(1);
                LED2_Write(0);
                LED3_Write(0);
                LED4_Write(0);
            }
            else if (arrayNumber == 1)
            {
                LED1_Write(0);
                 LED2_Write(1);
                LED3_Write(0);
                LED4_Write(0);
            }
            else if (arrayNumber == 2)
            {
                LED1_Write(0);
                 LED2_Write(0);
                LED3_Write(1);
                LED4_Write(0);
            }
            else if (arrayNumber == 3)
            {
                LED1_Write(0);
                 LED2_Write(0);
                LED3_Write(0);
                LED4_Write(1);
            }
            
            
            if (LEDstate == 0)
            {
                GreenLED_Write(1);
                GreenLED2_Write(0);
                
            }
            else if (LEDstate == 1)
            {
               GreenLED_Write(0);
                GreenLED2_Write(1);
                
            }
        }
    }
}

/* [] END OF FILE */
