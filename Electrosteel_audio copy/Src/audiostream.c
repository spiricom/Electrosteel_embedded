/*
 * audiostream.c
 *
 *  Created on: Aug 30, 2019
 *      Author: jeffsnyder
 */


/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "leaf.h"
#include "codec.h"
#include "i2c.h"
#include "gpio.h"
#include "spi.h"
#include "parameters.h"

#include "audiostream.h"
//the audio buffers are put in the D2 RAM area because that is a memory location that the DMA has access to.
int32_t audioOutBuffer[AUDIO_BUFFER_SIZE] __ATTR_RAM_D2;
int32_t audioInBuffer[AUDIO_BUFFER_SIZE] __ATTR_RAM_D2;

cStack midiStack;

char small_memory[SMALL_MEM_SIZE];
char medium_memory[MED_MEM_SIZE] __ATTR_RAM_D1;
char large_memory[LARGE_MEM_SIZE] __ATTR_SDRAM;
tMempool mediumPool;
tMempool largePool;

void audioFrame(uint16_t buffer_offset);
uint32_t audioTick(float* samples);

HAL_StatusTypeDef transmit_status;
HAL_StatusTypeDef receive_status;

uint32_t codecReady = 0;

uint32_t frameCounter = 0;

int stringPositions[4];

int newPluck = 0;
int newBar = 0;

uint8_t pluck[26];
uint8_t bar[8];



float decayExpBuffer[DECAY_EXP_BUFFER_SIZE]__ATTR_RAM_D2;
int previousStringInputs[12];

float volumeAmps128[128] = {0.000562, 0.000569, 0.000577, 0.000580, 0.000587, 0.000601, 0.000622, 0.000650, 0.000676, 0.000699, 0.000720, 0.000739, 0.000753, 0.000766, 0.000791, 0.000826, 0.000872, 0.000912, 0.000953, 0.001012, 0.001091, 0.001188, 0.001270, 0.001360, 0.001465, 0.001586, 0.001717, 0.001829, 0.001963, 0.002118, 0.002295, 0.002469, 0.002636, 0.002834, 0.003063, 0.003322, 0.003496, 0.003750, 0.004143, 0.004675, 0.005342, 0.005880, 0.006473, 0.007122, 0.007827, 0.008516, 0.009167, 0.009968, 0.010916, 0.012014, 0.012944, 0.013977, 0.015352, 0.017070, 0.019130, 0.020965, 0.022847, 0.024823, 0.026891, 0.028835, 0.030496, 0.033044, 0.036478, 0.040799, 0.045093, 0.049150, 0.053819, 0.059097, 0.064986, 0.070712, 0.076315, 0.081930, 0.087560, 0.093117, 0.098283, 0.104249, 0.111012, 0.118575, 0.124879, 0.131163, 0.141721, 0.156554, 0.175663, 0.195870, 0.213414, 0.228730, 0.241817, 0.252675, 0.264038, 0.276776, 0.290871, 0.306323, 0.322794, 0.338528, 0.353711, 0.368343, 0.382424, 0.393015, 0.406556, 0.426763, 0.453639, 0.487182, 0.522242, 0.550876, 0.573000, 0.588613, 0.598943, 0.613145, 0.628104, 0.643820, 0.660293, 0.676658, 0.692845, 0.709881, 0.727766, 0.746500, 0.764505, 0.782949, 0.802346, 0.822696, 0.844189, 0.867268, 0.886360, 0.901464, 0.912581, 0.921606, 0.932834, 0.944061};

BOOL bufferCleared = TRUE;

int numBuffersToClearOnLoad = 2;
int numBuffersCleared = 0;

#define NUM_STRINGS 12
#define NUM_STRINGS_PER_BOARD 4
volatile int firstString = 0;
volatile int lastString = 0;
volatile int lastStringPlusOne = 0;

tExpSmooth stringFreqSmoothers[NUM_STRINGS_PER_BOARD];

tExpSmooth volumeSmoother;
tExpSmooth knobSmoothers[4];

tSlide freqSlider[NUM_STRINGS_PER_BOARD];




//function pointers
shapeTick_t shapeTick[NUM_OSC];
filterTick_t filterTick[NUM_FILT];
lfoShapeTick_t lfoShapeTick[NUM_LFOS];
effectTick_t effectTick[NUM_EFFECT];

//oscillators
tMBSaw saw[NUM_OSC];
tMBPulse pulse[NUM_OSC];
tCycle sine[NUM_OSC];
tMBTriangle tri[NUM_OSC];

// Using seperate objects for pairs to easily maintain phase relation
tMBSawPulse sawPaired[NUM_OSC];
tMBSineTri sinePaired[NUM_OSC];

//noise
float noiseOuts[2];
tVZFilter noiseShelf1, noiseShelf2, noiseBell1;
tNoise noise;
tIntPhasor lfoSaw[NUM_LFOS];
tSquareLFO lfoPulse[NUM_LFOS];
tCycle lfoSine[NUM_LFOS];
tTriLFO lfoTri[NUM_LFOS];
tSawSquareLFO lfoSawSquare[NUM_LFOS];
tSineTriLFO lfoSineTri[NUM_LFOS];
uint8_t lfoOn[NUM_LFOS];

//oscillator outputs
float outSamples[2][NUM_OSC];

//source vals
float sourceValues[NUM_SOURCES];

tExpSmooth mapSmoothers[MAX_NUM_MAPPINGS];
tExpSmooth pitchSmoother[NUM_OSC];
tExpSmooth filterCutoffSmoother[NUM_FILT];


float freqMult[NUM_OSC];
float bendRangeMultiplier = 0.002929866324849f; //default to divide by 48


//filters
tDiodeFilter diodeFilters[NUM_FILT];
tVZFilter VZfilterPeak[NUM_FILT];
tVZFilter VZfilterLS[NUM_FILT];
tVZFilter VZfilterHS[NUM_FILT];
tVZFilter VZfilterBR[NUM_FILT];
tSVF lowpass[NUM_FILT];
tSVF highpass[NUM_FILT];
tSVF bandpass[NUM_FILT];
tLadderFilter Ladderfilter[NUM_FILT];

float filterGain[NUM_FILT];

//envelopes
tADSRT envs[NUM_ENV];
float expBuffer[EXP_BUFFER_SIZE];
float expBufferSizeMinusOne;
float decayExpBuffer[DECAY_EXP_BUFFER_SIZE];
float decayExpBufferSizeMinusOne;


//effects
 tHighpass dcBlock1[NUM_EFFECT];
 tHighpass dcBlock2[NUM_EFFECT];
 tVZFilter shelf1[NUM_EFFECT], shelf2[NUM_EFFECT], bell1[NUM_EFFECT];
 tCompressor comp[NUM_EFFECT];
 tCrusher bc[NUM_EFFECT];
 tLockhartWavefolder wf[NUM_EFFECT];
 tLinearDelay delay1[NUM_EFFECT];
 tLinearDelay delay2[NUM_EFFECT];
 tCycle mod1[NUM_EFFECT];
 tCycle mod2[NUM_EFFECT];
 float fxMix[NUM_EFFECT];
 float fxPostGain[NUM_EFFECT];
 tDiodeFilter FXdiodeFilters[NUM_EFFECT];
 tVZFilter FXVZfilterPeak[NUM_EFFECT];
 tVZFilter FXVZfilterLS[NUM_EFFECT];
 tVZFilter FXVZfilterHS[NUM_EFFECT];
 tVZFilter FXVZfilterBR[NUM_EFFECT];
 tSVF FXlowpass[NUM_EFFECT];
 tSVF FXhighpass[NUM_EFFECT];
 tSVF FXbandpass[NUM_EFFECT];
 tLadderFilter FXLadderfilter[NUM_EFFECT];
//master
float amplitude = 0.0f;
float finalMaster = 1.0f;

tSimplePoly myPoly;
float bend;
float transpose = 0.0f;
tNoise noise;

#define OVERSAMPLE 2
float inv_oversample = 1.0f / OVERSAMPLE;

tOversampler os;
float oversamplerArray[OVERSAMPLE];

float upState1[128];
float downState1[128];

tSVF finalLowpass;

uint8_t voiceSounding = 0;

LEAF leaf;

union breakFloat{
	float f;
	uint8_t b[4];
};


float paramsFromBrain[16];
uint maxVolumes[NUM_STRINGS];
float invMaxVolumes[NUM_STRINGS];
uint stringInputs[NUM_STRINGS];

float octave = 1.0f;

float stringMappedPositions[NUM_STRINGS];
float stringFrequencies[NUM_STRINGS];

float volumePedal = 0.0f;
float knobScaled[4];
float stringMIDIPitches[NUM_STRINGS_PER_BOARD];
//TODO:
// frets are measured at 3 7 12 and 19   need to redo these measurements with an accurately set capo
float fretMeasurements[4][4] ={
		{62750.0f, 61600.0f, 31785.0f, 0.0f},
		{39600.0f, 41500.0f, 15700.0f, 0.0f},
		{27520.0f, 30200.0f, 8458.0f, 0.0f},
		{9490.0f, 13600.0f, 2674.0f, 0.0f}
	};

float fretScaling[4] = {1.0f, 0.6666666666666f, 0.5f, 0.25f};

float stringOctave[NUM_STRINGS];
int voice = 0;
int dualSlider = 0;
int neck = 0;

int currentBarBuffer = 0;
int currentPluckBuffer = 0;

int newLevers = 0;
int edit = 0;
int whichTable = 0;

/**********************************************/

float map(float value, float istart, float istop, float ostart, float ostop)
{
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}


void audioInit(I2C_HandleTypeDef* hi2c, SAI_HandleTypeDef* hsaiOut, SAI_HandleTypeDef* hsaiIn)
{
	// Initialize LEAF.

	LEAF_init(&leaf, SAMPLE_RATE, small_memory, SMALL_MEM_SIZE, &randomNumber);

	tMempool_init (&mediumPool, medium_memory, MED_MEM_SIZE, &leaf);
	tMempool_init (&largePool, large_memory, LARGE_MEM_SIZE, &leaf);

	leaf.clearOnAllocation = 1;
	LEAF_generate_exp(decayExpBuffer, 0.001f, 0.0f, 1.0f, -0.0008f, DECAY_EXP_BUFFER_SIZE); // exponential decay buffer falling from 1 to 0

	int bit0 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
	int bit1 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5);

	firstString = (bit0+(bit1 << 1)) * NUM_STRINGS_PER_BOARD;


	for (int i = 0; i < NUM_STRINGS_PER_BOARD; i++)
	{

		tSlide_init(&freqSlider[i], 1, 20, &leaf);

		tExpSmooth_init(&stringFreqSmoothers[i],1.0f, 0.05f, &leaf);
	}


	tExpSmooth_init(&volumeSmoother,0.0f, 0.0005f, &leaf);
	for (int i = 0; i < 4; i++)
	{
		tExpSmooth_init(&knobSmoothers[i],0.0f, 0.0005f, &leaf);
	}


	for (int i = 0; i < AUDIO_BUFFER_SIZE; i++)
	{
		audioOutBuffer[i] = 0;
	}

	// set up the I2S driver to send audio data to the codec (and retrieve input as well)
	transmit_status = HAL_SAI_Transmit_DMA(hsaiOut, (uint8_t *)&audioOutBuffer[0], AUDIO_BUFFER_SIZE);
	receive_status = HAL_SAI_Receive_DMA(hsaiIn, (uint8_t *)&audioInBuffer[0], AUDIO_BUFFER_SIZE);

	// with the CS4271 codec IC, the SAI Transmit and Receive must be happening before the chip will respond to
	// I2C setup messages (it seems to use the masterclock input as it's own internal clock for i2c data, etc)
	// so while we used to set up codec before starting SAI, now we need to set up codec afterwards, and set a flag to make sure it's ready

	//now to send all the necessary messages to the codec
	AudioCodec_init(hi2c);
	HAL_Delay(1);

}

volatile uint16_t volumePedalInt;
float octaveRatios[4] = {0.5f, 1.0f, 2.0f, 4.0f};
int octaveIndex = 1;
int stringOctaveIndex[4];

void audioFrame(uint16_t buffer_offset)
{


	//if the codec isn't ready, keep the buffer as all zeros
	//otherwise, start computing audio!

	if (newBar)
	{

		int currentBarBufferL = currentBarBuffer;

		if ((SPI_RX[6 + (8 * currentBarBufferL)] == 254) && (SPI_RX[7 + (8 * currentBarBufferL)] == 253))
		{
			for (int j = 0; j < 2; j++)
			{
				stringPositions[j] =  ((uint16_t)SPI_RX[(j * 2) + (8 * currentBarBufferL)] << 8) + ((uint16_t)SPI_RX[(j * 2) + (8 * currentBarBufferL) + 1] & 0xff);
				if ((stringPositions[j] == 65535) || (stringPositions[j] > fretMeasurements[0][j]))
				{
					stringMappedPositions[j] = 1.0f;
				}
				else if ((stringPositions[j] >= fretMeasurements[1][j]) && (stringPositions[j] <= fretMeasurements[0][j]))
				{
					stringMappedPositions[j] = map((float)stringPositions[j], fretMeasurements[0][j], fretMeasurements[1][j], fretScaling[0], fretScaling[1]);
				}
				else if ((stringPositions[j] >= fretMeasurements[2][j]) && (stringPositions[j] < fretMeasurements[1][j]))
				{
					stringMappedPositions[j] = map((float)stringPositions[j], fretMeasurements[1][j], fretMeasurements[2][j], fretScaling[1], fretScaling[2]);
				}
				else
				{
					stringMappedPositions[j] = map((float)stringPositions[j], fretMeasurements[2][j], fretMeasurements[3][j], fretScaling[2], fretScaling[3]);
				}
			}
			float myMappedPos = 0.0f;
			for (int i = 0; i < NUM_STRINGS_PER_BOARD; i++)
			{

				if (dualSlider)
				{
					if ((stringMappedPositions[0] == 1.0f) && (stringMappedPositions[1] < 1.0f))
					{
						stringMappedPositions[0] = stringMappedPositions[1];
					}
					else if ((stringMappedPositions[1] == 1.0f) && (stringMappedPositions[0] < 1.0f))
					{
						stringMappedPositions[1] = stringMappedPositions[0];
					}
					myMappedPos = LEAF_interpolation_linear(stringMappedPositions[0], stringMappedPositions[1], ((float)(i+firstString)) * 0.090909090909091f);
				}
				else
				{
					myMappedPos =  stringMappedPositions[0];
				}
				float tempFreq = (1.0f / myMappedPos) * mtof(stringMIDIPitches[i]);
				tempFreq = tSlide_tick(&freqSlider[i], tempFreq);
				tExpSmooth_setDest(&stringFreqSmoothers[i], tempFreq);
			}


		}
		newBar = 0;

	}

	if (newLevers)
	{
		int currentLeverBufferL = currentLeverBuffer;

		if ((SPI_LEVERS[72 + (currentLeverBufferL * 74)] == 254) && (SPI_LEVERS[73 + (currentLeverBufferL * 74)] == 253))
		{


			for (int i = 0; i < 16; i++)
			{
				paramsFromBrain[i] = SPI_LEVERS[(i + 56) + (currentLeverBuffer * 74)] * 0.003921568627451f; //scaled 0.0 to 1.0

			}

			union breakFloat tempBreak;

			for (int i = 0; i < NUM_STRINGS_PER_BOARD; i++)
			{


				tempBreak.b[0] = SPI_LEVERS[((i+firstString) * 4) + (currentLeverBufferL * 74)];
				tempBreak.b[1] = SPI_LEVERS[((i+firstString) * 4) + 1 + (currentLeverBufferL * 74)];
				tempBreak.b[2] = SPI_LEVERS[((i+firstString) * 4) + 2 + (currentLeverBufferL * 74)];
				tempBreak.b[3] = SPI_LEVERS[((i+firstString) * 4) + 3 + (currentLeverBufferL * 74)];
				stringMIDIPitches[i] = tempBreak.f;

#if 0
				if (voice == 0)
				{
					tLivingString2_setPickupPos(&strings[i], .9999f);
				}

				if ((voice == 0) || (voice == 1))
				{
					tADSRT_setDecay(&fenvelopes[i], params[7] * 1000.0f);//noise env
					tADSRT_setDecay(&envelopes[i][0], params[0] * 50000.0f);//other env
					tADSRT_setDecay(&envelopes[i][1], params[2] * 50000.0f);//filter env
					tCycle_setFreq(&LFOs[i][0], (params[5 ] * 2.0f) + LFOdetunes[i][0]);
				}
#endif
			}

			for (int i = 0; i < 4; i++)
			{
				tExpSmooth_setDest(&knobSmoothers[i], (SPI_LEVERS[(i + 49) + (currentLeverBufferL * 74)] * 0.0078125)); //   divided by 128
			}

			int modeBit = SPI_LEVERS[48 + (currentLeverBufferL * 74)];

			neck = (modeBit >> 6) & 1;
			dualSlider = (modeBit >> 5) & 1;

			edit = (modeBit >> 4) & 1;
			voice = SPI_LEVERS[55 + (currentLeverBufferL * 74)];

			octave = (((int32_t) (modeBit & 15) - 1 ) * 12.0f);
			octaveIndex = (modeBit & 15);
			//octave = powf(2.0f,((int32_t) (modeBit & 3) - 1 ));

			volumePedalInt = ((uint16_t)SPI_LEVERS[53 + (currentLeverBufferL * 74)] << 8) + ((uint16_t)SPI_LEVERS[54 + (currentLeverBufferL * 74)] & 0xff);
			volumePedal = volumePedalInt * 0.0002442002442f;
			tExpSmooth_setDest(&volumeSmoother,volumePedal);
		}
	}

	if (codecReady)
	{

		for (int i = 0; i < (HALF_BUFFER_SIZE); i += 2)
		{
			float theSamples[2];
			theSamples[0] = ((float)(audioInBuffer[buffer_offset + i] << 8)) * INV_TWO_TO_31;
			theSamples[1] = ((float)(audioInBuffer[buffer_offset + i + 1] << 8)) * INV_TWO_TO_31;

			audioOutBuffer[buffer_offset + i] = (int32_t)(theSamples[1] * TWO_TO_23);
			audioOutBuffer[buffer_offset + i + 1] = (int32_t)(theSamples[0] * TWO_TO_23);
		}

	}

}



uint32_t audioTick(float* samples)
{
/*
	for (int i = 0; i < 12; i++)
	{
		pedalScaled[i] = tExpSmooth_tick(&pedalSmoothers[i]);
	}
*/
	samples[0]= 0.0f;

	float volumeSmoothed = tExpSmooth_tick(&volumeSmoother);

	for (int i = 0; i < 4; i++)
	{
		knobScaled[i] = tExpSmooth_tick(&knobSmoothers[i]);
	}

	for (int i = 0; i < NUM_STRINGS_PER_BOARD; i++)
	{
		stringFrequencies[i] = tExpSmooth_tick(&stringFreqSmoothers[i]);
	}

	if (newPluck)
	{
		for (int i = 0; i < NUM_STRINGS_PER_BOARD; i++)
		{
			if ((previousStringInputs[i] == 0) && (stringInputs[i] > 0))
			{

				float amplitz = stringInputs[i] * 0.00005f;
				amplitz = LEAF_clip(0.0, amplitz, 1.0f);
				//float amplitz = stringInputs[i] * 0.000015259021897f;
				//tExpSmooth_setVal(&smoother[i], amplitz);
				//tExpSmooth_setDest(&smoother[i], 0.0f);
				stringOctaveIndex[i] = octaveIndex;
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
			}
			else if ((previousStringInputs[i] > 0) && (stringInputs[i] == 0))
			{
				//note off
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
			}
			previousStringInputs[i] = stringInputs[i];
		}
		newPluck = 0;
	}


	float volIdx = LEAF_clip(47.0f, ((volumeSmoothed * 80.0f) + 47.0f), 127.0f);
	int volIdxInt = (int) volIdx;
	float alpha = volIdx-volIdxInt;
	int volIdxIntPlus = (volIdxInt + 1) & 127;
	float omAlpha = 1.0f - alpha;
	float out = volumeAmps128[volIdxInt] * omAlpha;
	out += volumeAmps128[volIdxIntPlus] * alpha;



	for (int i = 0; i < NUM_STRINGS_PER_BOARD; i++)
	{
		float tempSamp = 0.0f;

		//tCycle_setFreq(&sines[i], stringFrequencies[i] * octaveRatios[stringOctaveIndex[i]]);
		//tempSamp = tCycle_tick(&sines[i]);


		samples[0] += tempSamp;
	}

	//samples[0] *= out; //put back in!!!!!!!!!!!!!!!!!

	samples[0] = (samples[0] * 0.25f);
	samples[1] = samples[0];
	return 0;
}


void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi == &hspi5)
	{
		currentPluckBuffer = 1;

		if ((SPI_PLUCK_RX[0 + (26*currentPluckBuffer)] == 254) && (SPI_PLUCK_RX[25 + (26*currentPluckBuffer)] == 253))
		{

			for (int i = 0; i < NUM_STRINGS_PER_BOARD; i++)
			{

				stringInputs[i] = (SPI_PLUCK_RX[((i+firstString)*2)+ 1 + (26*currentPluckBuffer)] << 8) + SPI_PLUCK_RX[((i+firstString)*2)+ 2 + (26*currentPluckBuffer)];
			}
		}
		newPluck = 1;
		HAL_SPI_Receive_DMA(&hspi5, SPI_PLUCK_RX, 52);
	}
	if (hspi == &hspi2)
	{
		/*
		for (int i = 0; i < 8; i++)
		{
			bar[i] = SPI_RX[i+8];
		}
		*/
		newBar = 1;
		currentBarBuffer = 1;
	}

	if (hspi == &hspi1)
	{

		/*
		for (int i = 0; i < 74; i++)
		{
			levers[1][i] = SPI_LEVERS[i];
		}
		*/
		newLevers = 1;
		currentLeverBuffer = 1;
	}
}

void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi == &hspi5)
	{

		currentPluckBuffer = 0;
		if ((SPI_PLUCK_RX[0 + (26*currentPluckBuffer)] == 254) && (SPI_PLUCK_RX[25 + (26*currentPluckBuffer)] == 253))
		{

			for (int i = 0; i < NUM_STRINGS_PER_BOARD; i++)
			{

				stringInputs[i] = (SPI_PLUCK_RX[((i+firstString)*2)+ 1 + (26*currentPluckBuffer)] << 8) + SPI_PLUCK_RX[((i+firstString)*2)+ 2 + (26*currentPluckBuffer)];
			}
		}
		newPluck = 1;

	}
	if (hspi == &hspi2)
	{
		/*
		for (int i = 0; i < 8; i++)
		{
			bar[i] = SPI_RX[i];
		}
		*/
		newBar = 1;
		currentBarBuffer = 0;
	}
	if (hspi == &hspi1)
	{
		/*
		for (int i = 0; i < 74; i++)
		{
			levers[0][i] = SPI_LEVERS[i];
		}
		*/
		newLevers = 1;
		currentLeverBuffer = 0;
	}
}


void HAL_SAI_ErrorCallback(SAI_HandleTypeDef *hsai)
{
}

void HAL_SAI_TxCpltCallback(SAI_HandleTypeDef *hsai)
{

}

void HAL_SAI_TxHalfCpltCallback(SAI_HandleTypeDef *hsai)
{

}


void HAL_SAI_RxCpltCallback(SAI_HandleTypeDef *hsai)
{
	audioFrame(HALF_BUFFER_SIZE);
}

void HAL_SAI_RxHalfCpltCallback(SAI_HandleTypeDef *hsai)
{
	audioFrame(0);
}
