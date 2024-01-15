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
#include "gfx.h"
#include "oled.h"

extern uint8_t whichMacroPageIsActive;

void scanUI(void);
void enterEditModeMenu(void);
void exitEditModeMenu(void);
void leftPressed();
void rightPressed();
void downPressed();
void upPressed();
void enterPressed();
void enterLeverCalibrationMode(void);
void exitLeverCalibrationMode(void);
void enterFretCalibrationMode(void);
void exitFretCalibrationMode(void);
void exitPresetStoreMenu(void);
void displayCurrentPresetNameAndCopedent(void);
void displayCurrentControlNames(void);
/* [] END OF FILE */
