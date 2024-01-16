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
#include <device.h>
#include <stdio.h>
#include <math.h>


#define EEPROM_COPEDENT_OFFSET 0
#define COPEDENT_SIZE_IN_BYTES 274 //including name bytes
#define COPEDENT_SIZE_IN_FLOATS 132 // not including name bytes
#define PRESET_NAME_LENGTH_IN_BYTES 14
#define COPEDENT_NAME_LENGTH_IN_BYTES 10
#define NUM_FRET_MEASUREMENTS 12
#define NUM_SLIDERS 2
#define EEPROM_LEVER_CALIBRATION_OFFSET (EEPROM_COPEDENT_OFFSET + (MAX_NUM_COPEDENTS * COPEDENT_SIZE_IN_BYTES))
#define LEVER_CALIBRATION_SIZE_IN_BYTES (NUM_PEDALS * 4) //for each pedal, store 2 bytes for high and 2 bytes for low
#define EEPROM_FRET_CALIBRATION_OFFSET (EEPROM_LEVER_CALIBRATION_OFFSET + LEVER_CALIBRATION_SIZE_IN_BYTES)
#define FRET_CALIBRATION_SIZE_IN_BYTES NUM_FRET_MEASUREMENTS * NUM_SLIDERS * 2 //(measurement points *  2 sliders, each point 2 bytes)
#define EEPROM_CURRENT_PRESET_OFFSET EEPROM_FRET_CALIBRATION_OFFSET + FRET_CALIBRATION_SIZE_IN_BYTES  //2036
#define CURRENT_PRESET_SIZE_IN_BYTES 1
#define EEPROM_STRING_REP_OFFSET EEPROM_CURRENT_PRESET_OFFSET + CURRENT_PRESET_SIZE_IN_BYTES
#define STRING_REP_SIZE_IN_BYTES 1
#define EEPROM_TRANSPOSE_OFFSET EEPROM_STRING_REP_OFFSET + STRING_REP_SIZE_IN_BYTES
#define TRANSPOSE_SIZE_IN_BYTES 2
#define EEPROM_OCTAVE_ACTION_OFFSET EEPROM_TRANSPOSE_OFFSET + TRANSPOSE_SIZE_IN_BYTES
#define OCTAVE_ACTION_SIZE_IN_BYTES 1
#define EEPROM_DEADZONES_OFFSET EEPROM_OCTAVE_ACTION_OFFSET + OCTAVE_ACTION_SIZE_IN_BYTES
#define DEADZONES_SIZE_IN_BYTES 1
#define EEPROM_PITCHSMOOTHING_OFFSET EEPROM_DEADZONES_OFFSET + DEADZONES_SIZE_IN_BYTES
#define PITCHSMOOTHING_SIZE_IN_BYTES 1
#define EEPROM_CONTROLSMOOTHING_OFFSET EEPROM_PITCHSMOOTHING_OFFSET + PITCHSMOOTHING_SIZE_IN_BYTES
#define CONTROLSMOOTHING_SIZE_IN_BYTES 1
#define EEPROM_MIDI_SEND_OFFSET EEPROM_CONTROLSMOOTHING_OFFSET + CONTROLSMOOTHING_SIZE_IN_BYTES
#define MIDI_SEND_SIZE_IN_BYTES 1
#define EEPROM_PEDAL_INVERTED_OFFSET EEPROM_MIDI_SEND_OFFSET + MIDI_SEND_SIZE_IN_BYTES
#define PEDAL_INVERTED_SIZE_IN_BYTES 2
#define EEPROM_DUAL_SLIDER_OFFSET EEPROM_PEDAL_INVERTED_OFFSET + PEDAL_INVERTED_SIZE_IN_BYTES
#define DUAL_SLIDER_SIZE_IN_BYTES 1
#define EEPROM_NECKS_OFFSET EEPROM_DUAL_SLIDER_OFFSET + DUAL_SLIDER_SIZE_IN_BYTES
#define NECKS_SIZE_IN_BYTES 1
#define EEPROM_VOLUME_OFFSET EEPROM_NECKS_OFFSET + NECKS_SIZE_IN_BYTES
#define VOLUME_SIZE_IN_BYTES 1



#define PRESET_NAME_CLIPPED_LENGTH 12
#define COPEDENT_NAME_CLIPPED_LENGTH 10
#define MACRO_NAME_CLIPPED_LENGTH 9
#define CONTROL_NAME_CLIPPED_LENGTH 10

#define myBufferSize 32
#define MAX_NUM_COPEDENTS 7
#define NUM_STRINGS 12
#define NUM_PEDALS 10
#define INV_440 0.0022727272727273f

#define NUM_MACRO_PAGES 2
#define NUM_MACROS 8
#define NUM_CONTROLS 4
#define MACRO_NAME_LENGTH_IN_BYTES 9
#define CONTROL_NAME_LENGTH_IN_BYTES 10

#define MAX_NUM_PRESETS 64

//log10f is exactly log2(x)/log2(10.0f)
#define log10f_fast(x)  (log2f_approx(x)*0.3010299956639812f)

/* DMA Configuration for DMA_RX */
#define DMA_RX_BYTES_PER_BURST      (1u)
#define DMA_RX_REQUEST_PER_BURST    (1u)
#define DMA_RX_SRC_BASE             (CYDEV_PERIPH_BASE)


#define DMA_RX_DST_BASE             (CYDEV_SRAM_BASE)
/* DMA Configuration for DMA_TX */
#define DMA_TX_BYTES_PER_BURST      (1u)
#define DMA_TX_REQUEST_PER_BURST    (1u)
#define DMA_TX_SRC_BASE             (CYDEV_SRAM_BASE)
#define DMA_TX_DST_BASE             (CYDEV_PERIPH_BASE)

#define PLUCK_BUFFER_SIZE                 (32u)
#define BAR_BUFFER_SIZE                 (8u)
#define STORE_TD_CFG_ONCMPLT        (1u)


extern volatile uint8_t I2Cbuff1[256];
extern int octave;
extern uint8_t currentNeck;
extern uint8_t currentCopedent;
extern uint8_t mainOLEDWaitingToSend;
extern uint8_t volumeWaitingToSend;
extern uint8_t macroOLEDWaitingToSend;
extern uint8_t neckByte;
extern uint8_t necks[2];
extern uint8_t editMode;
extern uint8_t macroNamesArray[MAX_NUM_PRESETS][NUM_MACROS*NUM_MACRO_PAGES][MACRO_NAME_LENGTH_IN_BYTES];
extern uint8_t controlNamesArray[MAX_NUM_PRESETS][NUM_CONTROLS][CONTROL_NAME_LENGTH_IN_BYTES];
extern uint8_t patchNum;
extern uint8_t currentPresetSelection;
extern uint8_t presetNamesArray[MAX_NUM_PRESETS][PRESET_NAME_LENGTH_IN_BYTES];
extern uint8_t presetNumberToLoad;
extern uint8_t copedentNamesArray[MAX_NUM_COPEDENTS][COPEDENT_NAME_LENGTH_IN_BYTES];
extern uint8_t presetAlreadyDisplayed[MAX_NUM_PRESETS];
extern uint8_t whichMacro;
extern uint8_t fretCalibrationMode;
extern uint8_t leverCalibrationMode;
extern uint16_t fretMeasurements[NUM_SLIDERS][NUM_FRET_MEASUREMENTS];
extern uint16_t pedals_low[NUM_PEDALS];
extern uint16_t pedals_high[NUM_PEDALS];
extern uint8_t pedal_inverted[NUM_PEDALS];
extern uint16_t angle[NUM_PEDALS];
extern volatile uint16_t bar[NUM_SLIDERS];
extern int8_t transposeSemitones;
extern int8_t transposeCents;
extern float transposeFloat;
extern int8_t volumeInt;
extern int prevOctave;
extern uint8_t dualSlider;
extern uint8_t deadZone;
extern uint8_t stringRepresentation[NUM_SLIDERS];
extern uint8_t octaveAction;
extern uint8_t midiSendOn;
extern uint8_t midiBarSendOn;
extern uint8_t sendFirmwareUpdateRequest;
extern uint8_t knobFrozen[NUM_MACROS*NUM_MACRO_PAGES];
extern int16_t prevMacroKnobValues[NUM_MACROS*NUM_MACRO_PAGES];
extern uint8_t presetNumberToStore;
extern uint8_t sendLocalPresetStoreCommand;
extern char newPresetName[14];

typedef enum _MenuModes
{
	MainMenu = 0,
    StorePresetMenu,
    CalibrationMenu,
    SettingsMenu,
	CalibrateLeversMenu,
	CalibrateFretsMenu,
    TransposeMenu,
    OctaveActionMenu,
    DeadzonesMenu,
    SliderRepMenu,
    MidiSendMenu,
    VolumeMenu,
    FirmwareUpdateMenu,
	NilMenu
} MenuModes;

typedef enum _presetArraySectionState
{
    presetName = 0,
    macroNames = 1,
    initialVals = 2,
    mapCountNext = 3,
    mapping = 4,
    presetEnd = 5,
} presetArraySectionState;

uint8 I2C_MasterWriteBlocking(uint8 i2CAddr, uint16 nbytes, uint8_t mode);
void calculatePedalRatios(void);
void calculateStringRepDivider(void);


/* [] END OF FILE */
