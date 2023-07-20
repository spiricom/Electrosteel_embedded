/*main.c
*****************************************************************************/
#include <device.h>
#include <stdio.h>
#include <math.h>
#include "oled.h"
#include "main.h"


#define EEPROM_NECKS_OFFSET 0
#define EEPROM_COPEDENT_OFFSET 2
#define COPEDENT_SIZE_IN_BYTES 278 //including name bytes
#define COPEDENT_SIZE_IN_FLOATS 132 // not including name bytes
#define NAME_LENGTH_IN_BYTES 14
#define EEPROM_CALIBRATION_OFFSET (EEPROM_NECKS_OFFSET + EEPROM_COPEDENT_OFFSET + (MAX_NUM_COPEDENTS * COPEDENT_SIZE_IN_BYTES))
#define CALIBRATION_SIZE_IN_BYTES NUM_PEDALS * 4 //for each pedal, store 2 bytes for high and 2 bytes for low
#define MACRO_CLIPPED_LENGTH 8
#define NAME_CLIPPED_LENGTH 11
#define COPEDENT_NAME_CLIPPED_LENGTH 8
#define myBufferSize 32
void parseSysex(void);

uint8_t sysexBuffer[2048];
uint32_t sysexPointer = 0;
uint8_t receivingSysex = 0;
uint8_t parsingSysex = 0;
volatile uint8_t presetArray[2048];
uint8_t presetNumberToWrite = 0;
uint8_t copedentNumberToWrite = 0;
uint8_t sendMessageEnd = 0;

uint8_t sendSingleParamUpdate = 0;
uint8_t singleParamToUpdateHigh = 0;
uint8_t singleParamToUpdateLow = 0;
uint8_t singleParamValueHigh = 0;
uint8_t singleParamValueLow = 0;
            
            
enum presetArraySectionState
{
    presetName = 0,
    macroNames = 1,
    initialVals = 2,
    mapCountNext = 3,
    mapping = 4,
    presetEnd = 5,
};
uint8_t presetArraySection = presetName;

uint16_t messageArraySendCount = 0;
uint16_t messageArraySize = 0;

uint8_t sysexMessageInProgress = 0;

uint8_t bufCount = 0;
volatile uint8_t sendingMessage = 0;
volatile uint8_t sendKnobs = 0;
uint32_t currentFloat = 0;
uint32_t mapCount = 0;

uint16_t valsCount = 0;
uint16_t mapCountExpectation = 0;
uint16_t numMappings = 0;
volatile uint8_t parseThatMF = 0;
volatile float valCheck = 0.0f;
volatile float testVal = 0.0f;

int numStrings = 10;
/*
#define TUNING_ARRAY_SIZE 258
uint8_t tuningArray[TUNING_ARRAY_SIZE];
*/

volatile uint8 usbActivityCounter = 0u;
uint8 midiMsg[4];
uint8_t currentVBUS = 0;
uint8_t prevVBUS = 0;
volatile uint8_t USB_active = 0;
volatile uint8_t USB_check_flag = 0;


uint8 inBuffer[myBufferSize];

uint8 myArray[myBufferSize];
uint8 myInputArray[2];
int32_t linearPotValue32Bit[2];
uint8_t i = 0;
uint8_t counter = 0;
uint8_t returnedData[myBufferSize];
int32_t temper;
int previousButtons[11];
int octave = 5;
uint16_t angle[10];
uint16_t prevAngle[10];

uint16_t ADC_values[4];
uint16_t rawAngle = 0;
uint16_t midiSent = 0;
uint16_t midiOverflow = 0;

uint8_t macroKnobValues[8];

uint8_t currentCopedent = 0;
uint8_t necks[2] = {0,1};

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

void DmaTxConfiguration(void);

/* DMA Configuration for DMA_TX */
#define DMA_TX_BYTES_PER_BURST      (1u)
#define DMA_TX_REQUEST_PER_BURST    (1u)
#define DMA_TX_SRC_BASE             (CYDEV_SRAM_BASE)
#define DMA_TX_DST_BASE             (CYDEV_PERIPH_BASE)

#define PLUCK_BUFFER_SIZE                 (26u)
#define BAR_BUFFER_SIZE                 (8u)
#define STORE_TD_CFG_ONCMPLT        (1u)
uint8 rx1Channel, rx2Channel __attribute__((aligned(32)));
uint8 rx1TD[2], rx2TD[2]  __attribute__((aligned(32)));

volatile uint8 txChannel __attribute__((aligned(32)));
volatile uint8 txTD __attribute__((aligned(32)));

volatile uint8 rx3Channel __attribute__((aligned(32)));
volatile uint8 rx3TD __attribute__((aligned(32)));


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

    if ((rxBufferPluck[!currentPluckBuffer][0] == 254) && (rxBufferPluck[!currentPluckBuffer][25] == 253)) 
    {
        for (int i = 0 ; i < numStrings; i++)
        {
            strings[i] = ((rxBufferPluck[!currentPluckBuffer][(i*2)+1] << 8) + rxBufferPluck[!currentPluckBuffer][i*2+2]);
        }
    }
    SPIS_1_ClearRxBuffer();
    CyDmaClearPendingDrq(rx1Channel);

    //set up the next DMA transaction

    CyDmaTdSetConfiguration(rx1TD[currentPluckBuffer], PLUCK_BUFFER_SIZE, DMA_DISABLE_TD, TD_INC_DST_ADR | DMA_1__TD_TERMOUT_EN);
    CyDmaTdSetAddress(rx1TD[currentPluckBuffer], LO16((uint32) SPIS_1_RXDATA_PTR), LO16((uint32) rxBufferPluck[currentPluckBuffer]));
    CyDmaChSetInitialTd(rx1Channel, rx1TD[currentPluckBuffer]);
    CyDmaChEnable(rx1Channel, 1);

}



uint8_t spiAdjusted = 0;
uint8_t mySpiCounter = 0;
volatile uint16_t offsetErrorCount = 0;
volatile uint8_t SPI2errorflag = 0;
volatile int bar_index = 0;
uint8_t knobs[4];
uint8_t prevKnobs[4];

uint8_t knobs7bit[4];
uint8_t prevKnobs7bit[4];

volatile uint8_t SPI2started = 0;

uint8_t whichMacro = 0;

CY_ISR(spis_2_ss)
{

    currentBarBuffer = !currentBarBuffer;
    SPIS_2_ClearRxBuffer();
    CyDmaClearPendingDrq(rx2Channel);

    //set up the next DMA transaction
    CyDmaTdSetConfiguration(rx2TD[currentBarBuffer], BAR_BUFFER_SIZE, DMA_DISABLE_TD, TD_INC_DST_ADR | DMA_2__TD_TERMOUT_EN);
    CyDmaTdSetAddress(rx2TD[currentBarBuffer], LO16((uint32) SPIS_2_RXDATA_PTR), LO16((uint32) rxBufferBar[currentBarBuffer]));
    CyDmaChSetInitialTd(rx2Channel, rx2TD[currentBarBuffer]);
    CyDmaChEnable(rx2Channel, 1);
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
    //only do the restart check if there is a USB cable plugged in (to avoid restarting while trying to debug without a usb cable plugged in)
    if (USB_VBusPresent() == 1)
    {
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


//first mux, 0x70 is first element of array. 
//If sent to output 5 of this first mux, signal goes to 
// the ethernet cable, and a second mux is in the foot pedal at the end of that cable. This channel is selected with the second element of the array
//so the order of I2C communication is ( foot pedals 1-5, knee levers 1-5, volume pedal, OLED display )
uint8_t mux_states[12][2] = {{5,0}, {5,1}, {5,2}, {5,3}, {5,4}, {0, 0}, {1, 0}, {3, 0}, {4, 0}, {2, 0}, {5, 5},{6,0}};
uint8_t i2c_skipped[12] = {0,0,0,0,0,0,0,0,0,0,0,0}; //so that pedals and levers can be marked as skipped if communication fails because they are unconnected
uint16_t pedals_low[10] = {2691, 2305, 2457, 526, 3738, 2307, 3014, 2190, 2793, 1318};
uint16_t pedals_high[10] = {2797, 2405, 2580, 647, 3854, 2461, 3141, 2353, 2934, 1504};
uint16_t deadzone = 150;
uint16_t volumePedal = 4095;
uint16_t processed_pedals[10];
uint16_t prev_processed_pedals[10];
uint8_t pedals8bit[10];
uint8_t pedals7bit[10];
uint8_t prevPedals7bit[10];
int16_t prev_processed_volumePedal;
int16_t processed_volumePedal;


float fretMeasurements[4][4] ={

		{62750.0f, 61600.0f, 31785.0f, 0.0f },

		{39600.0f, 41500.0f, 15700.0f, 0.0f},

		{27520.0f, 30200.0f, 8458.0f, 0.0f},

		{9490.0f, 13600.0f, 2674.0f, 0.0f}

	};
#define NUM_MACROS 8
#define MAX_NUM_PRESETS 64
int currentPresetSelection = 0;
uint8_t presetNamesArray[MAX_NUM_PRESETS][NAME_LENGTH_IN_BYTES];
uint8_t presetNumberToLoad = 0;
uint8_t presetLoadedResponse[2] = {255, 0};


uint8_t macroNamesArray[MAX_NUM_PRESETS][NUM_MACROS][NAME_LENGTH_IN_BYTES];



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
uint8_t oct1Up = 1;
uint8_t oct4Up = 1;

volatile uint8_t encoderVal[MAX_ENCODERS];
int encoderNum = 0;
uint8_t button1Up = 0;
uint8_t button2Up = 0;
uint8_t button3Up = 0;
uint8_t button4Up = 0;
uint8_t patchNum = 0;
#define NUM_STRINGS 12
#define NUM_PEDALS 10


#define MAX_NUM_COPEDENTS 7
float copedent[MAX_NUM_COPEDENTS][11][NUM_STRINGS];
uint8_t copedentNamesArray[MAX_NUM_COPEDENTS][NAME_LENGTH_IN_BYTES];

float prevStringPitchBend[NUM_STRINGS];

float pedals[NUM_PEDALS][NUM_STRINGS];

uint8_t pedal_cc_assignments[NUM_PEDALS] = {0, 1, 2, 3, 4, 8, 9, 7, 6, 5};
float openStringFrequencies[NUM_STRINGS];
float stringMappedPositions[NUM_STRINGS];
float invStringMappedPositions[NUM_STRINGS];
float stringFrequencies[NUM_STRINGS];
float stringOctave[NUM_STRINGS];
float stringPitch[NUM_STRINGS];
float stringMIDI[NUM_STRINGS];
int openStringMIDI_Int[NUM_STRINGS];
int OLEDcount = 0;

int mainOLEDWaitingToSend = 0;
int macroOLEDWaitingToSend = 0;

int presetAlreadyDisplayed[MAX_NUM_PRESETS];

float pedals_float[NUM_PEDALS] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

float map(float value, float istart, float istop, float ostart, float ostop)
{
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}
void displayCurrentPresetNameAndCopedent();

int currentNeck = 0;

int editMode = 0;
int calibrationMode = 0;

void burnInitialPedalZeroPositions()
{
    
}


void calculatePedalRatios()
{

    //add deadzones on edges of pedal sensing
    for (int i = 0; i < NUM_PEDALS; i++)
    {

        float pedalDiff =(float)pedals_high[i] - (float)pedals_low[i];
        pedals_low[i] = pedals_low[i] + (0.1f * pedalDiff);
        pedals_high[i] = pedals_high[i] - (0.1f * pedalDiff);
        pedalDiff =(float)pedals_high[i] - (float)pedals_low[i];
        pedalRatios[i] = 4095.0f / pedalDiff;
    }
}
int main(void)
{
    
	CYGlobalIntEnable; 
    EEPROM_Start();
    
        eepromReturnValue = Em_EEPROM_Init((uint32_t)Em_EEPROM_em_EepromStorage);
    if(eepromReturnValue != CY_EM_EEPROM_SUCCESS)
    {
       // HandleError();
    }
    uint8_t myArrayCounter = 0;
  
    I2C_1_Start();  
    USB_SetPowerStatus(USB_DEVICE_STATUS_SELF_POWERED);
    my_Vbus_ISR_StartEx(Vbus_function);
    


    
    CyDelay(2000);
    //read from eeprom which copedents are loaded on which necks
    necks[0] = EEPROM_ReadByte(EEPROM_NECKS_OFFSET);
    necks[1] = EEPROM_ReadByte(EEPROM_NECKS_OFFSET + 1);
    
    for (int coped = 0; coped < MAX_NUM_COPEDENTS; coped++)
    {
        
        for (int letter = 0; letter < NAME_LENGTH_IN_BYTES; letter++)
        {
               copedentNamesArray[coped][letter] = EEPROM_ReadByte(EEPROM_COPEDENT_OFFSET + (coped*COPEDENT_SIZE_IN_BYTES) + letter);
        }
        for (int i = 0; i < 11; i++)
    	{
    		int pedalStartLoc = (i*24);
            for (int j = 0; j < NUM_STRINGS; j++)
    		{
                
                int stringStartLoc = (j*2);
                uint16_t tempIntHigh = EEPROM_ReadByte(EEPROM_COPEDENT_OFFSET + stringStartLoc + pedalStartLoc + (coped*COPEDENT_SIZE_IN_BYTES) + NAME_LENGTH_IN_BYTES);
                uint16_t tempIntLow = EEPROM_ReadByte(EEPROM_COPEDENT_OFFSET + stringStartLoc + pedalStartLoc + 1 + (coped*COPEDENT_SIZE_IN_BYTES)+ NAME_LENGTH_IN_BYTES);
                copedent[coped][i][j] = (((float)((tempIntHigh << 8) + tempIntLow)) * 0.00390625f) - 128.0f;// (256 value range from -128 to 128, divided by 65536)
            }
    	}
    }

    
    for (int i = 0; i < NUM_PEDALS; i++)
    {
        pedals_low[i] = (EEPROM_ReadByte(EEPROM_CALIBRATION_OFFSET + (i*4)) << 8) + (EEPROM_ReadByte(EEPROM_CALIBRATION_OFFSET + ((i*4) + 1)) & 255);
        pedals_high[i] = (EEPROM_ReadByte(EEPROM_CALIBRATION_OFFSET + ((i*4) + 2)) << 8) + (EEPROM_ReadByte(EEPROM_CALIBRATION_OFFSET + ((i*4) + 3)) & 255);
    }
    calculatePedalRatios();
                
    //blank out the preset names array so that we can tell when we get the real names from the synth board sd card
    for (int i = 0; i < MAX_NUM_PRESETS; i++)
    {
        for (int j = 0; j < NAME_LENGTH_IN_BYTES; j++)
        {
            presetNamesArray[i][j] = 255;

        }
        for (int j = 0; j < NUM_MACROS; j++)
        {
            for (int k = 0; k < NAME_LENGTH_IN_BYTES; k++)
            {
                macroNamesArray[i][j][k] = 255;
            }
        }
        presetAlreadyDisplayed[i] = 0;
    }
    
    QuadDec_1_Start();
    LED_amber1_Write(0);
    LED_amber2_Write(1);
    LED_amber3_Write(0);
    LED_amber4_Write(0);





    
    LED_red1_Write(0);
    LED_green2_Write(1);

    
    ADC_SAR_Seq_1_Start();
    ADC_SAR_Seq_1_StartConvert();

            
    currentCopedent = necks[currentNeck];
    CyDelay(10);
    
    //set up for the OLED screen's first write
    I2Cbuff1[0] = 1<<6;
    status = I2C_MasterWriteBlocking(0x70, 1, I2C_1_MODE_COMPLETE_XFER);
    myGFX_init(128, 64);
    myGFX_setFont(0);
    OLED_init(128, 64);
    OLEDwriteInt(currentCopedent , 2, 0,FourthLine);
    OLEDwriteString(" ", 1, OLEDgetCursor(), FourthLine);
    OLEDwriteString((char *)&copedentNamesArray[currentCopedent][0], COPEDENT_NAME_CLIPPED_LENGTH, OLEDgetCursor(), FourthLine);
    OLED_draw(128, 64);
    
    
    I2Cbuff1[0] = 1<<2;
    status = I2C_MasterWriteBlocking(0x70, 1, I2C_1_MODE_COMPLETE_XFER);

    for (int w = 0; w < 8; w++)
    {
        I2Cbuff1[0] = (1 << 3) + w;
        status = I2C_MasterWriteBlocking(0x72, 1, I2C_1_MODE_COMPLETE_XFER); 
        OLED_init(128, 32);
        //OLEDwriteInt(w , 1, 0,FirstLine);
        //OLEDwriteString(" ", 1, OLEDgetCursor(), FourthLine);
        //OLEDwriteString((char *)&copedentNamesArray[currentCopedent][0], NAME_LENGTH_IN_BYTES, OLEDgetCursor(), FourthLine);
       // OLED_draw(128, 32);
    }

    //initialize the macro knob adc to scan all knobs
    I2Cbuff1[0] = 1<<2;
    status = I2C_MasterWriteBlocking(0x70, 1, I2C_1_MODE_COMPLETE_XFER);
    main_counter = 9;

    I2Cbuff1[0] = 0xf; //message says scan single-ended mode from beginning to 8th knob (scan all knobs)
    status = I2C_MasterWriteBlocking(0x35, 1, I2C_1_MODE_COMPLETE_XFER);
    
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
    DmaTxConfiguration();
    DmaRxConfiguration();
    isr_SPI1_ss_StartEx(spis_1_ss);
    isr_SPI2_ss_StartEx(spis_2_ss);
    
    myArray[30] = 254;
    myArray[31] = 253;

    main_counter = 0;

	for(;;)
    {
        
        if (parseThatMF)
        {
            parseSysex();
        }
        
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
        testpin3_Write(1);
       //sense levers and pedals
        if (mux_states[main_counter][0] != last_mux)
        {
            I2Cbuff1[0] = 1<<mux_states[main_counter][0];
            uint8_t status = I2C_MasterWriteBlocking(0x70, 1, I2C_1_MODE_COMPLETE_XFER);
        }
        last_mux = mux_states[main_counter][0];
        
        
        CyDelayUs(10);
        if (mux_states[main_counter][0] == 5)
        {
            if (!i2c_skipped[main_counter])
            {
                I2Cbuff1[0] = 1<<mux_states[main_counter][1];
                status = I2C_MasterWriteBlocking(0x71, 1, I2C_1_MODE_COMPLETE_XFER);
            }
        }

        CyDelayUs(10);
        //if it's a hall sensor

        //temporarily don't scan vertical knee lever, should be <10 normally
        if (main_counter < 10)
        {
            if (!i2c_skipped[main_counter])
            {
                //CyDelayUs(100);
                I2Cbuff1[0] = 0x0E;
                status = I2C_MasterWriteBlocking(0x36, 1, I2C_1_MODE_NO_STOP);
                if (status == 0)
                {
                    status = I2C_MasterReadBlocking(0x36, 2, I2C_1_MODE_REPEAT_START);
                }
                if (status  == 0)
                {
                    //CyDelayUs(100);
                    angle[main_counter] = I2Cbuff2[0] << 8;
                    angle[main_counter] +=  I2Cbuff2[1];
                    
                    if (calibrationMode)
                    {
                        if (angle[main_counter] < pedals_low[main_counter])
                        {
                            if (main_counter == 0)
                            {
                                if (angle[main_counter] != 0)
                                {
                                     pedals_low[main_counter] = angle[main_counter];
                                }
                            }
                            else
                            {
                                pedals_low[main_counter] = angle[main_counter];
                            }
                            
                        }
                        if (angle[main_counter] > pedals_high[main_counter])
                        {
                             pedals_high[main_counter] = angle[main_counter];
                        }
                    }
                }
            }
        }
        
        //in addition to the hall sensor on {2,0} (the vertical knee lever) of the muxes, there is also the knob/oled board, so scan that as well on main counter round 9
        if (main_counter == 9)
        {
            if (!i2c_skipped[main_counter])
            {
                //scan the knob adc
                I2Cbuff1[0] = 0x0;      
                status = I2C_MasterReadBlocking(0x35, 16, I2C_1_MODE_COMPLETE_XFER);
                if (status == 0)
                {
                    for (int i = 0; i < NUM_MACROS; i++)
                    {
                       uint16_t tempInt =((I2Cbuff2[i*2] << 8) + (I2Cbuff2[i*2] & 255)) & 4095; // necessary to AND with 4095 to eliminate the 4 preceding bits set high by default
                        macroKnobValues[i] = 255 - (tempInt >> 4); //now squish it down to 8 bit for sending (also subtract from 255 because the pot is backwards for some reason
                    }
                    //
                    if (macroOLEDWaitingToSend == 2)
                    {
                        //send the data to the little macro OLED screens
                        
                        I2Cbuff1[0] = (1 << 3) + whichMacro;
                        status = I2C_MasterWriteBlocking(0x72, 1, I2C_1_MODE_COMPLETE_XFER); 
                        //OLED_init(128, 32);
                        OLEDclear(128, 32);
                        //OLEDwriteInt(w , 1, 0,FirstLine);
                        //OLEDwriteString(" ", 1, OLEDgetCursor(), FourthLine);
                        myGFX_setFont(1);
                        //GFXsetFont(&theGFX,  &SourceCodePro_Regular14pt7b);
                        OLEDwriteString((char *)&macroNamesArray[patchNum][whichMacro][0], MACRO_CLIPPED_LENGTH,0, SecondLine);
                        OLED_draw(128, 32);

                        whichMacro++;
                        if (whichMacro >=8)
                        {
                            macroOLEDWaitingToSend = 0;
                            whichMacro = 0;
                        }
                    }
                }
            }
            
        }
        //otherwise it's the ADC for the foot pedal
        else if (main_counter == 10)
        {
            //0x4f (0x4D?) is the 7=-bit version of the MCP3221 address, might need to be shifted over by 1 to the left
            if (!i2c_skipped[main_counter])
            {
                I2Cbuff1[0] = 0x0;      
                status = I2C_MasterReadBlocking(0x4f, 2, I2C_1_MODE_COMPLETE_XFER);
                if (status == 0)
                {
                    volumePedal = I2Cbuff2[0] << 8;
                    volumePedal +=  I2Cbuff2[1];
                }
            }
        }
        else
        if (main_counter == 11)
        { 
            if (mainOLEDWaitingToSend)
            {
                OLED_draw(128, 64);
                mainOLEDWaitingToSend = 0;
            }
            if (macroOLEDWaitingToSend == 1)
            {
                macroOLEDWaitingToSend = 2;
            }
            
            #if 0
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
                //OLED_drawFirstLine();
                
                //OLEDwriteInt( bar[0] , 6, 0,SecondLine);
                //OLEDwriteInt(currentCopedent , 2, 0,FourthLine);
                //OLEDwriteString(" ", 1, OLEDgetCursor(), FourthLine);
                //OLEDwriteString((char *)&copedentNamesArray[currentCopedent][0], NAME_LENGTH_IN_BYTES, OLEDgetCursor(), FourthLine);
                 //OLED_draw();
            }
            OLEDcount++;
            if (OLEDcount > 6)
            {
                OLEDcount = 0;
            }
            #endif
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
            
            
            //if ( processed_pedals[main_counter] != prev_processed_pedals[main_counter])
            {
                //sendMIDIControlChange(main_counter, (processed_pedals[main_counter] >> 7), 1);
                //sendMIDIControlChange(main_counter+36, (processed_pedals[main_counter] & 127), 1);
            }
            pedals_float[main_counter] = (float)processed_pedals[main_counter] * 2.442002442002442e-4f;
            pedals8bit[main_counter] = (float)processed_pedals[pedal_cc_assignments[main_counter]] * 0.0625f;
            pedals7bit[main_counter] = pedals8bit[main_counter] >> 1;
            if (pedals7bit[main_counter] != prevPedals7bit[main_counter])
            {
                sendMIDIControlChange(main_counter + 14, (pedals7bit[main_counter]), 1);
            }
            prevPedals7bit[main_counter] = pedals7bit[main_counter];
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
                
                sendMIDIControlChange(13, ( tempPedal >> 5), 0);
                //sendMIDIControlChange(22, ( tempPedal & 127), 0);
            }
             prev_processed_volumePedal = processed_volumePedal;
        }
        
        main_counter++;

        if (main_counter > 11)
        {
            main_counter = 0;
        }
        testpin3_Write(0);
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
        testpin5_Write(1);
        
        if ((rxBufferBar[!currentBarBuffer][6] == 254) && (rxBufferBar[!currentBarBuffer][7] == 253))
        {
            for (int i = 0; i < 2; i++)
            {
                bar[i] = ((rxBufferBar[!currentBarBuffer][i*2] << 8) + rxBufferBar[!currentBarBuffer][(i*2)+1]);    
                //
                if(bar[i] != prevBar[i])
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
                //
                prevBar[i] = bar[i];
            }
        }
        
        testpin5_Write(0);
        for (int i = 0 ; i < numStrings; i++)
        {
            if (strings[i] != prevStrings[i])
            {
                noteEvent(i);
            }
            prevStrings[i] = strings[i];
        }
        


        
        
        if (!oct1_Read())
        {
            if (octave > 4)
            {
                octave = 4;

            }
            else if ((oct1Up) && (octave > 0))
            {
                octave--;
            }
            LED_amber1_Write(1);
            LED_amber2_Write(0);
            LED_amber3_Write(0);
            LED_amber4_Write(0);
            oct1Up = 0;
        }
        
        else if (oct1_Read())
        {
            oct1Up = 1;
        }
        
        if (!oct2_Read())
        {
            octave = 5;
            LED_amber1_Write(0);
            LED_amber2_Write(1);
            LED_amber3_Write(0);
            LED_amber4_Write(0);
        }
        if (!oct3_Read())
        {
            octave = 6;
            LED_amber1_Write(0);
            LED_amber2_Write(0);
            LED_amber3_Write(1);
            LED_amber4_Write(0);            
        }
        if (!oct4_Read())
        {
            if (octave < 7)
            {
                octave = 7;

            }
            else if ((oct4Up) && (octave < 11))
            {
                octave++;

            }
            LED_amber1_Write(0);
            LED_amber2_Write(0);
            LED_amber3_Write(0);
            LED_amber4_Write(1);
            oct4Up = 0;
        }
        
        else if (oct4_Read())
        {
            oct4Up = 1;
        }
        
        if (!neck1_button_Read())
        {
            currentNeck = 0;
            currentCopedent = necks[currentNeck];
            LED_red1_Write(0);
            LED_green2_Write(1);
            displayCurrentPresetNameAndCopedent();
        }
        if (!neck2_button_Read())
        {
            currentNeck = 1;
            currentCopedent = necks[currentNeck];            
            LED_red1_Write(1);
            LED_green2_Write(0);          
            displayCurrentPresetNameAndCopedent();
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
        
        
        if (!editMode)
        {
        
            if ((!button1_Read()) && (button1Up))
            {
                currentCopedent -= 1;
                currentCopedent &= 31;
                necks[currentNeck] = currentCopedent;
                EEPROM_WriteByte(currentCopedent, EEPROM_NECKS_OFFSET + currentNeck);
                displayCurrentPresetNameAndCopedent();
                button1Up = 0;
            }
            else if (button1_Read())
            {
                button1Up = 1;
            }
            
            if ((!button2_Read()) && (button2Up))
            {
                currentCopedent += 1;
                currentCopedent &= 31;
                necks[currentNeck] = currentCopedent;
                EEPROM_WriteByte(currentCopedent, EEPROM_NECKS_OFFSET + currentNeck);
                
                displayCurrentPresetNameAndCopedent();
                button2Up = 0;
            }
            else if (button2_Read())
            {
                button2Up = 1;
            }
            
            if ((!button3_Read()) && (button3Up))
            {
                patchNum -= 1;
                patchNum &= 63;
                displayCurrentPresetNameAndCopedent();
                button3Up = 0;
            }
            else if (button3_Read())
            {
                button3Up = 1;
            }
            
            if ((!button4_Read()) && (button4Up))
            {
                patchNum += 1;
                patchNum &= 63;
                displayCurrentPresetNameAndCopedent();
                button4Up = 0;
            }
            else if (button4_Read())
            {
                button4Up = 1;
            }
        }
        //if in edit mode, then /left right up down work differently
        else
        {
        
            if ((!button1_Read()) && (button1Up))
            {
                currentCopedent -= 1;
                currentCopedent &= 31;
                necks[currentNeck] = currentCopedent;
                EEPROM_WriteByte(currentCopedent, EEPROM_NECKS_OFFSET + currentNeck);
                displayCurrentPresetNameAndCopedent();
                button1Up = 0;
            }
            else if (button1_Read())
            {
                button1Up = 1;
            }
            
            if ((!button2_Read()) && (button2Up))
            {
                currentCopedent += 1;
                currentCopedent &= 31;
                necks[currentNeck] = currentCopedent;
                EEPROM_WriteByte(currentCopedent, EEPROM_NECKS_OFFSET + currentNeck);
                displayCurrentPresetNameAndCopedent();  
                button2Up = 0;
            }
            else if (button2_Read())
            {
                button2Up = 1;
            }
            
            if ((!button3_Read()) && (button3Up))
            {
                patchNum -= 1;
                patchNum &= 63;
                displayCurrentPresetNameAndCopedent();
                button3Up = 0;
            }
            else if (button3_Read())
            {
                button3Up = 1;
            }
            
            if ((!button4_Read()) && (button4Up))
            {
                patchNum += 1;
                patchNum &= 63;
                displayCurrentPresetNameAndCopedent();
                button4Up = 0;
            }
            else if (button4_Read())
            {
                button4Up = 1;
            }
        }
        if (((!edit_button_Read() && !encoder_button_Read()) && (editUp)) || ((!edit_button_Read() && editMode) && (editUp)))
        {
            editMode = !editMode;
            //for now edit mode is calibration mode
            calibrationMode = !calibrationMode;
            LED_red2_Write(editMode);
            editUp = 0;
            if (editMode)
            {
                //#if 0
                OLEDclear(128, 64);
        
                myGFX_setFont(0);
                
                OLEDwriteString("CALIBRATION", 11, 1, FirstLine);
                OLEDwriteString("MOVE PEDALS", 11, 1, SecondLine);
                OLEDwriteString("AND LEVERS", 11, 1, ThirdLine);
                OLEDwriteString("THEN EXIT", 11, 1, FourthLine);
                mainOLEDWaitingToSend = 1;
                               // #endif
                //entering calibration mode, clear the pedals low and high arrays
                for (int i = 0; i < 10; i++)
                {
                    pedals_low[i] = 4095;
                    pedals_high[i] = 0;
                }

            }
            else
            {
                //draw normal screen
                displayCurrentPresetNameAndCopedent();
                calculatePedalRatios();
                //now need to store this in EEPROM.                
                for (int i = 0; i < NUM_PEDALS; i++)
                {
                     EEPROM_WriteByte((pedals_low[i] >> 8), EEPROM_CALIBRATION_OFFSET + (i*4));
                     EEPROM_WriteByte((pedals_low[i] & 255), EEPROM_CALIBRATION_OFFSET + ((i*4) + 1));
                     EEPROM_WriteByte((pedals_high[i] >> 8), EEPROM_CALIBRATION_OFFSET + ((i*4) + 2));
                     EEPROM_WriteByte((pedals_high[i] & 255), EEPROM_CALIBRATION_OFFSET + ((i*4) + 3));
                }

                // also need to make this a little more hidden - maybe first edit then Enter?
            }
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
            knobs[i] = (ADC_SAR_Seq_1_GetResult16(i)/16);
            
            knobs[i] = 255 - knobs[i];
            knobs7bit[i] = knobs[i] >> 1;
            
            if (knobs7bit[i] != prevKnobs7bit[i])
            {
                sendMIDIControlChange(i+9, knobs7bit[i], 0);
            }
            prevKnobs7bit[i] = knobs7bit[i];
            
        }
        
        testpin4_Write(1);
        //calculate the pitch of each string based on the current Copedent
        for (int i = 0; i < numStrings; i++)
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
    		float tempMIDI = (copedent[necks[currentNeck]][0][i] +
                        (copedent[currentCopedent][4][i] * pedals_float[0]) +
                        (copedent[currentCopedent][5][i] * pedals_float[1]) +
                        (copedent[currentCopedent][6][i] * pedals_float[2]) +
                        (copedent[currentCopedent][7][i] * pedals_float[3]) +
                        (copedent[currentCopedent][8][i] * pedals_float[4]) +
                        (copedent[currentCopedent][10][i] * pedals_float[5]) +
                        (copedent[currentCopedent][9][i] * pedals_float[6]) +
                        (copedent[currentCopedent][3][i] * pedals_float[7]) +
                        (copedent[currentCopedent][1][i] * pedals_float[8]) +
                        (copedent[currentCopedent][2][i] * pedals_float[9]));

            
            float openStringMIDI  = copedent[currentCopedent][0][i];
            openStringMIDI_Int[i] = (int)openStringMIDI;
            
            float barMIDI = ftom((invStringMappedPositions[0]) * mtof(tempMIDI));
            
            float computerMIDIOffset = barMIDI - openStringMIDI_Int[i];// + stringOctave[i];
            
            float pitchBendAmount = (computerMIDIOffset * 170.6666666666667f) + 8192.0f;  // 14bit number divide by 2 for signed, then divided by 48 for 48 semitones up/down range
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
        testpin4_Write(0);
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
                //make sure previous SPI2 transmission has completed before transferring the remaining midi date
        while (0u == ((SPIM_1_ReadTxStatus() & SPIM_1_STS_SPI_DONE) || (SPIM_1_ReadTxStatus() & SPIM_1_STS_SPI_IDLE )))
        {
            ;
        }
        testpin6_Write(1);
        if (sendingMessage == 1) //sending synthesis preset to synth board
        {
            if (sendMessageEnd) //send end message
            {
                myArray[0] = 253;
                myArray[1] = presetNumberToWrite;
                currentPresetSelection = presetNumberToWrite;
                //display previous preset as loaded
                displayCurrentPresetNameAndCopedent();
                //OLED_invert(0);
                sendMessageEnd = 0;
                sendingMessage = 0;
                messageArraySendCount = 0;
                myArray[30] = 254;
                myArray[31] = 253;
                
            }
            else //send chunks
            {
                //send the next preset Chunkkkkk
                myArray[0] = 2;
                myArray[1] = presetNumberToWrite;
                for (uint i = 2 ; i < myBufferSize-2; i++)
                {
                    if (messageArraySendCount < messageArraySize)
                    {
                        myArray[i] = presetArray[messageArraySendCount++];
                    }
                    else
                    {
                        myArray[i] = 0xee; // preset end ack   - done, next send a message that s
                        sendMessageEnd = 1;
                    }
                }
                myArray[30] = 254;
                myArray[31] = 253;
            }    
        }
        
        else if (sendSingleParamUpdate)
        {
            myArray[0] = 6;
            myArray[1] = singleParamToUpdateHigh;
            myArray[2] = singleParamToUpdateLow;
            myArray[3] = singleParamValueHigh;
            myArray[4] = singleParamValueLow;
            myArray[30] = 254;
            myArray[31] = 253;
            sendSingleParamUpdate = 0;
        }
        else if (sendKnobs)
        {
            myArray[0] = 3; //sending knob stuff, not a preset send
            for (int i = 0; i < 8; i++)
            {
                myArray[i + 1] = macroKnobValues[i];
            }
            for (int i = 0; i < 4; i++)
            {
                myArray[i + 9] = knobs[i];
            }
            for (int i = 0; i < 10; i++)
            {
                myArray[i + 13] = pedals8bit[i];
            }
            myArray[24] = octave | (voice << 4) | (dualSlider << 5) | (neck << 6);
            myArray[25] = patchNum;
            myArray[26] = processed_volumePedal >> 8;
            myArray[27] = processed_volumePedal & 0xff;
            myArray[28] = bar[1] >> 8;
            myArray[29] = bar[1] & 0xff;
            myArray[30] = 254;
            myArray[31] = 253;
            
            
            sendKnobs = 0;
        }
        else
        {
            myArray[0] = 1; //sending normal pitch stuff, not a preset send
            for (int i = 0; i < 12; i++)
            {
                int scaledMIDI = roundf(stringMIDI[i] * 512.0f); // divide by 128 multiply by 65535
                myArray[i * 2 + 1] = scaledMIDI >> 8;
                myArray[(i * 2) + 2] = scaledMIDI & 255;
            }
            
            myArray[24] = octave | (voice << 4) | (dualSlider << 5) | (neck << 6);
            myArray[25] = patchNum;
            myArray[26] = processed_volumePedal >> 8;
            myArray[27] = processed_volumePedal & 0xff;
            myArray[28] = bar[0] >> 8;
            myArray[29] = bar[0] & 0xff;
            myArray[30] = 254;
            myArray[31] = 253;
            
            sendKnobs = 1; // for next time around, might make this slower though
            /*
            for (int i = 0; i < 16; i++)
            {
                myArray[i+56] = encoderVal[i];
            }
            */
        }

        

/*
        for(int i = 0; i < myBufferSize; i++)
        {
            SPIM_1_WriteTxData(myArray[i]);
        }
    */    
        

       
        
        
        //parse input from synth board (names)
        if ((inBuffer[0] == 253) && (inBuffer[31] == 254))
        {
            int whichPresetToStoreName = inBuffer[1];
            int whichMacroToStoreName = inBuffer[16];
            int bufferPointer = 2;
            for (int i = 0; i < NAME_LENGTH_IN_BYTES; i++)
            {
                presetNamesArray[whichPresetToStoreName][i] = inBuffer[bufferPointer];
                bufferPointer++;
            }
            bufferPointer = 17;
            for (int i = 0; i < NAME_LENGTH_IN_BYTES; i++)
            {
                macroNamesArray[whichPresetToStoreName][whichMacroToStoreName][i] = inBuffer[bufferPointer];
                bufferPointer++;
            }
            if ((whichPresetToStoreName == patchNum) && (whichMacroToStoreName == 7) && (!presetAlreadyDisplayed[whichPresetToStoreName]))
            {
                displayCurrentPresetNameAndCopedent();
            }
        }
        
        SPIM_1_ClearRxBuffer();
        CyDmaChEnable(rx3Channel, STORE_TD_CFG_ONCMPLT);
        CyDmaChEnable(txChannel, STORE_TD_CFG_ONCMPLT);
        
        testpin6_Write(0);
       

     }
}

void DmaTxConfiguration()
{
    /* Init DMA, 1 byte bursts, each burst requires a request */ 
    txChannel = DMA_4_DmaInitialize(DMA_TX_BYTES_PER_BURST, DMA_TX_REQUEST_PER_BURST, 
                                        HI16(DMA_TX_SRC_BASE), HI16(DMA_TX_DST_BASE));

    txTD = CyDmaTdAllocate();

    /* Configure this Td as follows:
    *  - Increment the source address, but not the destination address   
    */
    CyDmaTdSetConfiguration(txTD, myBufferSize, CY_DMA_DISABLE_TD, TD_INC_SRC_ADR);

    /* From the memory to the SPIM */
    CyDmaTdSetAddress(txTD, LO16((uint32)myArray), LO16((uint32) SPIM_1_TXDATA_PTR));
    
    /* Associate the TD with the channel */
    CyDmaChSetInitialTd(txChannel, txTD); 
   
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
    
        /* Init DMA, 1 byte bursts, each burst requires a request */ 
    rx3Channel = DMA_3_DmaInitialize(DMA_RX_BYTES_PER_BURST, DMA_RX_REQUEST_PER_BURST,
                                     HI16(DMA_RX_SRC_BASE), HI16(DMA_RX_DST_BASE));

    rx3TD = CyDmaTdAllocate();
    
    /* Configure this Td as follows:
    *  - Increment the destination address, but not the source address
    */
    CyDmaTdSetConfiguration(rx3TD, myBufferSize, CY_DMA_DISABLE_TD, TD_INC_DST_ADR);

    /* From the SPIM to the memory */
    CyDmaTdSetAddress(rx3TD, LO16((uint32)SPIM_1_RXDATA_PTR), LO16((uint32)inBuffer));

    /* Associate the TD with the channel */
    CyDmaChSetInitialTd(rx3Channel, rx3TD);
}

uint8 I2C_MasterWriteBlocking(uint8 i2CAddr, uint16 nbytes, uint8_t mode)
{
    uint8 volatile status;
    uint8_t error = 0;
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
                    error = 1;
                }
                if (timeout == 0)
                {
                    status = I2C_1_MSTAT_ERR_XFER;
                    I2C_reset();
                    error = 1;
                }
                
                if (status == 0)
                {
                    status = I2C_1_MSTAT_ERR_XFER;
                    I2C_reset();
                    error = 1;
                }
                
            } while(((status & (I2C_1_MSTAT_WR_CMPLT | I2C_1_MSTAT_ERR_XFER)) == 0u) && (status != 0u) && (timeout>0));
        }
        else
        {
            /* translate from I2CM_MasterWriteBuf() error output to
            *  I2CM_MasterStatus() error output */
            status = I2C_1_MSTAT_ERR_XFER;
            I2C_reset();
            error = 1;
        } 
    }  
    if ((status & I2C_1_MSTAT_ERR_ADDR_NAK) || (status & I2C_1_MSTAT_ERR_XFER))
    {
        //mark that i2c destination to be skipped (likely unplugged) and reset the I2C module
        //i2c_skipped[main_counter] = 1;
        I2C_reset();
        error = 1;
    }
    return error;
}

uint8 I2C_MasterReadBlocking(uint8 i2CAddr, uint8 nbytes, uint8_t mode)
{
    uint8 volatile status;
    uint32_t timeout = 50000;
    uint8_t error = 0;
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
                    error = 1;
                }
                if (timeout == 0)
                {
                    status = I2C_1_MSTAT_ERR_XFER;
                    I2C_reset();
                    error = 1;
                }
            } while(((status & (I2C_1_MSTAT_RD_CMPLT | I2C_1_MSTAT_ERR_XFER)) == 0u) && (status != 0u) && (timeout>0));
        }
        else
        {
            /* translate from I2CM_MasterReadBuf() error output to
            *  I2CM_MasterStatus() error output */
            status = I2C_1_MSTAT_ERR_XFER;
            I2C_reset();
            error = 1;
        }
    }
    if ((status & I2C_1_MSTAT_ERR_ADDR_NAK) || (status & I2C_1_MSTAT_ERR_XFER))
    {
        //mark that i2c destination to be skipped (likely unplugged) and reset the I2C module
        //i2c_skipped[main_counter] = 1;
        I2C_reset();
        error = 1;
    }
    return error;
}

void I2C_reset(void)
{
  I2C_1_Stop();

  /* Disable/clear everything, then reinitialize. */

  I2C_1_CFG_REG = 0x00;  // NECESSARY to get MCSR to reset and clear BUS_BUSY bit.

  I2C_1_XCFG_REG = 0x00;  // not sure if necessary.

  I2C_1_initVar = 0;  // MUST BE SET TO ZERO to allow I2C_1_Start() to call I2C_1_Init()

  I2C_1_Start();
}

void displayCurrentPresetNameAndCopedent()
{
    if (macroNamesArray[patchNum][7][0] != 255) //don't display if the name data still hasn't been retrieved by the SPI bus (255 is invalid initial data)
    {
        OLEDclear(128, 64);
        
        myGFX_setFont(0);
        OLEDwriteInt(patchNum , 2, 0,FirstLine);
        //OLEDwriteString(" ", 1, OLEDgetCursor(), FirstLine);
        OLEDwriteString((char *)&presetNamesArray[patchNum][0], NAME_CLIPPED_LENGTH, 0, SecondLine);
        OLEDwriteInt(currentCopedent , 2, 0,FourthLine);
        OLEDwriteString(" ", 1, OLEDgetCursor(), FourthLine);
        OLEDwriteString((char *)&copedentNamesArray[currentCopedent][0], COPEDENT_NAME_CLIPPED_LENGTH, OLEDgetCursor(), FourthLine);
        mainOLEDWaitingToSend = 1;
        presetAlreadyDisplayed[patchNum] = 1;
        //and update the macro OLED screens
        whichMacro = 0;
        macroOLEDWaitingToSend = 1;
    }
}
    
void checkUSB_Vbus(void)
{
   if (USB_VBusPresent() == 0)
   {
       USB_Stop();
       USB_active = 0; 
   }
   else if (USB_active == 0 )
   {
       USB_Start(0u, USB_3V_OPERATION ); 
        while (0u == USB_GetConfiguration());
        USB_MIDI_EP_Init();
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

         /* Reinitialize after SET_CONFIGURATION or SET_INTERFACE Requests */
        if(USB_IsConfigurationChanged() != 0x00)
        {
            USB_LoadInEP(USB_midi_in_ep, USB_midiInBuffer,(uint16) USB_midiInPointer);
            //USB_LoadInEP(USB_midi_in_ep, USB_midiInBuffer, 64);
            USB_ReadOutEP(USB_midi_out_ep,USB_midiOutBuffer, 64);
                                             /* configuring the DMAs for the first time only, the data as soon as received
                                             in the EP buffer is Transferred by DMA to the buffer as defined here with no CPU intervention */
            USB_EnableOutEP(USB_midi_out_ep);       /* Note 3.*/
        }
        if ((USB_active) && (USB_VBusPresent()))
        {
            USB_MIDI_IN_Service();
        }



        if ((USB_active) && (USB_VBusPresent()))
        {
            USB_MIDI_OUT_Service();
        }
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
    
    /*
    float tempAmp = strings[string] * 1.5259021896696421759365224689097e-5f;//divide by 65535
    float v = 127.0f + (64.0f * log10f_fast(tempAmp));
    int vInt  = (int) (v*4.0f);
    if (vInt > 127)
    {
        vInt = 127;
    }
    */
    uint16_t velocity = strings[string];
    if (velocity > 0)
    {
        //velocity = (((sqrtf((float)velocity) * 0.00001525878903f) - .0239372430f) * 130.114584436252734f);
        float tempVel = (float)velocity;
        tempVel = tempVel * 0.00001525878903f;
        tempVel = sqrtf(tempVel);
        tempVel = tempVel - 0.0239372430f;
        tempVel = tempVel * 130.114584436252734f;
        velocity = (int)tempVel;
        

        if (velocity > 127)
        {
            velocity = 127;
        }
        
        //only update octave on note-ons
        //stringOctave[string] = powf(2.0f,octave);
        int noteToSend = ((octave - 4) * 12) + openStringMIDI_Int[string];
        sendMIDINoteOn(noteToSend , ((uint8_t)velocity), string+1);
        prevNotes[string] = noteToSend;
            
    }
    else
    {
        sendMIDINoteOn(prevNotes[string], 0, string+1);
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
        if ((USB_active) && (USB_VBusPresent()))
        {       
            USB_PutUsbMidiIn(3u, midiMsg, USB_MIDI_CABLE_00);
        }
    }
}




volatile uint8_t checkStatus = 0;
volatile uint16_t checkBase = 0;



int SPI_errors = 0;

void parseSysex(void)
{
    parsingSysex = 1;
    //0 = it's a preset
    if (sysexBuffer[0] == 0)
    {
        sysexMessageInProgress = 1; // set a flag that we've started a sysex preset transfer. May take multiple sysex parse calls on the chunks to complete
        currentFloat = 0;
        presetArraySection = presetName;
        presetNumberToWrite = sysexBuffer[1];
        presetArray[0] = sysexBuffer[2];
        presetArray[1] = sysexBuffer[3];
        presetArray[2] = sysexBuffer[4];
        presetArray[3] = sysexBuffer[5];
        
        union breakFloat theVal;
        uint32_t i = 6;
        uint8_t stoppingPoint = NAME_LENGTH_IN_BYTES+6;
        for (; i < stoppingPoint; i++)
        {
            presetArray[i-2] = sysexBuffer[i] & 127; // pass on the first 14 elements as 8-bit bytes (they are the chars for the name string)
            presetNamesArray[presetNumberToWrite][i-6] = sysexBuffer[i] & 127;
        }
        
        presetArraySection = macroNames;

        
        for (int j = 0; j < NUM_MACROS; j++)
        {
            for (int k = 0; k < NAME_LENGTH_IN_BYTES; k++)
            {
                presetArray[i-2] = sysexBuffer[i] & 127; // pass on the first 14 elements as 8-bit bytes (they are the chars for the name string)
                macroNamesArray[presetNumberToWrite][j][k] = sysexBuffer[i] & 127; // pass on the first 14 elements as 8-bit bytes (they are the chars for the name string)
                i++;
            }
        }
        
        uint16_t valsStart = 4 + NAME_LENGTH_IN_BYTES + (NAME_LENGTH_IN_BYTES * NUM_MACROS);
        
        presetArraySection = initialVals;
        
        for (; i < sysexPointer; i = i+5)
        {
            theVal.u32 = 0;
            theVal.u32 |= ((sysexBuffer[i] &15) << 28);
            theVal.u32 |= (sysexBuffer[i+1] << 21);
            theVal.u32 |= (sysexBuffer[i+2] << 14);
            theVal.u32 |= (sysexBuffer[i+3] << 7);
            theVal.u32 |= (sysexBuffer[i+4] & 127);
            testVal = theVal.f;
            if (presetArraySection == initialVals)
            {

                if (currentFloat == 0)
                {
                    valsCount = (uint16_t) theVal.f;
                    presetArray[valsStart + currentFloat++] = valsCount >> 8;
                    presetArray[valsStart + currentFloat++] = valsCount & 0xff;
                }
                else if (currentFloat < ((valsCount+1)*2))
                { 
                    uint16_t intVal = (uint16_t)(theVal.f * 65535.0f);
                    presetArray[valsStart + currentFloat++] = intVal >> 8;
                    presetArray[valsStart + currentFloat++] = intVal & 0xff;
                }
                else if (currentFloat == ((valsCount+1)*2))
                {
                    valCheck = theVal.f;
                    if ((valCheck < -1.5f) && (valCheck > -2.5f))
                    {
                        presetArray[valsStart + currentFloat++] = 0xef;
                        presetArray[valsStart + currentFloat++] = 0xef;
                        presetArraySection = mapCountNext;
                        mapCount = 0;
                    }
                    else
                    {
                        //error state
                        SPI_errors++;
                        sysexMessageInProgress = 0;
                        sysexPointer = 0;
                        sendingMessage = 0;
                        parseThatMF = 0;
                    }
                }
            }
            else if (presetArraySection == mapCountNext)
            {
                mapCountExpectation = (uint16_t)theVal.f;
                presetArray[valsStart + currentFloat++] = mapCountExpectation >> 8;
                presetArray[valsStart + currentFloat++] = mapCountExpectation & 0xff;
                presetArraySection = mapping;
                numMappings = 0;
            }
            else if (presetArraySection == mapping)
            {
                // this is the order
                // source (int), target (int), scalarSource (arrives as -1.0f if no scalar, send as 255 if no scalar)(int), range (float -1.0 to 1.0)
                if (numMappings < mapCountExpectation)
                {
                    if ((mapCount % 4) == 0)
                    {
                        presetArray[valsStart + currentFloat++] = (uint8_t)theVal.f;
                    }
                    else if  (mapCount % 4 == 1)
                    {
                        presetArray[valsStart + currentFloat++] = (uint8_t)theVal.f;
                    }
                    else if (mapCount % 4 == 2) //check if the scalar source is -1 (if so send 255 instead of a valid source number)
                    {
                        if (theVal.f < 0.0f)
                        {
                             presetArray[valsStart + currentFloat++] = 0xff;
                        }
                        else
                        {
                             presetArray[valsStart + currentFloat++] = (uint8_t)theVal.f;
                        }
                    }
                    else
                    {
                        int16_t intVal = (int16_t)(theVal.f * 32767.0f); //keep it signed to allow negative numbers
                        presetArray[valsStart + currentFloat++] = intVal >> 8;
                        presetArray[valsStart + currentFloat++] = intVal & 0xff;
                        numMappings++;
                    }
                    mapCount++;
                }
                

                else
                {
                    //mapcount ended
                    if ((theVal.f < -2.5f) && (theVal.f > -3.5f))
                    {
                        presetArray[valsStart + currentFloat++] = 0xfe;
                        presetArray[valsStart + currentFloat++] = 0xfe;
                        presetArraySection = presetEnd;
                        sysexMessageInProgress = 0;
                        sendingMessage = 1;
                        patchNum = presetNumberToWrite;
                        messageArraySize = valsStart + currentFloat;
                    }
                    else
                    {
                        //error state
                        SPI_errors++;
                        sysexMessageInProgress = 0;
                        sysexPointer = 0;
                        sendingMessage = 0;
                        parseThatMF = 0;
                    }
                }
            }
            
        }
    }
    #if 0
    else if (sysexBuffer[0] == 1) //its a tuning
    {
        
        sysexMessageInProgress = 1; // set a flag that we've started a sysex preset transfer. May take multiple sysex parse calls on the chunks to complete
        currentFloat = 0;
        presetNumberToWrite = sysexBuffer[1];
        union breakFloat theVal;
        for (uint32_t i = 2; i < sysexPointer; i = i+5)
        {
            theVal.u32 = 0;
            theVal.u32 |= ((sysexBuffer[i] &15) << 28);
            theVal.u32 |= (sysexBuffer[i+1] << 21);
            theVal.u32 |= (sysexBuffer[i+2] << 14);
            theVal.u32 |= (sysexBuffer[i+3] << 7);
            theVal.u32 |= (sysexBuffer[i+4] & 127);
            testVal = theVal.f;
            uint16_t intVal = (uint16_t)(theVal.f * 512.0f);//(uint16_t)(theVal.f * 65535.0f);
            tuningArray[currentFloat++] = intVal >> 8;
            tuningArray[currentFloat++] = intVal & 0xff;
        }
        
        tuningArray[currentFloat++] = 0xef;
        tuningArray[currentFloat++] = 0xef;
                        
        
        messageArraySize = currentFloat;
                    
        if(messageArraySize != TUNING_ARRAY_SIZE)
        {
            //error state
            SPI_errors++;
            sysexMessageInProgress = 0;
            sysexPointer = 0;
            sendingMessage = 0;
            parseThatMF = 0;
        } else 
        {
            sysexMessageInProgress = 0;
            sendingMessage = 2;
        }
    }
    #endif
    

    
    else if (sysexBuffer[0] == 2) //its a copedent
    {
        sysexMessageInProgress = 1; // set a flag that we've started a sysex preset transfer. May take multiple sysex parse calls on the chunks to complete
        currentFloat = 0;
        copedentNumberToWrite = sysexBuffer[1];
        currentCopedent = copedentNumberToWrite;
        necks[currentNeck] = currentCopedent;

              
        
        union breakFloat theVal;
        uint32_t i = 2;
        uint8_t stoppingPoint = NAME_LENGTH_IN_BYTES+2;
        for (; i < stoppingPoint; i++)
        {
            //presetArray[i-2] = sysexBuffer[i] & 127; // pass on the first 14 elements as 8-bit bytes (they are the chars for the name string)
            uint8_t tempChar = sysexBuffer[i] & 127;
            copedentNamesArray[copedentNumberToWrite][i-2] = tempChar;
            checkBase = EEPROM_COPEDENT_OFFSET + (COPEDENT_SIZE_IN_BYTES * copedentNumberToWrite);
            checkStatus = EEPROM_WriteByte(tempChar, EEPROM_COPEDENT_OFFSET + (i - 2) + (COPEDENT_SIZE_IN_BYTES * copedentNumberToWrite));
        }
        
        i = NAME_LENGTH_IN_BYTES + 2; // start after the name storage to store the actual values

 
        while(i < sysexPointer)
        {
            for (uint32_t pedalToWrite = 0; pedalToWrite < 11; pedalToWrite++)
            {
                uint16_t pedalStartLoc = (pedalToWrite * 24);
                for (uint32_t stringChange = 0; stringChange < 12; stringChange++)
                {
                    
                    theVal.u32 = 0;
                    theVal.u32 |= ((sysexBuffer[i] &15) << 28);
                    theVal.u32 |= (sysexBuffer[i+1] << 21);
                    theVal.u32 |= (sysexBuffer[i+2] << 14);
                    theVal.u32 |= (sysexBuffer[i+3] << 7);
                    theVal.u32 |= (sysexBuffer[i+4] & 127);
                    copedent[copedentNumberToWrite][pedalToWrite][stringChange] = theVal.f;
                    uint16_t tempIntVersion = (uint16_t)((theVal.f * 256.0f) + 32768.0f);
                    uint8_t tempHigh = tempIntVersion >> 8;
                    uint8_t tempLow = tempIntVersion & 255;
                    
                    
                    uint16_t stringStartLoc = stringChange * 2;
                    checkBase = EEPROM_COPEDENT_OFFSET + stringStartLoc + pedalStartLoc + (COPEDENT_SIZE_IN_BYTES * copedentNumberToWrite) + NAME_LENGTH_IN_BYTES;
                    checkStatus = EEPROM_WriteByte(tempHigh, checkBase);
                    checkStatus = EEPROM_WriteByte(tempLow, checkBase + 1);
                    currentFloat++;
                    i = i+5;
                }
                
            }
        }
                        
        
        messageArraySize = currentFloat;
                    
        if(messageArraySize != COPEDENT_SIZE_IN_FLOATS)
        {
            //error state
            SPI_errors++;
            sysexMessageInProgress = 0;
            sysexPointer = 0;
            sendingMessage = 0;
            parseThatMF = 0;
        } 
        else 
        {
            sysexMessageInProgress = 0;
            //sendingMessage = 2;  // use this when we are ready to send copedents to the sd cards too
            
            displayCurrentPresetNameAndCopedent();
        }
    }
    
    
    else if (sysexBuffer[0] == 3) //it's a real-time parameter change
    {
        sysexMessageInProgress = 1; // set a flag that we've started a sysex preset transfer. May take multiple sysex parse calls on the chunks to complete
        union breakFloat theVal;
        uint32_t i = 2;
        
        //get the parameter ID
        theVal.u32 = 0;
        theVal.u32 |= ((sysexBuffer[i] &15) << 28);
        theVal.u32 |= (sysexBuffer[i+1] << 21);
        theVal.u32 |= (sysexBuffer[i+2] << 14);
        theVal.u32 |= (sysexBuffer[i+3] << 7);
        theVal.u32 |= (sysexBuffer[i+4] & 127);
        uint16_t roundedIndex = (uint16_t)roundf(theVal.f);
        singleParamToUpdateHigh = (roundedIndex << 8);
        singleParamToUpdateLow = roundedIndex & 0xff;
        
        i = i+5;
        
        //get the parameter value
        theVal.u32 = 0;
        theVal.u32 |= ((sysexBuffer[i] &15) << 28);
        theVal.u32 |= (sysexBuffer[i+1] << 21);
        theVal.u32 |= (sysexBuffer[i+2] << 14);
        theVal.u32 |= (sysexBuffer[i+3] << 7);
        theVal.u32 |= (sysexBuffer[i+4] & 127);
        
        uint16_t intVal = (uint16_t)(theVal.f * 65535.0f);
        singleParamValueHigh = intVal >> 8;
        singleParamValueLow = intVal & 0xff;
        
        sysexMessageInProgress = 0;
        sendSingleParamUpdate = 1;
    }

    parsingSysex = 0;
    sysexPointer = 0;
    parseThatMF = 0;
}

volatile uint8_t tempMIDI[4];
volatile uint8_t firstSysex = 0;
const uint16_t sysexPointerMask = 2047;
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
        if (receivingSysex)
        {
            for (int i = 0; i < 3; i++)
            {
                if (midiMsg[i] < 128)
                {
                    sysexBuffer[(sysexPointer++) & sysexPointerMask] = midiMsg[i];
                }
                else
                {
                    if (midiMsg[i] == USB_MIDI_EOSEX)
                    {
                        receivingSysex = 0;
                        //parseSysex();
                        return;
                     }
                }
            }
        }
        else if (midiMsg[USB_EVENT_BYTE0] == USB_MIDI_SYSEX)
        {
            if (!parsingSysex)
            {
                if (midiMsg[1] == 126) // special message saying that sysex multi-chunk transmission is finished. Parse it!
                {
                    parseThatMF = 1;

                    //sysexPointer = 0;
                }
                else if (midiMsg[1] == 0 || midiMsg[1] == 1 || midiMsg[1] == 2 || midiMsg[1] == 3)
                {
                    receivingSysex = 1;
                    
                    // if this is the first chunk, put in the first and second elements (following chunks need this data stripped until the final message gets sent)
                    if (sysexPointer == 0)
                    {
                        sysexBuffer[sysexPointer++ & sysexPointerMask] = midiMsg[1];
                        sysexBuffer[sysexPointer++ & sysexPointerMask] = midiMsg[2];
                    }
                }
            }
        }
        cable = cable; // so it doesn't complain about unused variables
    }
}    


/* [] END OF FILE */
