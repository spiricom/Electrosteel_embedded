/**
  ******************************************************************************
  * @file    Audio_playback_and_record/inc/waveplayer.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    26-June-2014
  * @brief   Header for waveplayer.c module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AUDIOSTREAM_H
#define __AUDIOSTREAM_H

/* Includes ------------------------------------------------------------------*/
#include "parameters.h"
#include "leaf.h"
#include "main.h"


#define AUDIO_FRAME_SIZE      8
#define HALF_BUFFER_SIZE      AUDIO_FRAME_SIZE * 2 //number of samples per half of the "double-buffer" (twice the audio frame size because there are interleaved samples for both left and right channels)
#define AUDIO_BUFFER_SIZE     AUDIO_FRAME_SIZE * 4 //number of samples in the whole data structure (four times the audio frame size because of stereo and also double-buffering/ping-ponging)
#define SMALL_MEM_SIZE 54000
#define MED_MEM_SIZE 340000
#define LARGE_MEM_SIZE 33554432 //32 MBytes - size of SDRAM IC
#define MTOF_TABLE_SIZE	32768
#define ATODB_TABLE_SIZE 8192
#define DBTOA_TABLE_SIZE 8192

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  BUFFER_OFFSET_NONE = 0,
  BUFFER_OFFSET_HALF,
  BUFFER_OFFSET_FULL,
}BUFFER_StateTypeDef;

#ifdef SAMPLERATE96K
#define SAMPLE_RATE 96000.f
#else
#define SAMPLE_RATE 48000.f
#endif

#define INV_SAMPLE_RATE 1.f/SAMPLE_RATE
#define SAMPLE_RATE_MS (SAMPLE_RATE / 1000.f)
#define INV_SR_MS 1.f/SAMPLE_RATE_MS
#define SAMPLE_RATE_DIV_PARAMS SAMPLE_RATE / 3
#define SAMPLE_RATE_DIV_PARAMS_MS (SAMPLE_RATE_DIV_PARAMS / 1000.f)
#define INV_SR_DIV_PARAMS_MS 1.f/SAMPLE_RATE_DIV_PARAMS_MS


#define EXP_BUFFER_SIZE 2048
#define DECAY_EXP_BUFFER_SIZE 4096

#define CTRL_MIDI_START 9

typedef enum BOOL {
	FALSE = 0,
	TRUE
} BOOL;



void audioInit(I2C_HandleTypeDef* hi2c, SAI_HandleTypeDef* hsaiOut, SAI_HandleTypeDef* hsaiIn);

void initFunctionPointers(void);

void audioFrame(uint16_t buffer_offset);
float audioTickL(void);
void DMA1_TransferCpltCallback(DMA_HandleTypeDef *hdma);
void DMA1_HalfTransferCpltCallback(DMA_HandleTypeDef *hdma);
void updateStateFromSPIMessage(uint8_t currentByte);

void setTranspose(float in, int v, int string);
void setPitchBendRange(float in, int v, int string);
void setNoiseAmp(float in, int v, int string);

void oscillator_tick(float note, int string);

typedef void (*shapeTick_t)(float*, int, float, float, int, int string);
typedef void (*lfoShapeTick_t)(float*, int, int string);
void sawSquareTick(float* sample, int v, float freq, float shape, int sync, int string);
void sineTriTick(float* sample, int v, float freq, float shape, int sync, int string);
void sawTick(float* sample, int v, float freq, float shape, int sync, int string);
void pulseTick(float* sample, int v, float freq, float shape, int sync, int string);
void sineTick(float* sample, int v, float freq, float shape, int sync, int string);
void triTick(float* sample, int v, float freq, float shape, int sync, int string);
void userTick(float* sample, int v, float freq, float shape, int sync, int string);

void lfoSawSquareTick(float* sample, int v, int string);
void lfoSineTriTick(float* sample, int v, int string);
void lfoSineTick(float* sample, int v, int string);
void lfoTriTick(float* sample, int v, int string);
void lfoSawTick(float* sample, int v, int string);
void lfoPulseTick(float* sample, int v, int string);

void lfoSawSquareSetRate(float r, int v, int string);
void lfoSineTriSetRate(float r, int v, int string);
void lfoSineSetRate(float r, int v, int string);
void lfoTriSetRate(float r, int v, int string);
void lfoSawSetRate(float r, int v, int string);
void lfoPulseSetRate(float r, int v, int string);


void lfoSawSquareSetPhase(float p, int v, int string);
void lfoSineTriSetPhase(float p, int v, int string);
void lfoSineSetPhase(float p, int v, int string);
void lfoTriSetPhase(float p, int v, int string);
void lfoSawSetPhase(float p, int v, int string);
void lfoPulseSetPhase(float p, int v, int string);


void lfoSawSquareSetShape(float s, int v, int string);
void lfoSineTriSetShape(float s, int v, int string);
void lfoSineSetShape(float s, int v, int string);
void lfoTriSetShape(float s, int v, int string);
void lfoSawSetShape(float s, int v, int string);
void lfoPulseSetShape(float s, int v, int string);

extern shapeTick_t shapeTick[NUM_OSC];
extern lfoShapeTick_t lfoShapeTick[NUM_LFOS];

void noise_tick(int string);
void noiseSetFreq(float value, int v, int string);
void noiseSetGain(float value, int v, int string);
void noiseSetTilt(float value, int v, int string);

float filter_tick(float* samples, float note, int string);

typedef void (*filterTick_t)(float*, int, float, int);
void setFreqMultPitch(float pitch, int osc, int string);
void setFreqMultHarm(float harm, int osc, int string);
void lowpassTick(float* sample, int v, float cutoff, int string);
void highpassTick(float* sample, int v, float cutoff, int string);
void bandpassTick(float* sample, int v, float cutoff, int string);
void diodeLowpassTick(float* sample, int v, float cutoff, int string);
void LadderLowpassTick(float* sample, int v, float cutoff, int string);
void VZlowshelfTick(float* sample, int v, float cutoff, int string);
void VZhighshelfTick(float* sample, int v, float cutoff, int string);
void VZpeakTick(float* sample, int v, float cutoff, int string);
void VZbandrejectTick(float* sample, int v, float cutoff, int string);

void filterSetCutoff(float cutoff, int v, int string);
void filterSetKeyfollow(float keyfollow, int v, int string);
void lowpassSetQ(float q, int v, int string);
void highpassSetQ(float q, int v, int string);
void bandpassSetQ(float q, int v, int string);
void diodeLowpassSetQ(float q, int v, int string);
void VZpeakSetQ(float bw, int v, int string);
void VZlowshelfSetQ(float bw, int v, int string);
void VZhighshelfSetQ(float bw, int v, int string);
void VZbandrejectSetQ(float bw, int v, int string);
void LadderLowpassSetQ(float q, int v, int string);
void lowpassSetGain(float gain, int v, int string);
void highpassSetGain(float gain, int v, int string);
void bandpassSetGain(float gain, int v, int string);
void diodeLowpassSetGain(float gain, int v, int string);
void VZpeakSetGain(float gain, int v, int string);
void VZlowshelfSetGain(float gain, int v, int string);
void VZhighshelfSetGain(float gain, int v, int string);
void VZbandrejectSetGain(float gain, int v, int string);
void LadderLowpassSetGain(float gain, int v, int string);
extern filterTick_t filterTick[NUM_FILT];

//envelope functions
void setEnvelopeAttack(float a, int v, int string);
void setEnvelopeDecay(float d, int v, int string);
void setEnvelopeSustain(float s, int v, int string);
void setEnvelopeRelease(float r, int v, int string);
void setEnvelopeLeak(float leak, int v, int string);

//effects


typedef float (*effectTick_t)(float sample,int v, int string);
extern effectTick_t effectTick[NUM_EFFECT];
float blankTick(float sample, int v, int string);
float tiltFilterTick(float sample,int v, int string);
float hardClipTick(float sample, int v, int string);
float tanhTick(float sample, int v, int string);
float softClipTick(float sample, int v, int string);
float satTick(float sample, int v, int string);
float bcTick(float sample, int v, int string);
float compressorTick(float sample, int v, int string);
float shaperTick(float sample, int v, int string);
float wavefolderTick(float sample, int v, int string);
float chorusTick(float sample, int v, int string);

void clipperGainSet(float value, int v, int string);
void wavefolderParam1(float value, int v, int string);
void wavefolderParam3(float value, int v, int string);
void tiltParam1(float value, int v, int string);
void tiltParam2(float value, int v, int string);
void tiltParam3(float value, int v, int string);
void tiltParam4(float value, int v, int string);
void compressorParam1(float value, int v, int string);
void compressorParam2(float value, int v, int string);
void compressorParam3(float value, int v, int string);
void compressorParam4(float value, int v, int string);
void compressorParam5(float value, int v, int string);
void offsetParam2(float value, int v, int string);
void param2Linear(float value, int v, int string);
void param3Linear(float value, int v, int string);
void param3Soft(float value, int v, int string);
void param3Hard(float value, int v, int string);
void param3BC(float value, int v, int string);
void param4Linear(float value, int v, int string);
void param5Linear(float value, int v, int string);
void fxMixSet(float value, int v, int string);
void fxPostGainSet(float value, int v, int string);
float wavefolderTick(float sample, int v, int string);
void chorusParam1(float value, int v, int string);
void chorusParam2(float value, int v, int string);
void chorusParam3(float value, int v, int string);
void chorusParam4(float value, int v, int string);

void FXLowpassParam1(float value, int v, int string);
void FXLowpassParam3(float value, int v, int string);
void FXHighpassParam1(float value, int v, int string);
void FXHighpassParam3(float value, int v, int string);
void FXBandpassParam1(float value, int v, int string);
void FXBandpassParam3(float value, int v, int string);
void FXDiodeParam1(float value, int v, int string);
void FXDiodeParam3(float value, int v, int string);
void FXPeakParam1(float value, int v, int string);
void FXPeakParam2(float value, int v, int string);
void FXPeakParam3(float value, int v, int string);
void FXLowShelfParam1(float value, int v, int string);
void FXLowShelfParam2(float value, int v, int string);
void FXLowShelfParam3(float value, int v, int string);
void FXHighShelfParam1(float value, int v, int string);
void FXHighShelfParam2(float value, int v, int string);
void FXHighShelfParam3(float vlaue, int v, int string);
void FXNotchParam1(float value, int v, int string);
void FXNotchParam2(float value, int v, int string);
void FXNotchParam3(float value, int v, int string);
void FXLadderParam1(float value, int v, int string);
void FXLadderParam3(float value, int v, int string);
float FXlowpassTick(float sample, int v, int string);
float FXhighpassTick(float sample, int v, int string);
float FXbandpassTick(float sample, int v, int string);
float FXdiodeLowpassTick(float sample, int v, int string);
float FXLadderLowpassTick(float sample, int v, int string);
float FXVZlowshelfTick(float sample, int v, int string);
float FXVZhighshelfTick(float sample, int v, int string);
float FXVZpeakTick(float sample, int v, int string);
float FXVZbandrejectTick(float sample, int v, int string);


//master functions
void setAmp(float amp, int v, int string);
void setFinalLowpass(float in, int v, int string);
void setMaster(float amp, int v, int string);

extern float sourceValues[NUM_SOURCES][NUM_STRINGS_PER_BOARD];
extern uint8_t lfoOn[NUM_LFOS];
extern float oscAmpMult;
extern float oscAmpMultArray[4];

extern int32_t audioOutBuffer[AUDIO_BUFFER_SIZE];
extern int32_t audioInBuffer[AUDIO_BUFFER_SIZE];
extern uint32_t codecReady;
extern int presetReady;
extern uint8_t oscToTick;
extern uint8_t filterToTick;
extern uint8_t overSampled;
extern uint8_t numEffectToTick;
//extern float audioDisplayBuffer[128];
extern uint32_t displayBufferIndex;
extern uint8_t numStringsThisBoard;
extern volatile int firstString;
extern float stringMIDIPitches[NUM_STRINGS_PER_BOARD];
extern tExpSmooth knobSmoothers[12];
extern tExpSmooth pedalSmoothers[10];
#endif /* __AUDIOSTREAM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
