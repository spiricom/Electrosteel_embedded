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

#include "main.h"
#include "ui.h"

int8_t prevEncoderVal = 0;
uint8_t encoderWatch = 0;
//signed so that we can check if it goes below zero
int8_t menuPosition[3][2];
enum direction{Left, Right, Down, Up, Enter};
uint8_t semitonesOrCents = 0;
uint8_t editUp = 1;
uint8_t oct1Up = 1;
uint8_t oct4Up = 1;
uint8_t encoderUp = 1;
uint8_t button1Up = 1;
uint8_t button2Up = 1;
uint8_t button3Up = 1;
uint8_t button4Up = 1;
uint8_t shiftUp = 1;
uint8_t editingSliderRepString = 0;
uint8_t whichMidiSendSelected = 0;

void scanUI(void)
{
    uint8_t tempButtons = Status_Reg_1_Read();
    if (!(tempButtons&(1<<4)))
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
    
    else if ((tempButtons&(1<<4)))
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
    if (!(tempButtons&(1<<5)))
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
    
    else if ((tempButtons&(1<<5)))
    {
        oct4Up = 1;
    }
    
    if (!neck1_button_Read())
    {
        currentNeck = 0;
        currentCopedent = necks[currentNeck];
        neckByte = (necks[0]<<5) + (necks[1]<<2) + currentNeck;
        EEPROM_WriteByte(neckByte, EEPROM_NECKS_OFFSET);
        LED_red1_Write(0);
        LED_green2_Write(1);
        if (!editMode)
        {
            displayCurrentPresetNameAndCopedent();
        }
        else
        {
            exitEditModeMenu();   
        }
    }
    if (!neck2_button_Read())
    {
        currentNeck = 1;
        currentCopedent = necks[currentNeck];    
        neckByte = (necks[0]<<5) + (necks[1]<<2) + currentNeck;
        EEPROM_WriteByte(neckByte, EEPROM_NECKS_OFFSET);
        LED_red1_Write(1);
        LED_green2_Write(0);          
        if (!editMode)
        {
            displayCurrentPresetNameAndCopedent();
        }
        else
        {
            exitEditModeMenu();   
        }
    }
    
    if ((!(tempButtons&(1<<6))) && (shiftUp))
    {
        dualSlider = !dualSlider;
        LED_green1_Write(dualSlider);
        EEPROM_WriteByte(dualSlider, EEPROM_DUAL_SLIDER_OFFSET);
        shiftUp = 0;
    }
    else if ((tempButtons&(1<<6)))
    {
        shiftUp = 1;
    }

    if ((!(tempButtons&(1<<0))) && (button1Up))
    {
        leftPressed();
        button1Up = 0;
    }
    else if ((tempButtons&(1<<0)))
    {
        button1Up = 1;
    }
    
    if ((!(tempButtons&(1<<1))) && (button2Up))
    {
        rightPressed();
        button2Up = 0;
    }
    else if ((tempButtons&(1<<1)))
    {
        button2Up = 1;
    }
    
    if ((!(tempButtons&(1<<2))) && (button3Up))
    {
        downPressed();
        button3Up = 0;
    }
    else if ((tempButtons&(1<<2)))
    {
        button3Up = 1;
    }
    
    if ((!(tempButtons&(1<<3))) && (button4Up))
    {
        upPressed();
        button4Up = 0;
    }
    else if ((tempButtons&(1<<3)))
    {
        button4Up = 1;
    }
    
    if ((!edit_button_Read()) && (editUp))
    {
        editMode = !editMode;
        if (editMode)
        {
            enterEditModeMenu();
        }
        else
        {
            exitEditModeMenu();
        }
        editUp = 0;
    }
    else if (edit_button_Read())
    {
        editUp = 1;
    }
    
    if ((!(tempButtons&(1<<7))) && (encoderUp))
    {
        
    }
    else if ((tempButtons&(1<<7)))
    {
        encoderUp = 1;
    }
    
    prevOctave = octave;
    if (editMode)
    {
        if (encoderWatch)
        {
            int8_t currentEncoderVal = Decoder_1_GetPosition();
            if (menuPosition[0][0] == TransposeMenu) //editing transpose
            {
                if (prevEncoderVal != currentEncoderVal)
                {
                    OLEDtextColor(1, 0);
                    OLEDclearLine(ThirdLine);
                    OLEDclearLine(FourthLine);
                    float theMultiplier = 1.0f;
                    if (semitonesOrCents == 1)
                    {
                        theMultiplier = 0.01f;
                    }
                    myGFX_setFont(1);
                    transposeFloat = transposeFloat - (((float)Decoder_1_GetPosition()) * theMultiplier);
                    Decoder_1_SetPosition(0);
                    if (transposeFloat < -12.0)
                    {
                        transposeFloat = -12.0;
                    }
                    else if (transposeFloat > 12.0)
                    {
                        transposeFloat = 12.0;
                    }
                    float absTransposeFloat = transposeFloat;
                    GFXsetCursor(&theGFX, 20,53);
                    if (transposeFloat < 0.0f)
                    {
                        GFXwrite(&theGFX, 45);
                        absTransposeFloat = -absTransposeFloat;
                    }
                    else
                    {
                        GFXwrite(&theGFX, 32);
                    }
                    if (!semitonesOrCents)
                    {
                        OLEDtextColor(0, 1);
                        GFXfillRect(&theGFX, 32, 34, 30, 25, theGFX.textbgcolor);
                    }

                    uint8_t currentChar = ((uint8_t)(absTransposeFloat * 0.1f));  
                    absTransposeFloat -= currentChar * 10.0f;
                    GFXwrite(&theGFX, currentChar + 48);
                    currentChar = ((uint8_t)absTransposeFloat);    
                    GFXwrite(&theGFX, currentChar + 48);
                    OLEDtextColor(1, 0);

                    GFXwrite(&theGFX, 46); //decimal point
                    if (semitonesOrCents)
                    {
                        OLEDtextColor(0, 1);
                        GFXfillRect(&theGFX, 70, 34, 30, 25, theGFX.textbgcolor);
                    }
                    absTransposeFloat -= currentChar;
                    currentChar = ((uint8_t)(absTransposeFloat * 10.0f));    
                    GFXwrite(&theGFX, currentChar + 48);
                    absTransposeFloat -= (currentChar * 0.1f);
                    currentChar = ((uint8_t)(absTransposeFloat * 100.0f));    
                    GFXwrite(&theGFX, currentChar + 48);
                    OLEDtextColor(1, 0);
                    mainOLEDWaitingToSend = 1;
                }
            }
                
            if (menuPosition[0][0] == DeadzonesMenu) //editing deadzones
            {
                if (prevEncoderVal != currentEncoderVal)
                {
                    OLEDtextColor(1, 0);
                    OLEDclearLine(ThirdLine);
                    OLEDclearLine(FourthLine);
                    
                    myGFX_setFont(1);
                    int16_t deadZoneTemp = deadZone;
                    
                    deadZoneTemp = deadZoneTemp - Decoder_1_GetPosition();
                    Decoder_1_SetPosition(0);
                    if (deadZoneTemp < 0)
                    {
                        deadZone = 0;
                    }
                    else if (deadZoneTemp > 100)
                    {
                        deadZone = 100;
                    }
                    else 
                    {
                        deadZone = deadZoneTemp;
                    }
                    calculatePedalRatios();
                    GFXsetCursor(&theGFX, 30,53);
                    
                    float deadZoneRepresentation = (float)(deadZone) * 0.2f;
                    
                    uint8_t currentChar = ((uint8_t)(deadZoneRepresentation * 0.1f));  
                    deadZoneRepresentation -= currentChar * 10.0f;
                    GFXwrite(&theGFX, currentChar + 48);
                    currentChar = ((uint8_t)deadZoneRepresentation);    
                    GFXwrite(&theGFX, currentChar + 48);


                    GFXwrite(&theGFX, 46); //decimal point
                    
                    deadZoneRepresentation -= currentChar;
                    currentChar = ((uint8_t)(deadZoneRepresentation * 10.0f));    
                    GFXwrite(&theGFX, currentChar + 48);
                    deadZoneRepresentation -= (currentChar * 0.1f);
                    currentChar = ((uint8_t)(deadZoneRepresentation*100.0f));    
                    GFXwrite(&theGFX, currentChar + 48);
                    GFXwrite(&theGFX, 37); //percent symbol
                    OLEDtextColor(1, 0);
                    mainOLEDWaitingToSend = 1;
                }
            }
            if (menuPosition[0][0] == SliderRepMenu) //editing string/slider representation
            {
                if (prevEncoderVal != currentEncoderVal)
                {
                    OLEDtextColor(1, 0);

                    myGFX_setFont(2);

                    int16_t sliderTemp = stringRepresentation[editingSliderRepString];
                    sliderTemp = sliderTemp - Decoder_1_GetPosition();
                    Decoder_1_SetPosition(0);
                    if (sliderTemp < 0)
                    {
                         stringRepresentation[editingSliderRepString] = 0;
                    }
                    else if (sliderTemp > 9)
                    {
                         stringRepresentation[editingSliderRepString] = 9;
                    }
                    else 
                    {
                         stringRepresentation[editingSliderRepString] = sliderTemp;
                    }
                    
                    uint8_t sliderRepDisplay[2];
                    sliderRepDisplay[0] = stringRepresentation[0] + 1;
                    sliderRepDisplay[1] = stringRepresentation[1] + 1;
                    
                    OLEDwriteString("S1=", 3, 0, FourthLine);
                    if (!editingSliderRepString)
                    {
                        OLEDtextColor(0, 1);
                        GFXfillRect(&theGFX, 24, 48, 16, 16, theGFX.textbgcolor);
                    }
                    uint8_t currentChar = sliderRepDisplay[0] / 10;
                    GFXwrite(&theGFX, currentChar + 48);
                    currentChar = sliderRepDisplay[0] - (currentChar*10);
                    GFXwrite(&theGFX, currentChar + 48);
                    OLEDtextColor(1, 0);

                    GFXwrite(&theGFX, 32); //space
                    GFXwrite(&theGFX, 83); //S
                    GFXwrite(&theGFX, 50); //2
                    GFXwrite(&theGFX, 61); //=
                    if (editingSliderRepString)
                    {
                        OLEDtextColor(0, 1);
                        GFXfillRect(&theGFX, 72, 48, 16, 16, theGFX.textbgcolor);
                    }
                    currentChar = sliderRepDisplay[1] / 10;
                    GFXwrite(&theGFX, currentChar + 48);
                    currentChar = sliderRepDisplay[1]  - (currentChar*10);
                    GFXwrite(&theGFX, currentChar + 48);
                   
                    OLEDtextColor(1, 0);
                    mainOLEDWaitingToSend = 1;
                }
            }
            prevEncoderVal = currentEncoderVal;
        }
    }
    
}




const char* const calibrationNames[] = { "  SET LEVERS ", "  SET FRETS  ", 0 }; 
const char* const mainMenuNames[] =    { "  CALIBRATION", "  SETTINGS   ", 0 }; 
const char* const settingsNames[] =   { "  TRANSPOSE  ", "  OCTAVE ACTION", "  DEADZONES    ", "  SLIDER REPR ", "  SMOOTHING   ", "  MIDI SEND  ", 0 }; 
uint8_t numMainMenuItems = 2;
uint8_t numCalibrationItems = 2;
uint8_t numSettingsItems = 6;

void enterEditModeMenu(void)
{

    OLEDclear(128, 64);
    myGFX_setFont(2);
    OLEDtextColor(0, 1);
    OLEDwriteString("  CALIBRATION     ", 15, 0, FirstLine);
    OLEDwriteArrow(0, FirstLine);
    OLEDtextColor(1, 0);
    OLEDwriteString("  SETTINGS       ", 15, 0, SecondLine);
    OLEDtextColor(1, 0);
    mainOLEDWaitingToSend = 1;
    editMode = 1;
    LED_red2_Write(editMode);
    //initialize menu position to all zero
    menuPosition[0][0] = 0; //x
    menuPosition[0][1] = 0; //y
    menuPosition[1][0] = 0; //x
    menuPosition[1][1] = 0; //y
    menuPosition[2][0] = 0; //x
    menuPosition[2][1] = 0; //y
}

void exitEditModeMenu(void)
{
    
    if (leverCalibrationMode == 1)
    {
        exitLeverCalibrationMode();
    }
    if (fretCalibrationMode == 1)
    {
        exitFretCalibrationMode();
    }
    if (menuPosition[0][0] == TransposeMenu)
    {
        transposeSemitones = (int8_t)transposeFloat;
        transposeCents = (int8_t)((transposeFloat - transposeSemitones) * 100.0f);
        EEPROM_WriteByte(transposeSemitones, EEPROM_TRANSPOSE_OFFSET);
        EEPROM_WriteByte(transposeCents, EEPROM_TRANSPOSE_OFFSET + 1);
    }
    if (menuPosition[0][0] == DeadzonesMenu)
    {
        EEPROM_WriteByte(deadZone, EEPROM_DEADZONES_OFFSET);
    }
    if (menuPosition[0][0] == SliderRepMenu)
    {
        uint8_t tempByte = ((stringRepresentation[0] & 15) << 4) + (stringRepresentation[1] & 15);
        EEPROM_WriteByte(tempByte,EEPROM_STRING_REP_OFFSET);
        calculateStringRepDivider();
    }
    if (menuPosition[0][0] == MidiSendMenu)
    {
        uint8_t tempByte = ((midiBarSendOn & 1)<<1) + (midiSendOn & 1);
        EEPROM_WriteByte(tempByte,EEPROM_MIDI_SEND_OFFSET);
    }
    
    encoderWatch = 0;
    Decoder_1_Stop();
    editMode = 0;
    LED_red2_Write(editMode);
    displayCurrentPresetNameAndCopedent();
}

uint8_t fretToCalibrate = 0;
uint8_t whichFretArray[NUM_FRET_MEASUREMENTS] = {0, 1, 3, 5, 7, 9, 12, 15, 17, 19, 21, 24};
void menuAction(enum direction action)
{
    uint8_t whatToDraw = 0;
    
    if (menuPosition[0][0] == MainMenu) //we are at the main menu
    {
        //if we went up or down, switch the menu item
        if (action == Up)
        {
            menuPosition[0][1]--;
            if (menuPosition[0][1] < 0)
            {
                menuPosition[0][1] = 0;
            }
            whatToDraw = 1;
        }
        else if (action == Down)
        {
            menuPosition[0][1]++;
            if (menuPosition[0][1] >= numMainMenuItems)
            {
                menuPosition[0][1] = numMainMenuItems-1;
            }
            whatToDraw = 1;
        }
        else if ((action == Right) || (action == Enter))
        {
            //select this submenu from the main menu
            menuPosition[0][0] = menuPosition[0][1]+1; //now [0][0] = 1 means calibration and [0][0] = 2 means settings
            whatToDraw = menuPosition[0][0]+1;
        }
        //ignore left button
    }
    else if (menuPosition[0][0] == CalibrationMenu) //we are at the calibration submenu
    {
        //if we went up or down, switch the menu item
        if (action == Up)
        {
            menuPosition[1][1]--;
            if (menuPosition[1][1] < 0)
            {
                menuPosition[1][1] = 0;
            }
            whatToDraw = 2;
        }
        else if (action == Down)
        {
            menuPosition[1][1]++;
            if (menuPosition[1][1] >= numCalibrationItems)
            {
                menuPosition[1][1] = numCalibrationItems-1;
            }
            whatToDraw = 2;
        }
        else if ((action == Right) || (action == Enter))
        {
            if (menuPosition[1][1] == 0)
            {
                //calibrate levers
                menuPosition[0][0] = CalibrateLeversMenu; //means calibrating levers now
                whatToDraw = 0;
                enterLeverCalibrationMode();
            }
            else if (menuPosition[1][1] == 1)
            {
                //calibrate bar slider frets
                menuPosition[0][0] = CalibrateFretsMenu; //means calibrating frets now
                whatToDraw = 0;
                enterFretCalibrationMode();
            }
        }
        else if (action == Left) 
        {
            //go back to main menu
            menuPosition[0][0] = 0;
            whatToDraw = 1;
        }
    }
    else if (menuPosition[0][0] == SettingsMenu) //we are at the settings submenu
    {
        //if we went up or down, switch the menu item
        if (action == Up)
        {
            menuPosition[2][1]--;
            if (menuPosition[2][1] < 0)
            {
                menuPosition[2][1] = 0;
            }
            whatToDraw = 3;
        }
        else if (action == Down)
        {
            menuPosition[2][1]++;
            if (menuPosition[2][1] >= numSettingsItems)
            {
                menuPosition[2][1] = numSettingsItems-1;
            }
            whatToDraw = 3;
        }
        else if ((action == Right) || (action == Enter))
        {
            if (menuPosition[2][1] == 0)
            {
                //transpose
                menuPosition[0][0] = TransposeMenu;
                Decoder_1_Start();
                whatToDraw = 0;
                encoderWatch = 1;
                OLEDclear(128, 64);
                myGFX_setFont(2);
                OLEDtextColor(1, 0);
                OLEDwriteString("VALUE KNOB SETS", 15, 0, FirstLine);
                OLEDwriteString("TRANSPOSITION  ", 15, 0, SecondLine);
                prevEncoderVal = 127;
                Decoder_1_SetPosition(0);
                mainOLEDWaitingToSend = 1;
            }
            else if (menuPosition[2][1] == 1)
            {
                //octave action setting
                menuPosition[0][0] = OctaveActionMenu;
                whatToDraw = 0;
                OLEDclear(128, 64);
                myGFX_setFont(2);
                OLEDtextColor(1, 0);
                OLEDwriteString("OCTAVE ACTION  ", 15, 0, FirstLine);
                OLEDtextColor(octaveAction, !octaveAction);
                OLEDwriteString("ON NEXT NOTE   ", 15, 0, SecondLine);
                OLEDtextColor(!octaveAction, octaveAction);
                OLEDwriteString("IMMEDIATE      ", 15, 0, ThirdLine);
                OLEDtextColor(1, 0);
                mainOLEDWaitingToSend = 1;
            }
            else if (menuPosition[2][1] == 2)
            {
                //dead zone setting
                menuPosition[0][0] = DeadzonesMenu;
                Decoder_1_Start();
                whatToDraw = 0;
                encoderWatch = 1;
                OLEDclear(128, 64);
                myGFX_setFont(2);
                OLEDtextColor(1, 0);
                OLEDwriteString("VALUE KNOB SETS", 15, 0, FirstLine);
                OLEDwriteString("LEVER DEADZONES", 15, 0, SecondLine);
                prevEncoderVal = 127;
                Decoder_1_SetPosition(0);
                mainOLEDWaitingToSend = 1;
            }
            else if (menuPosition[2][1] == 3)
            {
                //dead zone setting
                menuPosition[0][0] = SliderRepMenu;
                Decoder_1_Start();
                whatToDraw = 0;
                encoderWatch = 1;
                OLEDclear(128, 64);
                myGFX_setFont(2);
                OLEDtextColor(1, 0);
                OLEDwriteString("SET WHICH      ", 15, 0, FirstLine);
                OLEDwriteString("STRINGS SLIDERS", 15, 0, SecondLine);
                OLEDwriteString("REPRESENT(1-10)", 15, 0, ThirdLine);
                prevEncoderVal = 127;
                Decoder_1_SetPosition(0);
                mainOLEDWaitingToSend = 1;
                editingSliderRepString = 0;
            }
            else if (menuPosition[2][1] == 5)
            {
                //midi send setting
                menuPosition[0][0] = MidiSendMenu;
                whatToDraw = 0;
                OLEDclear(128, 64);
                myGFX_setFont(2);
                OLEDtextColor(1, 0);
                OLEDwriteString("SEND MIDI ", 10, 0, FirstLine);
                GFXfillRect(&theGFX, 76, 0, 37, 16, !whichMidiSendSelected);
                OLEDtextColor(whichMidiSendSelected, !whichMidiSendSelected);
                if (midiSendOn)
                {
                    GFXwrite(&theGFX, 79);
                    GFXwrite(&theGFX, 78);
                }
                else
                {
                    GFXwrite(&theGFX, 79);
                    GFXwrite(&theGFX, 70);
                    GFXwrite(&theGFX, 70);
                }
                
                OLEDtextColor(1, 0);
                OLEDwriteString("SEND BAR  ", 10, 0, SecondLine);
                
                GFXfillRect(&theGFX, 76, 16, 37, 16, whichMidiSendSelected);
                OLEDtextColor(!whichMidiSendSelected, whichMidiSendSelected);
                if (midiBarSendOn)
                {
                    GFXwrite(&theGFX, 79);
                    GFXwrite(&theGFX, 78);
                }
                else
                {
                    GFXwrite(&theGFX, 79);
                    GFXwrite(&theGFX, 70);
                    GFXwrite(&theGFX, 70);
                }
                mainOLEDWaitingToSend = 1;
            }
        }
        else if (action == Left) 
        {
            //go back to main menu
            menuPosition[0][0] = MainMenu;
            whatToDraw = 1;
        }
    }
    
    else if (menuPosition[0][0] == CalibrateLeversMenu) //we are in lever calibration
    {
        if ((action == Right) || (action == Enter))
        {
            OLEDclear(128, 64);
            myGFX_setFont(2);
            OLEDtextColor(0, 1);
            OLEDwriteString("NOW PUT ALL", 11, 1, FirstLine);
            OLEDwriteString("PEDALS/LEVERS  ", 15, 1, SecondLine);
            OLEDwriteString("IN RESTING STATE", 16, 1, ThirdLine);
            OLEDwriteString("AND PRESS EDIT", 14, 1, FourthLine);
            mainOLEDWaitingToSend = 1;
            OLEDtextColor(1, 0);
        }
    }
    else if (menuPosition[0][0] == CalibrateFretsMenu) //we are in fret calibration
    {
        //when user presses -> button, then store the current fret and increment which fret to store next
        if ((action == Right) || (action == Enter))
        {
            fretMeasurements[0][fretToCalibrate] = bar[0];
            fretMeasurements[1][fretToCalibrate] = bar[1];
            fretToCalibrate++;
            if (fretToCalibrate == NUM_FRET_MEASUREMENTS)
            {
                exitFretCalibrationMode();
            }
            else
            {
               OLEDwriteInt(whichFretArray[fretToCalibrate], 2, 40, ThirdLine);
               mainOLEDWaitingToSend = 1;
            }
        }
    }
    else if (menuPosition[0][0] == TransposeMenu) //we are in transpose
    {
        
        if (action == Right)
        {
            semitonesOrCents = (semitonesOrCents+1)&1;
            prevEncoderVal = 127;
        }
        else if (action == Left)
        {
            semitonesOrCents = (semitonesOrCents-1)&1;
            prevEncoderVal = 127;
        }
    }
    else if (menuPosition[0][0] == OctaveActionMenu) //we are in octave action
    {
        
        if (action == Up)
        {
            octaveAction = (octaveAction+1)&1;
        }
        else if (action == Down)
        {
            octaveAction = (octaveAction-1)&1;
        }
        
         else if (action == Left) 
        {
            //go back to main menu
            menuPosition[0][0] = SettingsMenu;
            whatToDraw = 1;
        }
        
        myGFX_setFont(2);
        OLEDtextColor(1, 0);
        OLEDtextColor(octaveAction, !octaveAction);
        OLEDwriteString("ON NEXT NOTE   ", 15, 0, SecondLine);
        OLEDtextColor(!octaveAction, octaveAction);
        OLEDwriteString("IMMEDIATE      ", 15, 0, ThirdLine);
        OLEDtextColor(1, 0);
        mainOLEDWaitingToSend = 1;
    }

    else if (menuPosition[0][0] == SliderRepMenu) //we are in sliderRep
    {
       
        if (action == Right)
        {
            editingSliderRepString = (editingSliderRepString+1)&1;
            prevEncoderVal = 127;
        }
        else if (action == Left)
        {
            editingSliderRepString = (editingSliderRepString-1)&1;
            prevEncoderVal = 127;
        }
    }
    else if (menuPosition[0][0] == MidiSendMenu) //we are in midisend menu
    {
        
        if (action == Right)
        {
            if (!whichMidiSendSelected)
            {
                midiSendOn = (midiSendOn+1)&1;
            }
            else
            {
                midiBarSendOn = (midiBarSendOn+1)&1;
            }
        }
        else if (action == Left)
        {
            if (!whichMidiSendSelected)
            {
                midiSendOn = (midiSendOn-1)&1;
            }
            else
            {
                midiBarSendOn = (midiBarSendOn-1)&1;
            }
        }
        else if (action == Up)
        {
            whichMidiSendSelected = (whichMidiSendSelected+1)&1;
        }
        else if (action == Down)
        {
            whichMidiSendSelected = (whichMidiSendSelected-1)&1;
        }
        OLEDtextColor(1, 0);
        OLEDwriteString("SEND MIDI ", 10, 0, FirstLine);
        GFXfillRect(&theGFX, 76, 0, 37, 16, !whichMidiSendSelected);
        OLEDtextColor(whichMidiSendSelected, !whichMidiSendSelected);
        if (midiSendOn)
        {
            GFXwrite(&theGFX, 79);
            GFXwrite(&theGFX, 78);
        }
        else
        {
            GFXwrite(&theGFX, 79);
            GFXwrite(&theGFX, 70);
            GFXwrite(&theGFX, 70);
        }
        OLEDtextColor(1, 0);
        OLEDwriteString("SEND BAR  ", 10, 0, SecondLine);
        GFXfillRect(&theGFX, 76, 16, 37, 16, whichMidiSendSelected);
        OLEDtextColor(!whichMidiSendSelected, whichMidiSendSelected);
        if (midiBarSendOn)
        {
            GFXwrite(&theGFX, 79);
            GFXwrite(&theGFX, 78);
        }
        else
        {
            GFXwrite(&theGFX, 79);
            GFXwrite(&theGFX, 70);
            GFXwrite(&theGFX, 70);
        }
        mainOLEDWaitingToSend = 1;
                
    }
    
    //now draw stuff
    if (whatToDraw == 1)
    {
        //draw main menu
        OLEDclear(128, 64);
        myGFX_setFont(2);
        for (int i = 0; i < numMainMenuItems; i++)
        {
            if (menuPosition[0][1] == i)
            {
                OLEDtextColor(0, 1);
                OLEDwriteString(mainMenuNames[i], 15, 0, i);
                OLEDwriteArrow(0, i);
            }
            else
            {
                OLEDtextColor(1, 0);
                OLEDwriteString(mainMenuNames[i], 15, 0, i);
                
            }

        }
        OLEDtextColor(1, 0);
        mainOLEDWaitingToSend = 1;
    }
    else if (whatToDraw == 2)
    {
        //draw calibration menu
        OLEDclear(128, 64);
        myGFX_setFont(2);
        for (int i = 0; i < numCalibrationItems; i++)
        {
            if (menuPosition[1][1] == i)
            {
                OLEDtextColor(0, 1);
                OLEDwriteString(calibrationNames[i], 15, 0, i);
                OLEDwriteArrow(0, i);
            }
            else
            {
                OLEDtextColor(1, 0);
                OLEDwriteString(calibrationNames[i], 15, 0, i);
                
            }
        }
        OLEDtextColor(1, 0);
        mainOLEDWaitingToSend = 1;
    }
    else if (whatToDraw == 3)
    {
        //draw settings menu
        OLEDclear(128, 64);
        myGFX_setFont(2);
        uint8_t tempPos = 0;
        for (int i = 0; i < numSettingsItems; i++)
        {
            if (menuPosition[2][1] == i)
            {
                OLEDtextColor(0, 1);
                OLEDwriteString(settingsNames[i], 15, 0, 0);
                OLEDwriteArrow(0, 0);
            }
            else if (i > menuPosition[2][1])
            {
                OLEDtextColor(1, 0);
                tempPos = (i - menuPosition[2][1]);
                if (tempPos < 4)
                {
                    OLEDwriteString(settingsNames[i], 15, 0, tempPos);
                } 
            }
        }
        tempPos++;
        OLEDtextColor(1, 0);
        while (tempPos < 4)
        {
            OLEDwriteString("               ", 15, 0, tempPos);
            tempPos++;
        }
        mainOLEDWaitingToSend = 1;
    }
}



void leftPressed()
{
    if (!editMode) //normal behavior
    {
        if (currentCopedent == 0)
        {
            currentCopedent = MAX_NUM_COPEDENTS-1;
        }
        else
        {
            currentCopedent -= 1;
        }
        necks[currentNeck] = currentCopedent;
        neckByte = 0;
        neckByte |= (necks[0]<<5) + (necks[1]<<2) + currentNeck;
        EEPROM_WriteByte(neckByte, EEPROM_NECKS_OFFSET);
        displayCurrentPresetNameAndCopedent();
    }
    else
    {
        menuAction(Left);
    }
}

void rightPressed()
{
    if (!editMode) //normal behavior
    {
        currentCopedent += 1;
        if (currentCopedent >= MAX_NUM_COPEDENTS)
        {
            currentCopedent = 0;
        }
        necks[currentNeck] = currentCopedent;
        neckByte = 0;
        neckByte |= (necks[0]<<5) + (necks[1]<<2) + currentNeck;
        EEPROM_WriteByte(neckByte, EEPROM_NECKS_OFFSET);
        displayCurrentPresetNameAndCopedent();
    }
    else
    {
       menuAction(Right);
    }
}

void downPressed()
{
    if (!editMode) //normal behavior
    {
        patchNum -= 1;
        patchNum &= 63;
        EEPROM_WriteByte(patchNum, EEPROM_CURRENT_PRESET_OFFSET);
        displayCurrentPresetNameAndCopedent();
    }
    else
    {
        menuAction(Down);
    }
}

void upPressed()
{
    if (!editMode) //normal behavior
    {
        patchNum += 1;
        patchNum &= 63;
        EEPROM_WriteByte(patchNum, EEPROM_CURRENT_PRESET_OFFSET);
        displayCurrentPresetNameAndCopedent();
    }
    else
    {
        menuAction(Up);
    }
}

void enterPressed()
{
    if (!editMode) //normal behavior
    {
        ;//nothing
    }
    else
    {
        menuAction(Enter);
    }
}

void enterLeverCalibrationMode(void)
{
    OLEDclear(128, 64);
    myGFX_setFont(2);
    OLEDtextColor(0, 1);
    OLEDwriteString("CALIBRATION", 11, 1, FirstLine);
    OLEDwriteString("MOVE ALL PEDALS", 15, 1, SecondLine);
    OLEDwriteString("AND LEVERS", 10, 1, ThirdLine);
    OLEDwriteString("THEN PRESS ->", 15, 1, FourthLine);
    mainOLEDWaitingToSend = 1;
    OLEDtextColor(1, 0);
    //entering calibration mode, clear the pedals low and high arrays
    for (int i = 0; i < 10; i++)
    {
        pedals_low[i] = 4095;
        pedals_high[i] = 0;
    }
    leverCalibrationMode = 1;
}

void exitLeverCalibrationMode(void)
{
    leverCalibrationMode = 0;
    //draw normal screen
    for (int i = 0; i < NUM_PEDALS; i++)
    {
        //if you are closer to pedal high than pedal low, then switch high and low, the sensor is reading backwards
        if (angle[i] > (pedals_low[i]+20))
        {
            pedal_inverted[i] = 1;
        }
        else
        {
            pedal_inverted[i] = 0;
        }
    }
    uint16_t pedal_inverted_byte = 0;
    for (int i = 0; i < NUM_PEDALS; i++)
    {
        pedal_inverted_byte += pedal_inverted[i] << i;
    }
    EEPROM_WriteByte(pedal_inverted_byte>>8, EEPROM_PEDAL_INVERTED_OFFSET);
    EEPROM_WriteByte(pedal_inverted_byte& 255, EEPROM_PEDAL_INVERTED_OFFSET+1);
    calculatePedalRatios();
    //now need to store this in EEPROM.                
    for (int i = 0; i < NUM_PEDALS; i++)
    {
         EEPROM_WriteByte((pedals_low[i] >> 8), EEPROM_LEVER_CALIBRATION_OFFSET + (i*4));
         EEPROM_WriteByte((pedals_low[i] & 255), EEPROM_LEVER_CALIBRATION_OFFSET + ((i*4) + 1));
         EEPROM_WriteByte((pedals_high[i] >> 8), EEPROM_LEVER_CALIBRATION_OFFSET + ((i*4) + 2));
         EEPROM_WriteByte((pedals_high[i] & 255), EEPROM_LEVER_CALIBRATION_OFFSET + ((i*4) + 3));
    }
}


void enterFretCalibrationMode(void)
{
    OLEDclear(128, 64);
    myGFX_setFont(2);
    OLEDtextColor(0, 1);
    fretToCalibrate = 0;
    OLEDwriteString("CALIBRATION", 11, 1, FirstLine);
    OLEDwriteString("PLACE BAR AT ", 15, 1, SecondLine);
    OLEDwriteString("FRET ", 5, 1, ThirdLine);
    OLEDwriteInt(whichFretArray[fretToCalibrate], 2, 40, ThirdLine);
    OLEDwriteString("THEN PRESS ->", 15, 1, FourthLine);
    mainOLEDWaitingToSend = 1;
    OLEDtextColor(1, 0);
    fretCalibrationMode = 1;
}

void exitFretCalibrationMode(void)
{
    fretCalibrationMode = 0;
    //now need to store this in EEPROM.                
    for (int i = 0; i < NUM_FRET_MEASUREMENTS; i++)
    {
         EEPROM_WriteByte((fretMeasurements[0][i] >> 8), EEPROM_FRET_CALIBRATION_OFFSET + (i*4));
         EEPROM_WriteByte((fretMeasurements[0][i] & 255), EEPROM_FRET_CALIBRATION_OFFSET + ((i*4) + 1));
         EEPROM_WriteByte((fretMeasurements[1][i] >> 8), EEPROM_FRET_CALIBRATION_OFFSET + ((i*4) + 2));
         EEPROM_WriteByte((fretMeasurements[1][i] & 255), EEPROM_FRET_CALIBRATION_OFFSET + ((i*4) + 3));
    }
    exitEditModeMenu();

}


void displayCurrentPresetNameAndCopedent(void)
{
    int macroCheck = 0;
    for (int i = 0; i < 8; i++)
    {
        if (macroNamesArray[patchNum][i][0] == 255)
        {
            macroCheck = 1;
        }  
    }
    if (macroCheck == 0) //don't display if the name data still hasn't been retrieved by the SPI bus (255 is invalid initial data)
    {
        OLEDclear(128, 64);
        OLEDtextColor(1, 0);
        myGFX_setFont(0);
        OLEDwriteInt(patchNum , 2, 0,FirstLine);
        //OLEDwriteString(" ", 1, OLEDgetCursor(), FirstLine);
        OLEDwriteString((char *)&presetNamesArray[patchNum][0], NAME_CLIPPED_LENGTH, 0, SecondLine);
        GFXwriteFastHLine(&theGFX, 0, 40, 128, 1);
        OLEDwriteInt(currentCopedent , 1, 0,FourthLine);
        OLEDwriteString(" ", 1, OLEDgetCursor(), FourthLine);
        OLEDwriteString((char *)&copedentNamesArray[currentCopedent][0], COPEDENT_NAME_CLIPPED_LENGTH, OLEDgetCursor(), FourthLine);
        mainOLEDWaitingToSend = 1;
        presetAlreadyDisplayed[patchNum] = 1;
        //and update the macro OLED screens
        whichMacro = 0;
        macroOLEDWaitingToSend = 1;
    }
}
/* [] END OF FILE */
