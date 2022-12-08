/*main.c
*****************************************************************************/
#include <device.h>
#include <stdio.h>
#include <math.h>
#include "oled.h"
#include "main.h"

#define myBufferSize 74


volatile uint8 usbActivityCounter = 0u;
uint8 midiMsg[4];
uint8_t currentVBUS = 0;
uint8_t prevVBUS = 0;
volatile uint8_t USB_active = 0;
volatile uint8_t USB_check_flag = 0;

uint8 myArray[myBufferSize];
uint8 myInputArray[2];
int32_t linearPotValue32Bit[4];
uint8_t i = 0;
uint8_t counter = 0;
uint8_t returnedData[myBufferSize];
int32_t temper;
int previousButtons[11];
int octave = 1;
uint16_t angle[10];
uint16_t prevAngle[10];

uint16_t ADC_values[4];
uint16_t rawAngle = 0;
uint16_t midiSent = 0;
uint16_t midiOverflow = 0;

void checkUSB_Vbus(void);
void sendMIDIAllNotesOff(void);
void sendMIDIPitchBend(int val, int channel);
void firstCheckUSB_Vbus(void);
void restartSystemCheck(void);
void sendMIDINoteOn(int MIDInoteNum, int velocity, int channel);
void sendMIDIControlChange(int CCnum, int CCval, int channel);
CY_ISR_PROTO(SleepIsr_function);
void noteEvent(int string);
void I2C_reset(void);
void CCEvent(int cc, int val);
void DmaRxConfiguration(void);
/* DMA Configuration for DMA_RX */
#define DMA_RX_BYTES_PER_BURST      (1u)
#define DMA_RX_REQUEST_PER_BURST    (1u)
#define DMA_RX_SRC_BASE             (CYDEV_PERIPH_BASE)
#define DMA_RX_DST_BASE             (CYDEV_SRAM_BASE)

#define PLUCK_BUFFER_SIZE                 (26u)
#define BAR_BUFFER_SIZE                 (8u)
#define STORE_TD_CFG_ONCMPLT        (1u)
uint8 rx1Channel, rx2Channel __attribute__((aligned(32)));
uint8 rx1TD[2], rx2TD[2] __attribute__((aligned(32)));

volatile uint8 rxBufferPluck[2][PLUCK_BUFFER_SIZE] __attribute__((aligned(32)));
volatile uint8 rxBufferBar[2][BAR_BUFFER_SIZE] __attribute__((aligned(32)));

volatile uint16_t strings[12];
volatile uint16_t prevStrings[12];
volatile uint16_t bar[2];
volatile uint16_t prevBar[2];
volatile uint16_t maxStrings[12];
volatile uint8_t amHere = 0;
volatile uint8_t spiCounter = 0;
volatile uint8_t newDataFlag = 0;
int prevOctave = 0;
uint8_t pluck_index = 0;
volatile uint8_t amHere2 = 0;
volatile uint8_t spiCounter2 = 0;
volatile uint8_t newDataFlag2 = 0;
volatile uint8_t currentPluckBuffer = 0;
volatile uint8_t currentBarBuffer = 0;
volatile uint8_t pluckErrorCount = 0;
volatile uint16_t SPI1ErrorCount = 0;



volatile uint8_t inputData = 0;


union breakFloat {
 float f;
 uint8_t b[4];  
 uint32_t u32;
};


CY_ISR(spis_1_ss)
{
    currentPluckBuffer = !currentPluckBuffer;

    SPIS_1_ClearRxBuffer();
    CyDmaClearPendingDrq(rx1Channel);

    //set up the next DMA transaction

    CyDmaTdSetConfiguration(rx1TD[currentPluckBuffer], PLUCK_BUFFER_SIZE, DMA_DISABLE_TD, TD_INC_DST_ADR | DMA_1__TD_TERMOUT_EN);
    CyDmaTdSetAddress(rx1TD[currentPluckBuffer], LO16((uint32) SPIS_1_RXDATA_PTR), LO16((uint32) rxBufferPluck[currentPluckBuffer]));
    CyDmaChSetInitialTd(rx1Channel, rx1TD[currentPluckBuffer]);
    CyDmaChEnable(rx1Channel, 1);

    /*
    //get rid of any data in the spi2 buffer
    currentPluckBuffer = !currentPluckBuffer;
    pluck_index = 0;
    SPIS_1_ClearRxBuffer();
    //set up dma to transfer with a clean start
    //CyDmaChSetInitialTd(rx2Channel, rx2TD[0]);
    //CyDmaChEnable(rx2Channel, 1);
    //offsetErrorCount++;
    //disable this interrupt until another error occurs
    //isr_SPI2_ss_Stop();
    */
}

CY_ISR(spis_1_function) {     /* No need to clear any interrupt source; interrupt component should be      * configured for RISING_EDGE mode.      */     /* Read the debouncer status reg just to clear it, no need to check its      * contents in this application.      */  
    //SPI receive from pluck detector
    while(SPIS_1_GetRxBufferSize())
    {
        rxBufferPluck[currentPluckBuffer][pluck_index] = CY_GET_REG8(SPIS_1_RXDATA_PTR);
        pluck_index++;
    }
        
    if (pluck_index == 26)
    {
        if ((rxBufferPluck[currentPluckBuffer][0] == 254) && (rxBufferPluck[currentPluckBuffer][21] == 253))
        {

            for (int i = 0; i < 12; i++)
            {
                strings[i] = ((rxBufferPluck[currentPluckBuffer][(i*2)+1] << 7) + rxBufferPluck[currentPluckBuffer][i*2+2]);
            }
            
        }
        else
        {
            
            //disable the dma chain
            //CyDmaChDisable(rx2Channel);

            SPI1ErrorCount++;
            //enable an interrupt to reset it on the rising edge of the cs (at the end of an 8-byte transfer)
            //isr_SPI2_ss_StartEx(spis_2_ss);


            
            amHere = 1;
        }
    }
    /*
    uint8_t currentTd = 0;
    uint8_t state = 0;
     CyDmaChStatus(rx1Channel, &currentTd, &state);
    

    currentPluckBuffer = (currentTd & 1);
    if ((rxBufferPluck[currentPluckBuffer][0] == 254) && (rxBufferPluck[currentPluckBuffer][21] == 253))
    {
        for (int i = 0; i < 10; i++)
        {
            strings[i] = ((rxBufferPluck[currentPluckBuffer][(i*2)+1] << 7) + rxBufferPluck[currentPluckBuffer][i*2+2]);
        }
    }
    else
    {
        pluckErrorCount++;
    }
    amHere = 1;
    */
}

uint8_t spiAdjusted = 0;
uint8_t mySpiCounter = 0;
volatile uint16_t offsetErrorCount = 0;
volatile uint8_t SPI2errorflag = 0;
volatile int bar_index = 0;
uint8_t knobs[4];
uint8_t prevKnobs[4];

volatile uint8_t SPI2started = 0;


CY_ISR(spis_2_ss)
{
    //get rid of any data in the spi2 buffer


    currentBarBuffer = !currentBarBuffer;
    SPIS_2_ClearRxBuffer();
    CyDmaClearPendingDrq(rx2Channel);

    //set up the next DMA transaction

    CyDmaTdSetConfiguration(rx2TD[currentBarBuffer], BAR_BUFFER_SIZE, DMA_DISABLE_TD, TD_INC_DST_ADR | DMA_2__TD_TERMOUT_EN);
    CyDmaTdSetAddress(rx2TD[currentBarBuffer], LO16((uint32) SPIS_2_RXDATA_PTR), LO16((uint32) rxBufferBar[currentBarBuffer]));
    CyDmaChSetInitialTd(rx2Channel, rx2TD[currentBarBuffer]);
    CyDmaChEnable(rx2Channel, 1);
    //SPI2started = 1;

    /*
    //get rid of any data in the spi2 buffer
    currentBarBuffer = !currentBarBuffer;
    bar_index = 0;
    SPIS_2_ClearRxBuffer();
    */
    //set up dma to transfer with a clean start
    //CyDmaChSetInitialTd(rx2Channel, rx2TD[0]);
    //CyDmaChEnable(rx2Channel, 1);
    //offsetErrorCount++;
    //disable this interrupt until another error occurs
    //isr_SPI2_ss_Stop();
}


CY_ISR(spis_2_function) {     /* No need to clear any interrupt source; interrupt component should be      * configured for RISING_EDGE mode.      */     /* Read the debouncer status reg just to clear it, no need to check its      * contents in this application.      */  
    //SPI receive from bar sensor
    /*
    while(SPIS_2_GetRxBufferSize())
    {
        rxBufferBar[currentBarBuffer][bar_index] = CY_GET_REG8(SPIS_2_RXDATA_PTR);
        bar_index++;
    }
        
    if (bar_index == 8)
    {
        if ((rxBufferBar[currentBarBuffer][6] == 254) && (rxBufferBar[currentBarBuffer][7] == 253))
        {
            for (int i = 0; i < 2; i++)
            {
                bar[i] = ((rxBufferBar[currentBarBuffer][i*2] << 8) + rxBufferBar[currentBarBuffer][(i*2)+1]);
            }
            
        }
        else
        {
            
            //disable the dma chain
            //CyDmaChDisable(rx2Channel);
            SPI2errorflag = 1;
            offsetErrorCount++;
            //enable an interrupt to reset it on the rising edge of the cs (at the end of an 8-byte transfer)
            //isr_SPI2_ss_StartEx(spis_2_ss);


            
            amHere2 = 1;
        }
    }
    /*
        uint8_t currentTd = 0;
        uint8_t state = 0;
        CyDmaChStatus(rx2Channel, &currentTd, &state);
        currentBarBuffer = (currentTd & 1);
        uint8_t datasize = 8;
        */
    
    /*
        if ((rxBufferBar[currentBarBuffer][6] == 254) && (rxBufferBar[currentBarBuffer][7] == 253))
        {
            for (int i = 0; i < 2; i++)
            {
                bar[i] = ((rxBufferBar[currentBarBuffer][i*2] << 8) + rxBufferBar[currentBarBuffer][(i*2)+1]);
            }
            
        }
        else
        {
            
            //disable the dma chain
            //CyDmaChDisable(rx2Channel);
            SPI2errorflag = 1;
            //enable an interrupt to reset it on the rising edge of the cs (at the end of an 8-byte transfer)
            //isr_SPI2_ss_StartEx(spis_2_ss);


            
            amHere2 = 1;
        }
*/
        
        amHere = 1;

}



CY_ISR(SleepIsr_function)
{
    if (USB_active)
    {
        //check USB activity
        if( USB_CheckActivity() != 0u ) 
        {
            usbActivityCounter = 0u;
        } 
        else 
        {
            usbActivityCounter++;
        }

    }
    //Clear pending interrupt
    SleepTimer_GetStatus();
}

    static uint8 CYCODE eepromArray[]={ 0, 0 };
                                            
    uint8 array[] ={ 0, 0 };
                                
    /*Return status for EEPROM and UART*/ 
cy_en_em_eeprom_status_t eepromReturnValue;


/* EEPROM storage in work flash, this is defined in Em_EEPROM.c*/
#if defined (__ICCARM__)
#pragma data_alignment = CY_FLASH_SIZEOF_ROW
const uint8_t Em_EEPROM_em_EepromStorage[Em_EEPROM_PHYSICAL_SIZE] = {0u};
#else
const uint8_t Em_EEPROM_em_EepromStorage[Em_EEPROM_PHYSICAL_SIZE]
__ALIGNED(CY_FLASH_SIZEOF_ROW) = {0u};
#endif /* defined (__ICCARM__) */

    uint8 eeprom_cnt;
    cystatus status;
    volatile const uint8 * ptr;
volatile int barCount = 0;

//#define I2C_1_TIMEOUT_ENABLE 1u //overwrites the default in the i2c block
    
//this ISR should happen when a USB cable is plugged in or unplugged.

CY_ISR(Vbus_function)
{
    //plug or unplug event
    //check if eeprom has a flag saying you just restarted. If so, don't restart again
    //otherwise, restart
    my_Vbus_ISR_ClearPending();
    vBusPin_ClearInterrupt();
    restartSystemCheck();

}

void restartSystemCheck()
{
    eepromReturnValue = Em_EEPROM_Read(0u, eepromArray, 2u);
    if (*(volatile uint8 *) &eepromArray[0] == 1u)
    {
        //a flag says we just restarted
        //write a zero so it knows next time that it's OK to restart
        array[0] = 0;
        Em_EEPROM_Write(0u,array,2u);     
        USB_check_flag = 1;
    }
    else
    {
       //otherwise, we need to restart
       array[0] = 1;
       Em_EEPROM_Write(0u,array,2u);  
        USB_Stop();
        I2C_1_Stop();
       CySoftwareReset();
    }
}
    
#define INV_440 0.0022727272727273f

float   LEAF_clip(float min, float val, float max)
{
    float tempmin = min;
    float tempmax = max;
    if (min > max)
    {
        tempmin = max;
        tempmax = min;
    }
    if (val < tempmin)
    {
        return tempmin;
    }
    else if (val > tempmax)
    {
        return tempmax;
    }
    else
    {
        return val;
    }
}
float mtof(float f)
{
    if (f <= -1500.0f) return(0);
    else if (f > 1499.0f) return(mtof(1499.0f));
    else return (8.17579891564f * expf(0.0577622650f * f));
}

float ftom(float f)
{
    return (f > 0 ? 17.3123405046f * logf(.12231220585f * f) : -1500.0f);
}

// alpha, [0.0, 1.0]
float LEAF_interpolation_linear (float A, float B, float alpha)
{
    float omAlpha = 1.0f - alpha;
    
    // First 1/2 of interpolation
    float out = A * omAlpha;
    
    out += B * alpha;
    
    return out;
}


uint8 I2C_MasterWriteBlocking(uint8 i2CAddr, uint16 nbytes, uint8_t mode);
uint8 I2C_MasterReadBlocking(uint8 i2CAddr, uint8 nbytes, uint8_t mode);
void USB_service(void);

volatile uint8_t I2Cbuff1[256];
volatile uint8_t I2Cbuff2[16];
volatile uint8_t send_it = 0;

uint8_t mux_states[12][2] = {{5,0}, {5,1}, {5,2}, {5,3}, {5,4}, {0, 0}, {1, 0}, {3, 0}, {4, 0}, {2, 0}, {5, 5},{6,0}};
uint16_t pedals_low[10] = {2691, 2305, 2457, 526, 3738, 2307, 3014, 2190, 2793, 1318};
uint16_t pedals_high[10] = {2797, 2405, 2580, 647, 3854, 2461, 3141, 2353, 2934, 1504};
uint16_t deadzone = 150;
uint16_t volumePedal = 4095;
uint16_t processed_pedals[10];
uint16_t prev_processed_pedals[10];
int16_t prev_processed_volumePedal;
int16_t processed_volumePedal;


float fretMeasurements[4][2] ={

		{52703.0f, 62473.0f},

		{33446.0f, 41091.0f},

		{23331.0f, 30345.0f},

		{7712.0f, 13618.0f}

	};



float fretScaling[4] = {1.0f, 0.6666666666666f, 0.5f, 0.25f};


#define MAX_ENCODERS 16

float pedalRatios[10];
uint8_t last_mux = 1;
volatile uint8_t main_counter = 0;
uint8_t neck = 0;
uint8_t dualSlider = 0;
uint8_t enterUp = 1;
uint8_t voice = 0;
uint8_t editUp = 1;
volatile uint8_t encoderVal[MAX_ENCODERS];
int encoderNum = 0;
uint8_t button1Up = 0;
uint8_t button2Up = 0;
uint8_t button3Up = 0;
uint8_t button4Up = 0;
uint8_t patchNum = 0;
#define NUM_STRINGS 12
#define NUM_PEDALS 10
#if 0
float pedalsInCents[NUM_PEDALS][NUM_STRINGS] =
{
		{-0.16f, 0.0f, 0.0f, 0.0f, 1.84f, 0.0f, -0.16f, 0.0f, 0.0f, 1.84f, 0.0f, 0.0f},
		{0.0f, 0.0f, 116.0f, 0.0f, 0.0f, 116.0f, 0.0f, 0.0f, -14.0f, 0.0f, 116.0f, 0.0f},
		{-16.0f, 0.0f, 0.0f, 184.0f, 184.0f, 0.0f, -16.0f, 0.0f, 0.0f, 0.0f, 0.f, 0.0f},
		{0.0f, 0.0f, 0.0f, 0.0f, -200.0f, -200.0f, 0.0f, 0.0f, 0.0f, -200.0f, -200.0f, 0.0f},
        {-2400.0f, -2400.0f, -2400.0f, -2400.0f, -2400.0f, -2400.0f, -2400.0f, -2400.0f, -2400.0f, -2400.0f, -2400.0f, -2400.0f},
        {0.0f, 0.0f, 0.0f, -112.0f, 0.0f, 0.0f, 0.0f, -112.0f, 0.0f, 0.0f, 0.0f, -112.0f},
        {0.0f, 0.0f, 0.0f, 75.0f, 0.0f, 0.0f, 0.0f, 75.0f, 0.0f, 0.0f, 0.0f, 75.0f},
        {-14.0f, -204.0f, 0.0f, 0.0f, 0.0f, 0.0f, -14.0f, 0.0f, -134.0f, 0.0f, 0.0f, 0.0f},
		{186.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 0.0f, -100.0f, 0.0f, 0.0f, 0.0f, 0.0f, -100.0f, 0.0f, 0.0f},
};
float openStringMidinotes[NUM_STRINGS] = {66.04f,62.88f,67.86f, 64.0f,59.02f, 55.86f, 54.04f, 52.0f, 50.18f,  47.02f, 43.86,  40.0f };
#endif

float copedent[32][11][NUM_STRINGS];

float prevStringPitchBend[NUM_STRINGS];


#if 0 


float pedalsInCents[NUM_PEDALS][NUM_STRINGS] =
{
    {0.0f, 0.0f, -100.f, 0.0f, 0.0f, -100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f, 200.0f, 0.0f, 0.0f, 0.0f, 200.0f, 0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f, 200.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.f, 0.0f},
	{200.0f, 100.f, 0.0f, 0.0f, 0.0f, 0.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
    
    {0.0f, -200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -200.0f, 0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, -100.0f, 0.0f, 0.0f, 0.0f, -100.0f, 0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, -100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 300.0f, 300.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f, 0.0f, -100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
};

float openStringMidinotes[NUM_STRINGS] = {66.0f, 63.0f, 68.0f,  64.0f, 59.0f, 56.0f, 54.0f, 52.0f, 47.0f, 44.0f,40.0f, 35.0f };
#endif

float pedals[NUM_PEDALS][NUM_STRINGS];


float openStringFrequencies[NUM_STRINGS];
float stringMappedPositions[NUM_STRINGS];
float invStringMappedPositions[NUM_STRINGS];
float stringFrequencies[NUM_STRINGS];
float stringOctave[NUM_STRINGS];
float stringPitch[NUM_STRINGS];
float stringMIDI[NUM_STRINGS];
int openStringMIDI_Int[NUM_STRINGS];
int OLEDcount = 0;

/*
float fretMeasurements[4][2] ={
		{53699.0f, 62199.0f},
		{23462.0f, 30653.0f},
		{27336.0f, 28186.0f},
		{9460.0f, 9849.0f}
	};
float fretScaling[4] = {1.0f, 0.5f, 0.5f, 0.25f};
*/
float pedals_float[NUM_PEDALS] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

float map(float value, float istart, float istop, float ostart, float ostop)
{
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}

int currentNeck = 0;
#define EEPROM_COPEDENT_OFFSET 0
#define COPEDENT_SIZE_IN_BYTES 528

int main(void)
{
    
	CYGlobalIntEnable; 

    EEPROM_Start();
    
    //add deadzones on edges of pedal sensing
    for (int i = 0; i < NUM_PEDALS; i++)
    {

        float pedalDiff =(float)pedals_high[i] - (float)pedals_low[i];
        pedals_low[i] = pedals_low[i] + (0.1f * pedalDiff);
        pedals_high[i] = pedals_high[i] - (0.1f * pedalDiff);
        pedalDiff =(float)pedals_high[i] - (float)pedals_low[i];
        pedalRatios[i] = 4095.0f / pedalDiff;
    }
    //for (int i = 0; i < NUM_STRINGS; i++)
    //{
        //openStringFrequencies[i] = mtof(openStringMidinotes[i]);
        //stringOctave[i] = 1.0f;
   // }
    for (int i = 0; i < 11; i++)
	{
		int pedalStartLoc = i*48;
        //for (int j = 0; j < NUM_STRINGS; j++)
		//{
			//pedals[i][j] = pow(2.0, (pedalsInSemitones[currentNeck][i][j] / 1200.0));
		//}
        for (int j = 0; j < NUM_STRINGS; j++)
		{

            int stringStartLoc = j*4;

            union breakFloat myTemp;
            myTemp.b[0] = EEPROM_ReadByte(EEPROM_COPEDENT_OFFSET + stringStartLoc + pedalStartLoc);
            myTemp.b[1] = EEPROM_ReadByte(EEPROM_COPEDENT_OFFSET + stringStartLoc + pedalStartLoc + 1);
            myTemp.b[2] = EEPROM_ReadByte(EEPROM_COPEDENT_OFFSET + stringStartLoc + pedalStartLoc + 2);
            myTemp.b[3] = EEPROM_ReadByte(EEPROM_COPEDENT_OFFSET + stringStartLoc + pedalStartLoc + 3);
            copedent[0][i][j] = myTemp.f;
            
            myTemp.b[0] = EEPROM_ReadByte(EEPROM_COPEDENT_OFFSET + stringStartLoc + pedalStartLoc + COPEDENT_SIZE_IN_BYTES);
            myTemp.b[1] = EEPROM_ReadByte(EEPROM_COPEDENT_OFFSET + stringStartLoc + pedalStartLoc + COPEDENT_SIZE_IN_BYTES + 1);
            myTemp.b[2] = EEPROM_ReadByte(EEPROM_COPEDENT_OFFSET + stringStartLoc + pedalStartLoc + COPEDENT_SIZE_IN_BYTES + 2);
            myTemp.b[3] = EEPROM_ReadByte(EEPROM_COPEDENT_OFFSET + stringStartLoc + pedalStartLoc + COPEDENT_SIZE_IN_BYTES + 3);
            copedent[1][i][j] = myTemp.f;
        }
	}

    
    QuadDec_1_Start();
    LED_amber1_Write(0);
    LED_amber2_Write(1);
    LED_amber3_Write(0);
    LED_amber4_Write(0);
    //CyDmaChEnable(rxChannel, STORE_TD_CFG_ONCMPLT);
    
/*
    while(1)
    {
        if (!oct1_Read())
        {
            LED_amber1_Write(1);
            LED_amber2_Write(0);
            LED_amber3_Write(0);
            LED_amber4_Write(0);
        }
        if (!oct2_Read())
        {
            LED_amber1_Write(0);
            LED_amber2_Write(1);
            LED_amber3_Write(0);
            LED_amber4_Write(0);
        }
        if (!oct3_Read())
        {
            LED_amber1_Write(0);
            LED_amber2_Write(0);
            LED_amber3_Write(1);
            LED_amber4_Write(0);
        }
        if (!oct4_Read())
        {
            LED_amber1_Write(0);
            LED_amber2_Write(0);
            LED_amber3_Write(0);
            LED_amber4_Write(1);
        }


    }
    */
    SPIM_1_Start();
 


    //CyDelay(150);
    eepromReturnValue = Em_EEPROM_Init((uint32_t)Em_EEPROM_em_EepromStorage);
    if(eepromReturnValue != CY_EM_EEPROM_SUCCESS)
    {
       // HandleError();
    }
    uint8_t myArrayCounter = 0;
    I2C_1_Start();    
    USB_SetPowerStatus(USB_DEVICE_STATUS_SELF_POWERED);
    my_Vbus_ISR_StartEx(Vbus_function);
    ADC_SAR_Seq_1_Start();
    ADC_SAR_Seq_1_StartConvert();
    if (!USB_VBusPresent())
    {
        restartSystemCheck();
    }



    CyDelay(100);
    I2Cbuff1[0] = 1<<6;
    status = I2C_MasterWriteBlocking(0x70, 1, I2C_1_MODE_COMPLETE_XFER);

    OLED_init();
#if 0
    while(1)
    {
        for (int i=  0; i < 4; i++)
        {
            knobs[i] = 127 - (ADC_SAR_Seq_1_GetResult16(i)/32);
            if (knobs[i] != prevKnobs[i])
            {
               // sendMIDIControlChange(80+i, knobs[i]);
            }
            prevKnobs[i] = knobs[i];
        }
        

        I2Cbuff1[0] = 1<<0;
        uint8_t status = I2C_MasterWriteBlocking(0x70, 1, I2C_1_MODE_COMPLETE_XFER);

        //CyDelayUs(100);
        I2Cbuff1[0] = 0x0E;
        status = I2C_MasterWriteBlocking(0x36, 1, I2C_1_MODE_NO_STOP);
        status = I2C_MasterReadBlocking(0x36, 2, I2C_1_MODE_REPEAT_START);
       // CyDelayUs(100);
        angle[0] = I2Cbuff2[0] << 8;
        angle[0] +=  I2Cbuff2[1];
        
    }
    #endif
    //OLEDclear();
    /*
    while(1)
    {
        OLEDwriteInt(bar[1], 5, 0,FirstLine);
        OLED_draw();
        CyDelay(1);
        
        OLEDwriteInt(oct1_Read(), 1, 0,SecondLine);
        OLEDwriteInt(oct2_Read(), 1, 10,SecondLine);
        OLEDwriteInt(oct3_Read(), 1, 20,SecondLine);
        OLEDwriteInt(oct4_Read(), 1, 30,SecondLine);
        for (int i=  0; i < 4; i++)
        {
            OLEDwriteInt( ADC_SAR_Seq_1_GetResult16(i)/8, 3, i*30,2);
        }

    }
    */
#if 0
    I2Cbuff1[0] = 1<<mux_states[10][0];
    uint8_t status = I2C_MasterWriteBlocking(0x70, 1, I2C_1_MODE_COMPLETE_XFER);


    I2Cbuff1[0] = 1<<mux_states[10][1];
    status = I2C_MasterWriteBlocking(0x71, 1, I2C_1_MODE_COMPLETE_XFER);

    //address 0x48
    I2Cbuff1[0] = 0x1;
    I2Cbuff1[1] = 0b11000000;
    I2Cbuff1[2] = 0b10000011;

    status = I2C_MasterWriteBlocking(0x48, 3, I2C_1_MODE_COMPLETE_XFER);
    #endif
    
    SPIS_1_Start();  
    SPIM_1_Start();  
    SPIS_2_Start(); 
    DmaRxConfiguration();
    //isr_1_StartEx(isr_1_function);
    //isr_SPI1_DMA_StartEx(spis_1_function);
    isr_SPI1_ss_StartEx(spis_1_ss);
    //isr_SPI2_DMA_StartEx(spis_2_function);
    isr_SPI2_ss_StartEx(spis_2_ss);
    
    myArray[72] = 254;
    myArray[73] = 253;
    //temporarily start on the volume pedal for testing!
    //TODO: fix this
    main_counter = 0;
    //CyDelay(1000);
    //CyDelay(1);
	for(;;)
    {
        //if (newDataFlag)
        //{
        //}
            /*
            for (int i = 0; i < 5; i++)
            {
                I2C_1_MasterSendStart(0x70, 0); 
                I2C_1_MasterWriteByte(1<<i);
                I2C_1_MasterSendStop(); 


                I2C_1_MasterSendStart(0x36, 0); 
                I2C_1_MasterWriteByte(0x0C);
                //I2C_1_MasterSendStop();
                I2C_1_MasterSendRestart(0x36, 1); 
                rawAngle = I2C_1_MasterReadByte(1) << 8;
                //I2C_1_MasterSendRestart(0x36, 1);
                rawAngle +=  I2C_1_MasterReadByte(0);
                 I2C_1_MasterSendStop(); 
                
                CyDelay(1);

                I2C_1_MasterSendStart(0x36, 0); 
                I2C_1_MasterWriteByte(0x01);
                I2C_1_MasterWriteByte(rawAngle >> 8);
                I2C_1_MasterWriteByte(rawAngle & 0xff);
                I2C_1_MasterWriteByte((rawAngle+500) >> 8);
                I2C_1_MasterWriteByte((rawAngle+500) & 0xff);
                I2C_1_MasterSendStop(); 
                
                CyDelay(2);

                I2C_1_MasterSendStart(0x36, 0); 
                I2C_1_MasterWriteByte(0xff);
               I2C_1_MasterWriteByte(0x80);
                I2C_1_MasterSendStop(); 
               CyDelay(2);
            }
        */
        //set main i2c mux
    
        
        /*
        for (int i = 0; i < 4; i++)
        {
            I2C_1_MasterSendStart(0x71, 0); 
            I2C_1_MasterWriteByte(1<<(i+2));
            I2C_1_MasterSendStop(); 


            I2C_1_MasterSendStart(0x36, 0); 
            I2C_1_MasterWriteByte(0x0C);
            //I2C_1_MasterSendStop();
            I2C_1_MasterSendRestart(0x36, 1); 
            rawAngle = I2C_1_MasterReadByte(1) << 8;
            //I2C_1_MasterSendRestart(0x36, 1);
            rawAngle +=  I2C_1_MasterReadByte(0);
             I2C_1_MasterSendStop(); 
            
            CyDelay(1);

            I2C_1_MasterSendStart(0x36, 0); 
            I2C_1_MasterWriteByte(0x01);
            I2C_1_MasterWriteByte(rawAngle >> 8);
            I2C_1_MasterWriteByte(rawAngle & 0xff);
            I2C_1_MasterWriteByte((rawAngle+700) >> 8);
            I2C_1_MasterWriteByte((rawAngle+700) & 0xff);
            I2C_1_MasterSendStop(); 
            
            CyDelay(2);

            I2C_1_MasterSendStart(0x36, 0); 
            I2C_1_MasterWriteByte(0xff);
            I2C_1_MasterWriteByte(0x80);
            I2C_1_MasterSendStop(); 
           CyDelay(2);
        }
            */
        /*    
        if (main_counter == 6)
        {
            main_counter = 8;
        }
        */    

            
        if (mux_states[main_counter][0] != last_mux)
        {
            I2Cbuff1[0] = 1<<mux_states[main_counter][0];
            uint8_t status = I2C_MasterWriteBlocking(0x70, 1, I2C_1_MODE_COMPLETE_XFER);
        }
        last_mux = mux_states[main_counter][0];
        
        CyDelayUs(10);
        if (mux_states[main_counter][0] == 5)
        {
            I2Cbuff1[0] = 1<<mux_states[main_counter][1];
            status = I2C_MasterWriteBlocking(0x71, 1, I2C_1_MODE_COMPLETE_XFER);
        }

        CyDelayUs(10);
        //if it's a hall sensor
        if (main_counter < 10)
        {
            //CyDelayUs(100);
            I2Cbuff1[0] = 0x0E;
            status = I2C_MasterWriteBlocking(0x36, 1, I2C_1_MODE_NO_STOP);
            status = I2C_MasterReadBlocking(0x36, 2, I2C_1_MODE_REPEAT_START);
           // CyDelayUs(100);
            angle[main_counter] = I2Cbuff2[0] << 8;
            angle[main_counter] +=  I2Cbuff2[1];
        }
        //otherwise it's the ADC for the foot pedal
        else if (main_counter == 10)
        {
        //0x4D is the 7=-bit version of the MCP3221 address, might need to be shifted over by 1 to the left
            I2Cbuff1[0] = 0x0;      
            status = I2C_MasterReadBlocking(0x4f, 2, I2C_1_MODE_COMPLETE_XFER);
            volumePedal = I2Cbuff2[0] << 8;
            volumePedal +=  I2Cbuff2[1];
        }
        
        else
        { 
            if (OLEDcount == 0)
            {
                OLEDclearLine(FirstLine);
            }
            else if (OLEDcount == 1)
            {
                OLEDwriteInt(encoderNum, 2, 0, FirstLine);
		    }
            else if (OLEDcount == 2)
            {
                OLEDwriteString(" ", 1, OLEDgetCursor(), FirstLine);
            }
            else if (OLEDcount == 3)
            {
                OLEDwriteInt(encoderVal[encoderNum], 3, OLEDgetCursor(), FirstLine);
            }
            else if (OLEDcount == 4)
            {
                OLEDwriteString("     ", 5, OLEDgetCursor(), FirstLine);
            }
            else if (OLEDcount == 5)
            {
                OLEDwriteInt(patchNum, 2, OLEDgetCursor(), FirstLine);
            }
            else if (OLEDcount == 6)
            {
                OLED_drawFirstLine();
            }
            OLEDcount++;
            if (OLEDcount > 6)
            {
                OLEDcount = 0;
            }
        }
        
        /*
        I2Cbuff1[0] = 1<<main_counter;
        uint8_t status = I2C_MasterWriteBlocking(0x71, 1, I2C_1_MODE_COMPLETE_XFER);

                for (int i = 0; i < 5; i++)
                {
                    I2Cbuff1[0] = 1<<i;
                    status = I2C_MasterWriteBlocking(0x70, 1, I2C_1_MODE_COMPLETE_XFER);

                    I2Cbuff1[0] = 0x0E;
                    status = I2C_MasterWriteBlocking(0x36, 1, I2C_1_MODE_NO_STOP);

                    status = I2C_MasterReadBlocking(0x36, 2, I2C_1_MODE_REPEAT_START);


                    angle[i] = I2Cbuff2[0] << 8;
                    angle[i] +=  I2Cbuff2[1];
                }
            if (main_counter == 0)
            {               
                I2Cbuff1[0] = 1<<main_counter;
                uint8_t status = I2C_MasterWriteBlocking(0x71, 1, I2C_1_MODE_COMPLETE_XFER);

                for (int i = 0; i < 5; i++)
                {
                    I2Cbuff1[0] = 1<<i;
                    status = I2C_MasterWriteBlocking(0x70, 1, I2C_1_MODE_COMPLETE_XFER);

                    I2Cbuff1[0] = 0x0E;
                    status = I2C_MasterWriteBlocking(0x36, 1, I2C_1_MODE_NO_STOP);

                    status = I2C_MasterReadBlocking(0x36, 2, I2C_1_MODE_REPEAT_START);


                    angle[i] = I2Cbuff2[0] << 8;
                    angle[i] +=  I2Cbuff2[1];
                }
            }
            else
            {
                I2Cbuff1[0] = 1<<(main_counter+1);
                uint8_t status = I2C_MasterWriteBlocking(0x71, 1, I2C_1_MODE_COMPLETE_XFER);
                I2Cbuff1[0] = 0x0E;
                status = I2C_MasterWriteBlocking(0x36, 1, I2C_1_MODE_NO_STOP);
                if (status == I2C_1_MSTAT_ERR_XFER)
                {
                    I2Cbuff1[0] = 1<<(main_counter+1);
                    status = I2C_MasterWriteBlocking(0x71, 1, I2C_1_MODE_COMPLETE_XFER);
                }
           


                status = I2C_MasterReadBlocking(0x36, 2, I2C_1_MODE_REPEAT_START);
                 //I2C_1_MasterReadBuf(0x36, I2Cbuff3, 2, I2C_1_MODE_REPEAT_START);
                if (status == I2C_1_MSTAT_ERR_XFER)
                {
                    I2Cbuff1[0] = 1<<(main_counter+1);
                    status = I2C_MasterWriteBlocking(0x71, 1, I2C_1_MODE_COMPLETE_XFER);
                }
                
                angle[main_counter+4] = I2Cbuff2[0] << 8;
                angle[main_counter+4] +=  I2Cbuff2[1];
            }    
                

            send_it = 1;
        }
        */
        
        if (main_counter < 10)
        {
            
            //do math to make all pedals and levers report between 0 and 4095 scaled
            int16_t tempangle = ((int16_t) angle[main_counter] - (int16_t)pedals_low[main_counter]);
            
            if (tempangle > 0)
            {
                processed_pedals[main_counter] = (float)tempangle * pedalRatios[main_counter];
            }
            else
            {
                processed_pedals[main_counter] = 0;
            }
            if (processed_pedals[main_counter] > 4095)
            {
                processed_pedals[main_counter] = 4095;
            }
            
            
            if ( processed_pedals[main_counter] != prev_processed_pedals[main_counter])
            {
                //sendMIDIControlChange(main_counter, (processed_pedals[main_counter] >> 7), 1);
                //sendMIDIControlChange(main_counter+36, (processed_pedals[main_counter] & 127), 1);
            }
            pedals_float[main_counter] = (float)processed_pedals[main_counter] * 2.442002442002442e-4f;
            prev_processed_pedals[main_counter] = processed_pedals[main_counter];
        }
        else
        {
            processed_volumePedal = (float)volumePedal * 1.007378258730939f; //compensate for lower than full scale voltage readings

            if (processed_volumePedal < 0)
            {
                processed_volumePedal = 0;
            }
            else if (processed_volumePedal > 4095)
            {
                 processed_volumePedal = 4095;
            }
            
            if ( processed_volumePedal != prev_processed_volumePedal)
            {
                uint16_t tempPedal = processed_volumePedal;
                
                sendMIDIControlChange(21, ( tempPedal >> 7), 0);
                sendMIDIControlChange(22, ( tempPedal & 127), 0);
            }
             prev_processed_volumePedal = processed_volumePedal;
        }
        
        main_counter++;

        if (main_counter > 11)
        {
            main_counter = 0;
        }
        
        #if 0
            
            
        main_counter++;
        if (main_counter >= 11)
        {
               /*  
            testpin3_Write(1);
            I2Cbuff1[0] = 1<<6;
    status = I2C_MasterWriteBlocking(0x71, 1, I2C_1_MODE_COMPLETE_XFER);
        OLEDwriteInt(bar[1], 5, 0,FirstLine);

        //CyDelay(1);
        
        OLEDwriteInt(octave, 1, 0,SecondLine);

        OLED_draw();
                    I2Cbuff1[0] = 1<<0;
    status = I2C_MasterWriteBlocking(0x71, 1, I2C_1_MODE_COMPLETE_XFER);
        testpin3_Write(0);
            */
            main_counter = 0;
        }
        #endif
        if ((rxBufferBar[!currentBarBuffer][6] == 254) && (rxBufferBar[!currentBarBuffer][7] == 253))
        {
            for (int i = 0; i < 2; i++)
            {
                bar[i] = ((rxBufferBar[!currentBarBuffer][i*2] << 8) + rxBufferBar[!currentBarBuffer][(i*2)+1]);    
    
                if (bar[i] != prevBar[i])
                {
    				if ((bar[i] == 65535) || (bar[i] > fretMeasurements[0][i]))
    				{
    					stringMappedPositions[i] = 1.0f;
    				}

    				else if ((bar[i] >= fretMeasurements[1][i]) && (bar[i] <= fretMeasurements[0][i]))
    				{
    					stringMappedPositions[i] = map((float)bar[i], fretMeasurements[0][i], fretMeasurements[1][i], fretScaling[0], fretScaling[1]);
    				}

    				else if ((bar[i] >= fretMeasurements[2][i]) && (bar[i] < fretMeasurements[1][i]))
    				{
    					stringMappedPositions[i] = map((float)bar[i], fretMeasurements[1][i], fretMeasurements[2][i], fretScaling[1], fretScaling[2]);
    				}

    				else
    				{
    					stringMappedPositions[i] = map((float)bar[i], fretMeasurements[2][i], fretMeasurements[3][i], fretScaling[2], fretScaling[3]);
    				}

                    invStringMappedPositions[i] = 1.0f / stringMappedPositions[i];
                }
                prevBar[i] = bar[i];
            }
        }
        if ((rxBufferPluck[!currentPluckBuffer][0] == 254) && (rxBufferPluck[!currentPluckBuffer][25] == 253)) 
        {
            for (int i = 0 ; i < 12; i++)
            {
                strings[i] = ((rxBufferPluck[!currentPluckBuffer][(i*2)+1] << 7) + rxBufferPluck[!currentPluckBuffer][i*2+2]);
                if (strings[i] != prevStrings[i])
                {
                    noteEvent(i);
                }
                
                prevStrings[i] = strings[i];
            }
        }


        
        
        if (!oct1_Read())
        {
            octave = 0;
            LED_amber1_Write(1);
            LED_amber2_Write(0);
            LED_amber3_Write(0);
            LED_amber4_Write(0);
        }
        else if (!oct2_Read())
        {
            octave = 1;
            LED_amber1_Write(0);
            LED_amber2_Write(1);
            LED_amber3_Write(0);
            LED_amber4_Write(0);
        }
        else if (!oct3_Read())
        {
            octave = 2;
            LED_amber1_Write(0);
            LED_amber2_Write(0);
            LED_amber3_Write(1);
            LED_amber4_Write(0);            
        }
        else if (!oct4_Read())
        {
            octave = 3;
            LED_amber1_Write(0);
            LED_amber2_Write(0);
            LED_amber3_Write(0);
            LED_amber4_Write(1);
        }
        
        if (!neck1_button_Read())
        {
            neck = 0;
            currentNeck = 0;
            LED_red1_Write(0);
            LED_green2_Write(1);
        }
        if (!neck2_button_Read())
        {
            neck = 1;
            currentNeck = 1;
            LED_red1_Write(1);
            LED_green2_Write(0);
        }
        
        if ((!enter_button_Read()) && (enterUp))
        {
            dualSlider = !dualSlider;
            LED_green1_Write(dualSlider);
            enterUp = 0;
        }
        else if (enter_button_Read())
        {
            enterUp = 1;
        }
        
        
        
        if ((!button1_Read()) && (button1Up))
        {
            encoderNum -= 1;
            encoderNum &= 15;
            button1Up = 0;
        }
        else if (button1_Read())
        {
            button1Up = 1;
        }
        
        if ((!button2_Read()) && (button2Up))
        {
            encoderNum += 1;
            encoderNum &= 15;
            button2Up = 0;
        }
        else if (button2_Read())
        {
            button2Up = 1;
        }
        
        if ((!button3_Read()) && (button3Up))
        {
            patchNum -= 1;
            patchNum &= 15;
            button3Up = 0;
        }
        else if (button3_Read())
        {
            button3Up = 1;
        }
        
        if ((!button4_Read()) && (button4Up))
        {
            patchNum += 1;
            patchNum &= 15;
            button4Up = 0;
        }
        else if (button4_Read())
        {
            button4Up = 1;
        }
        
        if ((!edit_button_Read()) && (editUp))
        {
            voice = !voice;
            LED_red2_Write(voice);
            editUp = 0;
        }
        else if (edit_button_Read())
        {
            editUp = 1;
        }
        
        if (octave != prevOctave)
        {
            //sendMIDIControlChange(90, octave);
        }
        prevOctave = octave;
        
        
        for (int i=  0; i < 4; i++)
        {
            knobs[i] = (ADC_SAR_Seq_1_GetResult16(i)/32);
            if (i != 1)
            {
                knobs[i] = 127.0f - knobs[i];
            }
            if (knobs[i] != prevKnobs[i])
            {
                sendMIDIControlChange(i+17, knobs[i], 0);
            }
            prevKnobs[i] = knobs[i];
        }
        
       
        //calculate the pitch of each string based on the current Copedent
        for (int i = 0; i < NUM_STRINGS; i++)
    	{
    		//interpolate ratios for each of the strings
           /*
            float myMappedPos;
            if (dualSlider)
            {
               myMappedPos = LEAF_interpolation_linear(stringMappedPositions[0], stringMappedPositions[1], ((float)i) * 0.090909090909091f);
            }
            else
            {
                myMappedPos = stringMappedPositions[0];
            }

    		stringOctave[i] = powf(2.0f,octave);
            */
    		//then apply those ratios to the fundamental frequencies
    		float tempMIDI = (copedent[currentNeck][0][i] +
                        (copedent[currentNeck][4][i] * pedals_float[0]) +
                        (copedent[currentNeck][5][i] * pedals_float[1]) +
                        (copedent[currentNeck][6][i] * pedals_float[2]) +
                        (copedent[currentNeck][7][i] * pedals_float[3]) +
                        (copedent[currentNeck][8][i] * pedals_float[4]) +
                        (copedent[currentNeck][10][i] * pedals_float[5]) +
                        (copedent[currentNeck][9][i] * pedals_float[6]) +
                        (copedent[currentNeck][3][i] * pedals_float[7]) +
                        (copedent[currentNeck][1][i] * pedals_float[8]) +
                        (copedent[currentNeck][2][i] * pedals_float[9]));
    		//stringPitch[i] = tempFreq;
            //stringMIDI[i] = ftom(stringPitch[i]);
            
            float openStringMIDI  = copedent[currentNeck][0][i];
            openStringMIDI_Int[i] = (int)openStringMIDI;
            
            float barMIDI = ftom((invStringMappedPositions[0]) * mtof(tempMIDI));
            
            float computerMIDIOffset = barMIDI - openStringMIDI_Int[i];// + stringOctave[i];
            
            float pitchBendAmount = (computerMIDIOffset* 341.0f) + 8192.0f;  // 14bit number divide by 2 for signed, then divided by 24 for 24 semitones up/down range
            if (pitchBendAmount != prevStringPitchBend[i])
            {
                sendMIDIPitchBend((uint)pitchBendAmount, i+1);
            }
            prevStringPitchBend[i] = pitchBendAmount;
            if (tempMIDI > 0.0f)
            {
                stringMIDI[i] = tempMIDI;
            }
    	}

        if (encoder_button_Read())
        {
            encoderVal[encoderNum] += QuadDec_1_GetCounter() * 4;
        }
        else
        {
            encoderVal[encoderNum] += QuadDec_1_GetCounter();
        }
        QuadDec_1_SetCounter(0);
        

        
        if (USB_check_flag)
        {
            checkUSB_Vbus();
        }
        //only service the USB bus if there is a computer plugged in
        if ((USB_active) && (USB_VBusPresent()))
        {
            if (midiSent > 64)
            {
                midiOverflow++;
            }
            midiSent = 0;
            USB_service();
        }

        
        /*
        for (int i = 0; i < 10; i++)
        {
            myArray[i * 2] = processed_pedals[i] >> 8;
            myArray[(i * 2) + 1] = processed_pedals[i] & 0xff;
        }
        
        myArray[20] = octave | (voice << 2) | (dualSlider << 3) | (neck << 4);
        for (int i = 0; i < 4; i++)
        {
            myArray[i+21] = knobs[i];
        }
        myArray[25] = processed_volumePedal >> 8;
        myArray[26] = processed_volumePedal & 0xff;
        */
        
        for (int i = 0; i < 12; i++)
        {
            union breakFloat tempBreak;
            tempBreak.f = stringMIDI[i];
            
            
            myArray[i * 4] = tempBreak.b[0];
            myArray[(i * 4) + 1] = tempBreak.b[1];
            myArray[(i * 4) + 2] = tempBreak.b[2];
            myArray[(i * 4) + 3] = tempBreak.b[3];
        }
        
        myArray[48] = octave | (voice << 2) | (dualSlider << 3) | (neck << 4);
        for (int i = 0; i < 4; i++)
        {
            myArray[i+49] = knobs[i];
        }
        myArray[53] = processed_volumePedal >> 8;
        myArray[54] = processed_volumePedal & 0xff;
        myArray[55] = patchNum;
        for (int i = 0; i < 16; i++)
        {
            myArray[i+56] = encoderVal[i];
        }
        for(int i = 0; i < 74; i++)
        {

            SPIM_1_WriteTxData(myArray[i]);
        }

        //CyDelayUs(400);
        
        
     }
}



void DmaRxConfiguration()
{ 

    //pluck dma
    rx1Channel = DMA_1_DmaInitialize(DMA_RX_BYTES_PER_BURST, DMA_RX_REQUEST_PER_BURST,
                                     HI16(DMA_RX_SRC_BASE), HI16(DMA_RX_DST_BASE));

    rx1TD[0] = CyDmaTdAllocate();
    rx1TD[1] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(rx1TD[0], PLUCK_BUFFER_SIZE, DMA_DISABLE_TD , TD_INC_DST_ADR | DMA_1__TD_TERMOUT_EN);
    CyDmaTdSetConfiguration(rx1TD[1], PLUCK_BUFFER_SIZE, DMA_DISABLE_TD, TD_INC_DST_ADR | DMA_1__TD_TERMOUT_EN);
    CyDmaTdSetAddress(rx1TD[0], LO16((uint32) SPIS_1_RXDATA_PTR), LO16((uint32) rxBufferPluck[0]));
    CyDmaTdSetAddress(rx1TD[1], LO16((uint32) SPIS_1_RXDATA_PTR), LO16((uint32) rxBufferPluck[1]));

    
    
    //bar dma
    rx2Channel = DMA_2_DmaInitialize(DMA_RX_BYTES_PER_BURST, DMA_RX_REQUEST_PER_BURST,
                                     HI16(DMA_RX_SRC_BASE), HI16(DMA_RX_DST_BASE));
    rx2TD[0] = CyDmaTdAllocate();
    rx2TD[1] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(rx2TD[0], BAR_BUFFER_SIZE, DMA_DISABLE_TD, TD_INC_DST_ADR | DMA_2__TD_TERMOUT_EN);
    CyDmaTdSetConfiguration(rx2TD[1], BAR_BUFFER_SIZE, DMA_DISABLE_TD, TD_INC_DST_ADR | DMA_2__TD_TERMOUT_EN);
    CyDmaTdSetAddress(rx2TD[0], LO16((uint32) SPIS_2_RXDATA_PTR), LO16((uint32) rxBufferBar[0]));
    CyDmaTdSetAddress(rx2TD[1], LO16((uint32) SPIS_2_RXDATA_PTR), LO16((uint32) rxBufferBar[1]));


    /*
    rx1Channel = DMA_2_DmaInitialize(DMA_RX_BYTES_PER_BURST, DMA_RX_REQUEST_PER_BURST,
                                     HI16(DMA_RX_SRC_BASE), HI16(DMA_RX_DST_BASE));

    rx1TD[0] = CyDmaTdAllocate();
    rx1TD[1] = CyDmaTdAllocate();

    CyDmaTdSetConfiguration(rx1TD[0], BAR_BUFFER_SIZE, rx1TD[1] , TD_INC_DST_ADR | DMA_2__TD_TERMOUT_EN);
    CyDmaTdSetConfiguration(rx1TD[1], BAR_BUFFER_SIZE, rx1TD[0] , TD_INC_DST_ADR | DMA_2__TD_TERMOUT_EN);
    CyDmaTdSetAddress(rx1TD[0], LO16((uint32) SPIS_2_RXDATA_PTR), LO16((uint32) rxBufferBar[0]));
    CyDmaTdSetAddress(rx1TD[1], LO16((uint32) SPIS_2_RXDATA_PTR), LO16((uint32) rxBufferBar[1]));
    CyDmaChSetInitialTd(rx1Channel, rx1TD[0]);
    CyDmaChEnable(rx1Channel, 1);
    
    
    rx2Channel = DMA_1_DmaInitialize(DMA_RX_BYTES_PER_BURST, DMA_RX_REQUEST_PER_BURST,
                                     HI16(DMA_RX_SRC_BASE), HI16(DMA_RX_DST_BASE));

    rx2TD[0] = CyDmaTdAllocate();
    rx2TD[1] = CyDmaTdAllocate();

    CyDmaTdSetConfiguration(rx2TD[0], PLUCK_BUFFER_SIZE, rx2TD[1] , TD_INC_DST_ADR | DMA_1__TD_TERMOUT_EN);
    CyDmaTdSetConfiguration(rx2TD[1], PLUCK_BUFFER_SIZE, rx2TD[0] , TD_INC_DST_ADR | DMA_1__TD_TERMOUT_EN);
    CyDmaTdSetAddress(rx2TD[0], LO16((uint32) SPIS_1_RXDATA_PTR), LO16((uint32) rxBufferPluck[0]));
    CyDmaTdSetAddress(rx2TD[1], LO16((uint32) SPIS_1_RXDATA_PTR), LO16((uint32) rxBufferPluck[1]));
    CyDmaChSetInitialTd(rx2Channel, rx2TD[0]);
    CyDmaChEnable(rx2Channel, 1);
*/
}
uint8 I2C_MasterWriteBlocking(uint8 i2CAddr, uint16 nbytes, uint8_t mode)
{
    uint8 volatile status;
    uint32_t timeout = 50000;
    status = I2C_1_MasterClearStatus();
    if(!(status & I2C_1_MSTAT_ERR_XFER))
    {
        status = I2C_1_MasterWriteBuf(i2CAddr, (uint8 *)&I2Cbuff1, nbytes,
                                     mode);
        if(status == I2C_1_MSTR_NO_ERROR)
        {
            /* wait for write complete and no error */
            do
            {
                status = I2C_1_MasterStatus();
                timeout--;
                if (status == I2C_1_MSTAT_ERR_XFER)
                {
                    I2C_reset();
                }
                if (timeout == 0)
                {
                    status = I2C_1_MSTAT_ERR_XFER;
                    I2C_reset();
                }
                /*
                if (status == 0)
                {
                    status = I2C_1_MSTAT_ERR_XFER;
                    I2C_reset();
                }
                */
            } while(((status & (I2C_1_MSTAT_WR_CMPLT | I2C_1_MSTAT_ERR_XFER)) == 0u) && (status != 0u) && (timeout>0));
        }
        else
        {
            /* translate from I2CM_MasterWriteBuf() error output to
            *  I2CM_MasterStatus() error output */
            status = I2C_1_MSTAT_ERR_XFER;
            I2C_reset();
        } 
    }  
    return status;
}

uint8 I2C_MasterReadBlocking(uint8 i2CAddr, uint8 nbytes, uint8_t mode)
{
    uint8 volatile status;
    uint32_t timeout = 50000;
    status = I2C_1_MasterClearStatus();
    if(!(status & I2C_1_MSTAT_ERR_XFER))
    {
        status = I2C_1_MasterReadBuf(i2CAddr,
                                   (uint8 *)&(I2Cbuff2),
                                    nbytes, mode); 
        if(status == I2C_1_MSTR_NO_ERROR)
        {
            /* wait for read complete and no error */
            do
            {
                status = I2C_1_MasterStatus();
                timeout--;
                if (status == I2C_1_MSTAT_ERR_XFER)
                {
                    I2C_1_GENERATE_STOP_MANUAL;
                    I2C_reset();
                }
                if (timeout == 0)
                {
                    status = I2C_1_MSTAT_ERR_XFER;
                    I2C_reset();
                }
                /*
                if (status == 0)
                {
                    status = I2C_1_MSTAT_ERR_XFER;
                    I2C_reset();
                }
                */
            } while(((status & (I2C_1_MSTAT_RD_CMPLT | I2C_1_MSTAT_ERR_XFER)) == 0u) && (status != 0u) && (timeout>0));
        }
        else
        {
            /* translate from I2CM_MasterReadBuf() error output to
            *  I2CM_MasterStatus() error output */
            status = I2C_1_MSTAT_ERR_XFER;
            I2C_reset();
        }
    }
    return status;
}

void I2C_reset(void)
{
    //I2C_1_GENERATE_STOP_MANUAL;
    //I2C_1_state = I2C_1_SM_EXIT_IDLE;
    //CyDelay(100);
    ///I2C_1_Stop();
    //CyDelay(100);
    //I2C_1_Init();
    //CyDelay(100);
    //I2C_1_Start();
    //CyDelay(100);
    /*
            if (mux_states[main_counter][0] != last_mux)
        {
            I2Cbuff1[0] = 1<<mux_states[main_counter][0];
            uint8_t status = I2C_MasterWriteBlocking(0x71, 1, I2C_1_MODE_COMPLETE_XFER);
        }
        last_mux = mux_states[main_counter][0];
        
        CyDelayUs(10);
        if (mux_states[main_counter][0] == 0)
        {
            I2Cbuff1[0] = 1<<mux_states[main_counter][1];
            status = I2C_MasterWriteBlocking(0x70, 1, I2C_1_MODE_COMPLETE_XFER);
        }
        main_counter = 0;
    */
}

void checkUSB_Vbus(void)
{
   if (USB_VBusPresent() == 0)
   {
       USB_Stop();
       //LED_PWM_Write(0);
       USB_active = 0; 
        //CySoftwareReset();
   }
   else if (USB_active == 0 )
   {
       USB_Start(0u, USB_3V_OPERATION ); 
        while (0u == USB_GetConfiguration());
        USB_MIDI_EP_Init();
       //LED_PWM_Write(255);
       USB_active = 1;
   }
   USB_check_flag = 0;
}



void USB_service(void)
{
    if(USB_IsConfigurationChanged() != 0u)
    {
        if(USB_GetConfiguration() != 0u)   
        {
           // Sleep_isr_StartEx(SleepIsr_function);
            
            //SleepTimer_Start();
        	
            if ((USB_active) && (USB_VBusPresent()))
            {
                USB_MIDI_EP_Init();
            }
        }
        else
        {
            //SleepTimer_Stop();
        }    
    }        
    
    if(USB_GetConfiguration() != 0u)    
    {
        
        #if(USB_EP_MM != USB__EP_DMAAUTO) 
            if ((USB_active) && (USB_VBusPresent()))
            {
                USB_MIDI_IN_Service();
            }
        #endif

        #if(USB_EP_MM != USB__EP_DMAAUTO) 
            if ((USB_active) && (USB_VBusPresent()))
            {
                USB_MIDI_OUT_Service();
            }
        #endif

/*
        if( usbActivityCounter >= 2u ) 
        {

            USB_Suspend();

            CyPmSaveClocks();
            CyPmSleep(PM_SLEEP_TIME_NONE, PM_SLEEP_SRC_PICU);
            CyPmRestoreClocks();

            USB_Resume();
            USB_MIDI_EP_Init();
            
            usbActivityCounter = 0u; 

        }
        */
    }
        
}

// This is a fast approximation to log2()
// Y = C[0]*F*F*F + C[1]*F*F + C[2]*F + C[3] + E;
float log2f_approx(float X) {
  float Y, F;
  int E;
  F = frexpf(fabsf(X), &E);
  Y = 1.23149591368684f;
  Y *= F;
  Y += -4.11852516267426f;
  Y *= F;
  Y += 6.02197014179219f;
  Y *= F;
  Y += -3.13396450166353f;
  Y += E;
  return(Y);
}

//log10f is exactly log2(x)/log2(10.0f)
#define log10f_fast(x)  (log2f_approx(x)*0.3010299956639812f)

int prevNotes[NUM_STRINGS] = {0,0,0,0,0,0,0,0,0,0,0,0};

void noteEvent(int string)
{
    float tempAmp = strings[string] * 1.5259021896696421759365224689097e-5f;//divide by 65535
    float v = 127.0f + (64.0f * log10f_fast(tempAmp));
    int vInt  = (int) (v*4.0f);
    if (vInt > 127)
    {
        vInt = 127;
    }
    if (strings[string] == 0)
    {
        sendMIDINoteOn(prevNotes[string], 0, string+1);
    }
    else
    {
        if (vInt > 0)
        {
            //only update octave on note-ons
            //stringOctave[string] = powf(2.0f,octave);
            int noteToSend = ((octave - 1) * 12) + openStringMIDI_Int[string];
            sendMIDINoteOn(noteToSend , ((uint8_t)vInt), string+1);
            prevNotes[string] = noteToSend;
        }
        else
        {
             sendMIDINoteOn(prevNotes[string], 0, string+1);
        }
    }
}

void CCEvent(int cc, int val)
{
    
    sendMIDIControlChange(cc, val, 0);
}

void sendMIDINoteOn(int MIDInoteNum, int velocity, int channel)
{  
   
    midiMsg[0] = USB_MIDI_NOTE_ON + channel;
    midiMsg[1] = MIDInoteNum;
    midiMsg[2] = velocity;	
    //MIDI1_UART_PutArray(midiMsg, 3);
    if ((USB_active) && (USB_VBusPresent()))
    {
        USB_PutUsbMidiIn(3u, midiMsg, USB_MIDI_CABLE_00);
    } 
    midiSent += 4;
}

void sendMIDIPolyKeyPressure(int MIDInoteNum, int pressure, int channel)
{
    midiMsg[0] = USB_MIDI_POLY_KEY_PRESSURE + channel;
    midiMsg[1] = MIDInoteNum;
    midiMsg[2] = pressure;		
    //MIDI1_UART_PutArray(midiMsg, 3);

    if ((USB_active) && (USB_VBusPresent()))
    {
        USB_PutUsbMidiIn(3u, midiMsg, USB_MIDI_CABLE_00);
    } 
    midiSent += 4;
}

void sendMIDIControlChange(int CCnum, int CCval, int channel)
{
    midiMsg[0] = USB_MIDI_CONTROL_CHANGE + channel;
    midiMsg[1] = CCnum;
    midiMsg[2] = CCval;			
    //MIDI1_UART_PutArray(midiMsg, 3);
    
    if ((USB_active) && (USB_VBusPresent()))
    {
        USB_PutUsbMidiIn(3u, midiMsg, USB_MIDI_CABLE_00);
    } 
    midiSent += 4;
}

void sendMIDIPitchBend(int val, int channel)
{
    midiMsg[0] = USB_MIDI_PITCH_BEND_CHANGE + channel;
    midiMsg[1] = (val & 127); //LSB
    midiMsg[2] = (val >> 7);	//MSB		

    //MIDI1_UART_PutArray(midiMsg, 3);
    
    if ((USB_active) && (USB_VBusPresent()))
    {
        USB_PutUsbMidiIn(3u, midiMsg, USB_MIDI_CABLE_00);
    } 
    midiSent += 4;
}

void sendMIDIAllNotesOff(void)
{   
    for (i = 0; i < 128; i++)
    {
        midiMsg[0] = USB_MIDI_NOTE_ON;
        midiMsg[1] = i;
        midiMsg[2] = 0;	
       // MIDI1_UART_PutArray(midiMsg, 3);
        if ((USB_active) && (USB_VBusPresent()))
        {       
            USB_PutUsbMidiIn(3u, midiMsg, USB_MIDI_CABLE_00);
        }
    }
}



uint8_t sysexBuffer[128];
uint32_t sysexPointer = 0;
uint8_t receivingSysex = 0;
uint8_t parsingSysex = 0;
volatile uint8_t checkStatus = 0;
volatile uint8_t checkBase = 0;

volatile uint8_t testy = 0;

volatile uint8_t presetArray[74];

void parseSysex(void)
{
    // 0 = it's a preset
    if (sysexBuffer[0] == 0)
    {
        testy = 1;
        for(uint32_t i = 0; i < 72; i++)
        {
            if (i < sysexPointer)
            {   
                presetArray[i] = sysexBuffer[i];
            }
            else
            {
                presetArray[i] = 255;
            }
        }
        presetArray[72] = 240;
        presetArray[73] = 241;
        
        SPIM_1_WriteTxData(presetArray[i]);
        
    }
    //1 = it's a copedent
    if (sysexBuffer[0] == 1)
    {
        if ((sysexBuffer[2] > 49) && (sysexBuffer[2] <= 61))
        {
            union breakFloat theVal;
            uint32_t currentFloat = 0;
            uint32_t pedalToWrite = sysexBuffer[2] - 50;
            uint16_t pedalStartLoc = pedalToWrite * 48;


            for (uint32_t i = 3; i < sysexPointer; i = i+5)
            {
                theVal.u32 = 0;
                theVal.u32 |= ((sysexBuffer[i] &15) << 28);
                theVal.u32 |= (sysexBuffer[i+1] << 21);
                theVal.u32 |= (sysexBuffer[i+2] << 14);
                theVal.u32 |= (sysexBuffer[i+3] << 7);
                theVal.u32 |= (sysexBuffer[i+4] & 127);

                copedent[currentNeck][pedalToWrite][currentFloat] = theVal.f;
                uint16_t stringStartLoc = currentFloat * 4;
                checkBase = EEPROM_COPEDENT_OFFSET + stringStartLoc + pedalStartLoc + (COPEDENT_SIZE_IN_BYTES * currentNeck);
                checkStatus = EEPROM_WriteByte(theVal.b[0], EEPROM_COPEDENT_OFFSET + stringStartLoc + pedalStartLoc + (COPEDENT_SIZE_IN_BYTES * currentNeck));
                checkStatus = EEPROM_WriteByte(theVal.b[1], EEPROM_COPEDENT_OFFSET + stringStartLoc + pedalStartLoc + (COPEDENT_SIZE_IN_BYTES * currentNeck) + 1);
                checkStatus = EEPROM_WriteByte(theVal.b[2], EEPROM_COPEDENT_OFFSET + stringStartLoc + pedalStartLoc + (COPEDENT_SIZE_IN_BYTES * currentNeck) + 2);
                checkStatus = EEPROM_WriteByte(theVal.b[3], EEPROM_COPEDENT_OFFSET + stringStartLoc + pedalStartLoc + (COPEDENT_SIZE_IN_BYTES * currentNeck) + 3);
            
                currentFloat++;         
            }
        }
    }
    parsingSysex = 0;
    
}

uint8_t tempMIDI[4];

// this gets called if the Brain gets a MIDI message from the computer host
void USB_callbackLocalMidiEvent(uint8 cable, uint8 *midiMsg) CYREENTRANT
{   
    tempMIDI[0] = midiMsg[0];
    tempMIDI[1] = midiMsg[1];
     tempMIDI[2] = midiMsg[2];
     tempMIDI[3] = midiMsg[3];
    //check that we got here
    
    if ((USB_active) && (USB_VBusPresent()))
    { 
        /*
        if(midiMsg[USB_EVENT_BYTE0] == USB_MIDI_NOTE_ON)
        {
    
            //write the note on into the mastrKeys array, which stores all the pitches on/off info for the brain
            masterKeys[ midiMsg[USB_EVENT_BYTE1] ][0] = midiMsg[USB_EVENT_BYTE2];
            int possibleKey = (int)USB_EVENT_BYTE1 + (int)cvOffsetFinal - 32 - (int)keyOffset;
            if ((possibleKey < NUM_KEYS) && (possibleKey >= 0))
            {
                //looks like the MIDI note from the computer also lands on the keyboard with the current CV offset and keyOffset, so associate it with a key
                masterKeys[ midiMsg[USB_EVENT_BYTE1] ][1] = possibleKey;
            }
            else
            {
                masterKeys[ midiMsg[USB_EVENT_BYTE1] ][1] = -1;
            }
            if (midiMsg[USB_EVENT_BYTE2] > 0)
            {
                //note on
                addToNoteStack(midiMsg[USB_EVENT_BYTE1]);
                if (mainMode == SEQUENCERMODE)
                {
                    if (toggleKeys[midiMsg[USB_EVENT_BYTE1]] == 0)
                    {
                        toggleKeys[midiMsg[USB_EVENT_BYTE1]] = 1;
                        addToSequencerStack(midiMsg[USB_EVENT_BYTE1]);
                    }
                    else
                    {
                        toggleKeys[midiMsg[USB_EVENT_BYTE1]] = 0;
                        removeFromSequencerStack(midiMsg[USB_EVENT_BYTE1]);
                    }
                }
            }
            else
            {
                //note off
                removeFromNoteStack(midiMsg[USB_EVENT_BYTE1]);
            }
            
        }
        
        if (midiMsg[USB_EVENT_BYTE0] == USB_MIDI_CONTROL_CHANGE)
        {
            computerCC[midiMsg[USB_EVENT_BYTE2]] = midiMsg[USB_EVENT_BYTE1];
            
            if (midiMsg[USB_EVENT_BYTE2] == 0) // low res 7-bit full value
            {
                DACvalue16 = (midiMsg[USB_EVENT_BYTE1] << 5); 
                //send the DAC value to masterpitch sensor
                WriteCommandPacket((DACvalue16 >> 8),(DACvalue16 & 255) , masterPitch);
            }
            
            if (midiMsg[USB_EVENT_BYTE2] == 1) // high byte
            {
                DACvalue16 = (midiMsg[USB_EVENT_BYTE1] << 7) + DAClowbyte7; 
                //send the DAC value to masterpitch sensor
                WriteCommandPacket((DACvalue16 >> 8),(DACvalue16 & 255) , masterPitch);
            }
            if (midiMsg[USB_EVENT_BYTE2] == 2) // low byte
            {
                DAClowbyte7 = midiMsg[USB_EVENT_BYTE1];
            }

        }
        */
        
        if (receivingSysex)
        {
            for (int i = 0; i < 3; i++)
            {
                if (midiMsg[i] < 128)
                {
                    sysexBuffer[sysexPointer++] = midiMsg[i];
                }
                else
                {
                    if (midiMsg[i] == USB_MIDI_EOSEX)
                    {
                        receivingSysex = 0;
                        parsingSysex = 1;
                        parseSysex();
                     }
                }
            }

        }
        if (midiMsg[USB_EVENT_BYTE0] == USB_MIDI_SYSEX)
        {
            if (!parsingSysex)
            {
                receivingSysex = 1;
                sysexPointer = 0;
                sysexBuffer[sysexPointer++] = midiMsg[1];
                sysexBuffer[sysexPointer++] = midiMsg[2];
            }
        }
        
        cable = cable; // so it doesn't complain about unused variables
    }
}    

/* [] END OF FILE */
