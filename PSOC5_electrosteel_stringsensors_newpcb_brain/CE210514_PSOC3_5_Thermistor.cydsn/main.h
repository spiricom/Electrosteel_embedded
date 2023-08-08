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
extern volatile uint8_t I2Cbuff1[256];

typedef enum _MenuModes
{
	MainMenu = 0,
    CalibrationMenu,
    SettingsMenu,
	CalibrateLeversMenu,
	CalibrateFretsMenu,
    TransposeMenu,
    OctaveActionMenu,
    DeadzonesMenu,
    SliderRepMenu,
    MidiSendMenu,
	NilMenu
} MenuModes;

uint8 I2C_MasterWriteBlocking(uint8 i2CAddr, uint16 nbytes, uint8_t mode);
/* [] END OF FILE */
