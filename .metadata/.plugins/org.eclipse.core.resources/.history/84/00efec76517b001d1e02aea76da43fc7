/*
 * audiostream.c
 *
 *  Created on: Aug 30, 2019
 *      Author: jeffsnyder
 */


/* Includes ------------------------------------------------------------------*/
#include "audiostream.h"
#include "main.h"
#include "leaf.h"
#include "codec.h"
#include "i2c.h"
#include "gpio.h"
#include "spi.h"
#include "wavetables.h"

//the audio buffers are put in the D2 RAM area because that is a memory location that the DMA has access to.
int32_t audioOutBuffer[AUDIO_BUFFER_SIZE] __ATTR_RAM_D2;
int32_t audioInBuffer[AUDIO_BUFFER_SIZE] __ATTR_RAM_D2;

//#define DISPLAY_BLOCK_SIZE 512
//float audioDisplayBuffer[128];
//uint8_t displayBufferIndex = 0;
//float displayBlockVal = 0.0f;
//uint32_t displayBlockCount = 0;
char small_memory[SMALL_MEM_SIZE];
char medium_memory[MED_MEM_SIZE] __ATTR_RAM_D1;
char large_memory[LARGE_MEM_SIZE] __ATTR_SDRAM;
tMempool mediumPool;
tMempool largePool;

void audioFrame(uint16_t buffer_offset);
uint32_t audioTick(float* samples);
void buttonCheck(void);

HAL_StatusTypeDef transmit_status;
HAL_StatusTypeDef receive_status;

uint32_t codecReady = 0;

uint32_t frameCounter = 0;

int stringPositions[2];

tNoise myNoise;
int newPluck = 0;
int newBar = 0;

uint8_t pluck[26];
uint8_t bar[8];

uint32_t clipCounter[4] = {0,0,0,0};
uint32_t clipped[4] = {0,0,0,0};
uint32_t clipHappened[4] = {0,0,0,0};

#define DECAY_EXP_BUFFER_SIZE 1024
float decayExpBufferSizeMinusOne = 1023;
float decayExpBuffer[DECAY_EXP_BUFFER_SIZE];

int previousStringInputs[12];

float pedalsInCents[10][12] =
{
		{-16.0f, 0.0f, 0.0f, 0.0f, 184.0f, 0.0f,  -16.0f, 0.0f, 0.0f,  184.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 116.0f, 0.0f, 0.0f, 116.0f, 0.0f, 0.0f,  -14.0f, 0.0f, 116.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, -16.0f, 0.0f, 184.0f, 184.0f, 0.0f, 0.0f, -16.0f},
		{-1200.0f, 0.0f, 0.0f, 0.0f, -1200.0f, -1200.0f, -1200.0f, -1200.0f, -1200.0f, -1200.0f},
		{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 186.0f},
		{0.0f, 0.0f, 0.0f, -112.0f, 0.0f, 0.0f, 0.0f, -112.0f, 0.0f, 0.0f, 0.0f, -112.0f},
		{0.0f, 0.0f,  0.0f, 78.0f, 0.0f, 0.0f,  0.0f, 78.0f, 0.0f, 0.0f, 0.0f, 78.0f},
		{0.0f, 0.0f, -112.0f, 0.0f, 0.0f, 0.0f, -112.0f, 0.0f, 0.0f, 0.0f, 0.0f, -112.0f},
		{0.0f, 0.0f, -112.0f, 0.0f, 0.0f, 0.0f, -112.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, -112.0f, 0.0f, 0.0f, 0.0f, -112.0f, 0.0f, 0.0f, 0.0f}
};

float pedals[10][12] =
{
		{1.122462f, 1.0f, 1.0f, 1.0f, 1.0f, 1.122462f, 1.0f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f, 1.059463f, 1.0f, 1.0f, 1.059463f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.122462f, 1.122462f, 1.0f, 1.0f, 1.0f},
		{0.66742f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.059463f},
		{1.0f, 0.943874f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.890899f, 1.0f},
		{1.0f, 1.0f, 1.059463f, 1.0f, 1.0f, 1.0f, 1.059463f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 0.943874f, 1.0f, 1.0f, 1.0f, 0.943874f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 0.943874f, 1.0f, 1.0f, 1.0f, 0.943874f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 0.943874f, 1.0f, 1.0f, 1.0f, 0.943874f, 1.0f, 1.0f, 1.0f}
};

float partials[18] = {0.073f, 0.164f, 0.19f, 0.181f, 0.151f, 0.103f, 0.0684f, 0.053f, 0.046f, 0.032f, 0.024f, 0.021f, 0.0198f, 0.011f, 0.0114f, 0.0137f, 0.0139f, 0.0101f};
float partialsHigh[18] = {0.092f, 0.312f, 0.311f, 0.299f, 0.3125f, 0.13f, 0.054f, 0.028f, 0.012f, 0.0077f, 0.0018f, 0.003f, 0.0024f, 0.002415f, 0.00145f, 0.00103f, 0.0001f, 0.0014f};
float partialDecays[18] = {49.54f, 41.0f, 32.7f, 19.0f, 16.65f, 12.2f, 8.25f, 6.55f, 6.59f, 4.8f, 4.549f, 3.75f, 3.54f, 2.7f, 1.9f, 2.05f, 1.9f, 1.65f};
float partialDecaysHigh[18] = {15.7f, 11.8f, 9.7f, 8.95f, 7.3f, 4.6f, 4.9f, 4.32f, 2.9f, 2.34f, 1.23f, 2.5f, 2.211f, 1.94f, 1.77f, 0.71f, 0.1f, 0.05f};



float stringPartialGains[3][3][12] =
{
		{
				{0.039156f, 0.08295f, 0.100061f, 0.09995f, 0.04556f, 0.0177f, 0.04025f, 0.055531f, 0.051128f, 0.031538f, 0.016563f, 0.0112f},
				{0.151324f, 0.162346f, 0.061834f, 0.06991f, 0.0562f, 0.012482f, 0.014779f, 0.02f, 0.005216f, 0.010173f, 0.0f, 0.0f},
				{0.457762f, 0.17526f, 0.06247f, 0.05275f, 0.01362f, 0.0f, 0.002040f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}
		},
		{
				{0.030473f, 0.054897f, 0.065547f, 0.056177f, 0.02957f, 0.02767f, 0.028027f, 0.034652f, 0.026227f, 0.0144f, 0.006086f, 0.0027f},
				{0.102318f, 0.102264f, 0.04869f, 0.056057f, 0.025617f, 0.005731f, 0.04339f, 0.00369f, 0.004151f, 0.002016f, 0.001106f, 0.00528f},
				{0.2387f, 0.080883f, 0.01353f, 0.013997f, 0.004522f, 0.00f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}
		},
		{
				{0.05561f, 0.10098f, 0.12085f, 0.095168f, 0.04267f, 0.0135f, 0.014507f, 0.015348f, 0.010175f, 0.005007f, 0.002371f, 0.000964f},
				{0.15764f, 0.225206f, 0.0948f, 0.023891f, 0.007234f, 0.001718f, 0.001173f, 0.00106f, 0.001278f, 0.0f, 0.0f, 0.0f},
				{0.3303f, 0.0314f, 0.002494f, 0.002405f, 0.00362f, 0.000148f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}
		}
};

float stringDecays[3][3][12] =
{
		{
				{35.67f, 33.9234f, 18.64f, 15.892f, 12.619274f, 9.99546f, 7.434127f, 5.322585f, 5.60995f, 4.847801f, 3.186f, 2.8237f},
				{12.83f, 8.75f, 7.2341f, 5.26f, 4.023f, 2.43639f, 1.3249f, 2.28643f, 2.086553f, 1.18f, 0.9f, 0.8f},
				{6.422086f, 2.9616f, 1.636757f, 1.549297f, 0.924518f, 0.5f, 0.249887f, 0.1f, 0.05f, 0.05f, 0.05f, 0.05f}
		},
		{
				{23.38936f, 21.62787f, 14.968f, 12.094512f, 7.996f, 6.746f, 7.17174f, 4.94f, 4.28555f, 3.08621f, 2.5488f, 2.04907f},
				{15.018f, 10.320317f, 7.221724f, 6.184f, 3.760794f, 1.94116f, 2.561338f, 2.223991f, 1.574f, 1.0494f, 1.43f, 0.5994f},
				{5.977f, 4.47291f, 1.56f, 1.611f, 1.211950f, 0.9f, 0.8f, 0.6f, 0.5f, 0.4f, 0.3f, 0.2f}
		},
		{
				{15.64294f, 11.2199f, 8.171f, 7.371655f, 5.559978f, 4.685f, 1.91163f, 2.886f, 2.8612f, 2.1999f, 1.774915f, 0.63721},
				{8.17129f, 7.534f, 4.435f, 3.148471f, 1.8866f, 1.17f, 1.13f, 0.9495f, 0.912f, 0.6f, 0.5f, 0.4f},
				{4.635f, 2.298f, 1.1369f, 0.924581f, 0.599f, 0.53725f, 0.4f, 0.3f, 0.2f, 0.2f, 0.2f, 0.1f}
		}
};

float stringFundamentals[3][3] =
{
		{124.0f, 248.0f, 496.0f},
		{204.0f, 408.0f, 816.0f},
		{370.0f, 740.0f, 1480.0f}
};


float volumeDBs[28] = {-65.0f, -64.5f, -63.0f, -62.0f, -60.0f, -57.0f, -54.0f, -51.0f, -48.0f, -43.5f, -40.0f, -36.5f, -32.5f, 29.5f, 25.5f, 22.0f, 19.5f, 17.0f, 13.0f, 11.0f, 9.0f, 7.5f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.5f};
float volumeAmps[32] = {0.000562, 0.000588f, 0.000681f, 0.000756f, 0.000893f, 0.001136f, 0.001534f, 0.002066f, 0.002787f, 0.003709f, 0.005861f, 0.008554f, 0.012205f, 0.017569f, 0.025546f, 0.034485f, 0.051635f, 0.074325f, 0.096874f, 0.124266f, 0.174301f, 0.242202f, 0.292789f, 0.357063f, 0.412346f, 0.535042f, 0.606178f, 0.670620f, 0.740974f, 0.818682f, 0.900177f, 0.944061f};

float volumeAmps128[128] = {0.000562, 0.000569, 0.000577, 0.000580, 0.000587, 0.000601, 0.000622, 0.000650, 0.000676, 0.000699, 0.000720, 0.000739, 0.000753, 0.000766, 0.000791, 0.000826, 0.000872, 0.000912, 0.000953, 0.001012, 0.001091, 0.001188, 0.001270, 0.001360, 0.001465, 0.001586, 0.001717, 0.001829, 0.001963, 0.002118, 0.002295, 0.002469, 0.002636, 0.002834, 0.003063, 0.003322, 0.003496, 0.003750, 0.004143, 0.004675, 0.005342, 0.005880, 0.006473, 0.007122, 0.007827, 0.008516, 0.009167, 0.009968, 0.010916, 0.012014, 0.012944, 0.013977, 0.015352, 0.017070, 0.019130, 0.020965, 0.022847, 0.024823, 0.026891, 0.028835, 0.030496, 0.033044, 0.036478, 0.040799, 0.045093, 0.049150, 0.053819, 0.059097, 0.064986, 0.070712, 0.076315, 0.081930, 0.087560, 0.093117, 0.098283, 0.104249, 0.111012, 0.118575, 0.124879, 0.131163, 0.141721, 0.156554, 0.175663, 0.195870, 0.213414, 0.228730, 0.241817, 0.252675, 0.264038, 0.276776, 0.290871, 0.306323, 0.322794, 0.338528, 0.353711, 0.368343, 0.382424, 0.393015, 0.406556, 0.426763, 0.453639, 0.487182, 0.522242, 0.550876, 0.573000, 0.588613, 0.598943, 0.613145, 0.628104, 0.643820, 0.660293, 0.676658, 0.692845, 0.709881, 0.727766, 0.746500, 0.764505, 0.782949, 0.802346, 0.822696, 0.844189, 0.867268, 0.886360, 0.901464, 0.912581, 0.921606, 0.932834, 0.944061};
volatile int errorCount = 0;

float dAp[3][2][12];

float dAi[3][2][12];

float dBs[3][2][12];

float stringFundamentalsMIDI[3][3];

float randomFactors[256];

BOOL bufferCleared = TRUE;

int numBuffersToClearOnLoad = 2;
int numBuffersCleared = 0;

#define NUM_STRINGS 12
#define NUM_OSCS 1
#define NUM_ENVS 3
#define NUM_STRINGS_PER_BOARD 4
volatile int firstString = 0;
volatile int lastString = 0;
volatile int lastStringPlusOne = 0;
#define NUM_LFOS 3
tADSRT envelopes[NUM_STRINGS_PER_BOARD][NUM_ENVS];
tADSRT fenvelopes[NUM_STRINGS_PER_BOARD];
tSawtooth saws[NUM_STRINGS_PER_BOARD];
tSawtooth Ssaws[NUM_STRINGS_PER_BOARD][NUM_OSCS];
tCycle sines[NUM_STRINGS_PER_BOARD];
tCycle LFOs[NUM_STRINGS_PER_BOARD][NUM_LFOS];
tTriangle tris[NUM_STRINGS_PER_BOARD];
tLivingString2 strings[NUM_STRINGS_PER_BOARD];
tSimpleLivingString2 stringsS[NUM_STRINGS_PER_BOARD];
float theAmps[NUM_STRINGS_PER_BOARD];
tNoise myNoise;
tExpSmooth smoother[NUM_STRINGS_PER_BOARD];
tExpSmooth pitchSmoother[2];
tVZFilter filts[NUM_STRINGS_PER_BOARD];
tVZFilter noiseFilt;
tVZFilter noiseFilt2;
tExpSmooth pedalSmoothers[12];
tExpSmooth stringFreqSmoothers[NUM_STRINGS_PER_BOARD];
tRosenbergGlottalPulse pulse[NUM_STRINGS_PER_BOARD];
tExpSmooth volumeSmoother;
tExpSmooth knobSmoothers[4];
tCycle mySine[NUM_STRINGS_PER_BOARD][2];
tEfficientSVF filts2[NUM_STRINGS_PER_BOARD];
tPBPulse pulseW[NUM_STRINGS_PER_BOARD];
tFeedbackLeveler levelers[NUM_STRINGS_PER_BOARD][2];

tCycle additive[NUM_STRINGS_PER_BOARD][18];
tADSRT additiveEnv[NUM_STRINGS_PER_BOARD][18];


tWaveTable therT;
tWaveSynth wt[NUM_STRINGS_PER_BOARD];
tWaveTable wtab[5][73];
//int tableSizes[] = {26, 32, 73, 32, 22, 11, 64, 19};
int tableSizes[] = {26, 32, 73, 64, 19};
LEAF leaf;
int amHere = 0;



float LFOdetunes[NUM_STRINGS_PER_BOARD][3];

union breakFloat{
	float f;
	uint8_t b[4];
};

#define NUM_OVERTONES 11

float pedalValuesInt[12];
float pedalScaled[12];
int pedalOffset = 6;
uint maxVolumes[NUM_STRINGS];
float invMaxVolumes[NUM_STRINGS];
uint stringInputs[NUM_STRINGS];
//float openStringMidinotes[NUM_STRINGS] = {47.02f, 50.18f, 52.0f, 54.04f, 55.86f, 59.02f, 64.0f, 67.86f, 62.88f, 66.04f, 78.0f, 79.0f};
float openStringMidinotes[NUM_STRINGS] = {66.04f,62.88f,67.86f, 64.0f,59.02f, 55.86f, 54.04f, 52.0f, 50.18f,  47.02f, 43.86,  40.0f };

float openStringFrequencies[NUM_STRINGS] = {123.470825f, 146.832384f, 164.813779f, 184.997211f, 207.652349f, 246.941651f, 329.627557f, 415.304698f, 311.126984f, 369.994423f,440.0f, 480.0f};
float octave = 1.0f;

float stringMappedPositions[NUM_STRINGS];
float stringFrequencies[NUM_STRINGS];
float detunes[NUM_OSCS] = {1.0f, .996f, 1.002f, .999f, 1.0054, 0.998f};

uint8_t currentRandom;
float prevSamp[NUM_STRINGS];
float sympathetic = 0.000001f;
float volumePedal = 0.0f;
float knobScaled[4];
float stringMIDIPitches[NUM_STRINGS_PER_BOARD];
//TODO:
// frets are measured at 3 7 12 and 19   need to redo these measurements with an accurately set capo
float fretMeasurements[4][2] ={
		{52703.0f, 62473.0f},
		{33446.0f, 41091.0f},
		{23331.0f, 30345.0f},
		{7712.0f, 13618.0f}
	};

float fretScaling[4] = {1.0f, 0.6666666666666f, 0.5f, 0.25f};

float decayAf1[18];
float decayBs[18];
float decayAfParts[18];


float totalGain_s[3][3];
float gainNormalizers_s[3][3];
float stringOctave[NUM_STRINGS];
int voice = 0;
int dualSlider = 0;
int neck = 0;
float invNumOvertones;
float params[16];
float totalGain[2] = {0.0f, 0.0f};
float gainNormalizers[2] = {0.0f, 0.0f};

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

	invNumOvertones = 1.0f / NUM_OVERTONES;


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			stringFundamentalsMIDI[i][j] = LEAF_frequencyToMidi(stringFundamentals[i][j]);
		}
	}


	for (int i = 0; i < NUM_OVERTONES; i++)
	{
		totalGain[0] += partials[i];
		totalGain[1] += partialsHigh[i];

		for (int j = 0; j < 3; j++)

		{
			for (int k = 0; k < 3; k++)
			{
				totalGain_s[j][k] += stringPartialGains[j][k][i];
			}
		}

	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			gainNormalizers_s[i][j] = 1.0f / totalGain_s[i][j];
		}
	}
	gainNormalizers[0] = 1.0f / totalGain[0];
	gainNormalizers[1] = 1.0f / totalGain[1];


	for (int i = 0; i < NUM_OVERTONES; i++)
	{
		partials[i] = partials[i] * gainNormalizers[0];
		partialsHigh[i] = partialsHigh[i] * gainNormalizers[1];


		for (int j = 0; j < 3; j++)

		{
			for (int k = 0; k < 3; k++)
			{
				stringPartialGains[j][k][i] *= gainNormalizers_s[j][k];
			}
		}

	}

	for (int i = 0; i < NUM_OVERTONES; i++)
	{
		  decayAfParts[i] = (((1.0f/partialDecaysHigh[i])-(1.0f/partialDecays[i])) * 0.004048582995951f);  // divided by 370-123 = 247. value is 1/247

		  decayAf1[i] = decayAfParts[i] * 123.0f;

		  decayBs[i] = (1.0f/partialDecays[i]) - decayAf1[i];

		  for (int j = 0; j < 3; j++)
		  {

			  for (int k = 0; k < 2; k++)
			  {
				  float tempDivisor = (stringFundamentals[j][k+1] -  stringFundamentals[j][k]);
				  dAp[j][k][i] = ((1.0f / stringDecays[j][k+1][i]) - (1.0f / stringDecays[j][k][i])) / tempDivisor;

				  dAi[j][k][i] = dAp[j][k][i] * stringFundamentals[j][k];

				  dBs[j][k][i] = (1.0f/stringDecays[j][k][i]) - dAi[j][k][i];
			  }
		  }

	}

	for (int i = 0; i < 256; i++)
	{
		randomFactors[i] = randomNumber() + 0.5f;
	}

	for (int j = 0; j < 5;j++)
	{
		float * thisTable;
		int howMany = 0;
		if (j == 0)
		{
			thisTable = theremin;
		}
		else if (j == 1)
		{

			thisTable = c64;
		}
		else if (j == 2)
		{

			thisTable = ePiano;
		}
		else if (j == 3)
		{

			//thisTable = sg5;
			thisTable = fmPluck;
		}
		else if (j == 4)
		{

			//thisTable = sg11;
			//thisTable = formantSaw;
			thisTable = fmPluck;
		}

		howMany = tableSizes[j];
		for (int i = 0; i < howMany; i++)
		{
				//tWaveTable_initToPool(&wtab[j][i], thisTable + (2048*i), 2048, 20000.0f, &largePool);
		}
	}

	for (int i = 0; i < NUM_STRINGS_PER_BOARD; i++)
	{
		//tWaveSynth_init(&wt[i], wtab[0], 2048, tableSizes[0], 20000.0f, &leaf);
		//tWaveSynth_setAntiAliasing(&wt[i], 1.0f);

		for (int j = 0; j < NUM_OVERTONES; j++)
		{
			tCycle_init(&additive[i][j], &leaf);
			tADSRT_init(&additiveEnv[i][j], 5.0f, partialDecays[j] * 1000.0f, 0.0f, 150.0f, decayExpBuffer, DECAY_EXP_BUFFER_SIZE, &leaf);
		}

		//tRosenbergGlottalPulse_init(&pulse[i], &leaf);
		tEfficientSVF_init(&filts2[i], SVFTypeLowpass, 4000, 0.5f, &leaf);
		//tRosenbergGlottalPulse_setOpenLengthAndPulseLength(&pulse[i], 0.5f, 0.4f);
		//tSawtooth_initToPool(&saws[i], &mediumPool);
		/*
		for (int j = 0; j < NUM_OSCS; j++)
		{
			tSawtooth_initToPool(&Ssaws[i][j], &mediumPool);
		}
		*/
		//tCycle_initToPool(&sines[i], &mediumPool);
		//tTriangle_initToPool(&tris[i], &mediumPool);
		//tSawtooth_setFreq(&saws[i], 110.0f * ((float)i+1.0f));
		//tSimpleLivingString2_initToPool(&stringsS[i], 100.0f, .9f, 0.9999f, .0f, 0.01f, 0.01f, 0, &largePool);
		tLivingString2_initToPool(&strings[i], 100.0f, 0.6f, 0.3f, .9f, 0.0f, .9999f, .9999f, 0.0f, 0.05f, 0.05f, 1, &largePool);
		tLivingString2_setBrightness(&strings[i], .99f);
		tLivingString2_setPickPos(&strings[i], .5f);
		tLivingString2_setPrepPos(&strings[i], .4f);
		tLivingString2_setPrepIndex(&strings[i], 0.0f);
		tLivingString2_setPickupPos(&strings[i], 1.0f);
		tExpSmooth_init(&smoother[i],0.0f, 0.002f, &leaf);
		tVZFilter_init(&filts[i], Lowpass, 8000.0f, 6.1f, &leaf);

		tADSRT_init(&fenvelopes[i], 0.0f,  50.0f, 0.0f, 200.0f, decayExpBuffer, DECAY_EXP_BUFFER_SIZE, &leaf);
		tExpSmooth_init(&stringFreqSmoothers[i],1.0f, 0.01f, &leaf);
		tPBPulse_init(&pulseW[i], &leaf);
		for (int j = 0; j < NUM_LFOS; j++)
		{
			tCycle_init(&LFOs[i][j], &leaf);
			LFOdetunes[i][j] = randomNumber() * 0.4f;
		}
		for (int j = 0; j < NUM_ENVS; j++)
		{
			tADSRT_init(&envelopes[i][j], 5.0f, 300.0f, 0.0f, 200.0f, decayExpBuffer, DECAY_EXP_BUFFER_SIZE, &leaf);
			tADSRT_setLeakFactor(&envelopes[i][j], 0.999999f);
		}
		for (int j = 0; j < 2; j++)
		{
			tCycle_init(&mySine[i][j], &leaf);
			tCycle_setFreq(&mySine[i][j], (randomNumber() * 0.1f) + 0.001f);
			tFeedbackLeveler_init(&levelers[i][j], 1.0f, 0.01f, 0.01f, 0, &leaf);
		}
		openStringFrequencies[i] = mtof(openStringMidinotes[i]);
	}
	tVZFilter_init(&noiseFilt, BandpassPeak, 1500.0f, 1.5f, &leaf);
	tVZFilter_init(&noiseFilt2, Lowpass, 800.0f, 0.9f, &leaf);
	for (int i = 0; i < 12; i++)
	{
		tExpSmooth_init(&pedalSmoothers[i],0.0f, 0.02f, &leaf);
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < NUM_STRINGS; j++)
		{
			pedals[i][j] = pow(2.0, (pedalsInCents[i][j] / 1200.0));
		}
	}
	tExpSmooth_init(&volumeSmoother,0.0f, 0.0005f, &leaf);
	for (int i = 0; i < 4; i++)
	{
		tExpSmooth_init(&knobSmoothers[i],0.0f, 0.0005f, &leaf);
	}
	//loadingPreset = 1;
	//previousPreset = PresetNil;
	tNoise_init(&myNoise, WhiteNoise, &leaf);



	//HAL_Delay(100 * firstString);

	for (int i = 0; i < AUDIO_BUFFER_SIZE; i++)
	{
		audioOutBuffer[i] = 0;
	}

	HAL_Delay(1000);

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
int prevTable = 0;
void audioFrame(uint16_t buffer_offset)
{

	int i;
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
	uint32_t clipCatcher = 0;

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
		}
		newBar = 0;
	}

	if (newLevers)
	{
		int currentLeverBufferL = currentLeverBuffer;

		if ((SPI_LEVERS[72 + (currentLeverBufferL * 74)] == 254) && (SPI_LEVERS[73 + (currentLeverBufferL * 74)] == 253))
		{
			float myMappedPos = 0.0f;

			for (int i = 0; i < 16; i++)
			{
				params[i] = SPI_LEVERS[(i + 56) + (currentLeverBuffer * 74)] * 0.003921568627451f; //scaled 0.0 to 1.0

			}

			whichTable = LEAF_clip(0, SPI_LEVERS[71 + (currentLeverBuffer * 74)] >> 2, 5);

			if (whichTable != prevTable)
			{
				for (int i = 0; i < NUM_STRINGS_PER_BOARD; i++)
				{
					//tWaveSynth_setTables(&wt[i], wtab[whichTable], tableSizes[whichTable], 2048);
				}
			}
			prevTable = whichTable;
			union breakFloat tempBreak;

			for (int i = 0; i < NUM_STRINGS_PER_BOARD; i++)
			{
				if (dualSlider)
				{
					myMappedPos = LEAF_interpolation_linear(stringMappedPositions[0], stringMappedPositions[1], ((float)(i+firstString)) * 0.090909090909091f);
				}
				else
				{
					myMappedPos =  stringMappedPositions[0];
				}

				tempBreak.b[0] = SPI_LEVERS[((i+firstString) * 4) + (currentLeverBufferL * 74)];
				tempBreak.b[1] = SPI_LEVERS[((i+firstString) * 4) + 1 + (currentLeverBufferL * 74)];
				tempBreak.b[2] = SPI_LEVERS[((i+firstString) * 4) + 2 + (currentLeverBufferL * 74)];
				tempBreak.b[3] = SPI_LEVERS[((i+firstString) * 4) + 3 + (currentLeverBufferL * 74)];
				stringMIDIPitches[i] = tempBreak.f + stringOctave[i];
				float tempFreq = (1.0 / myMappedPos) * mtof(stringMIDIPitches[i]);
				tExpSmooth_setDest(&stringFreqSmoothers[i], tempFreq);
				stringMIDIPitches[i] = ftom(tempFreq);
				if (voice == 0)
				{
					tLivingString2_setPickupPos(&strings[i], params[6]);
				}
				if ((voice == 0) || (voice == 1))
				{
					tADSRT_setDecay(&fenvelopes[i], params[7] * 1000.0f);//noise env
					tADSRT_setDecay(&envelopes[i][0], params[0] * 50000.0f);//other env
					tADSRT_setDecay(&envelopes[i][1], params[2] * 50000.0f);//filter env
					tCycle_setFreq(&LFOs[i][0], (params[5 ] * 2.0f) + LFOdetunes[i][0]);
				}
			}


	/*
			for (int i = 0; i < 9; i++)
			{
				pedalValuesInt[i] = ((uint16_t)levers[currentLeverBuffer][(i * 2)] << 8) + ((uint16_t)levers[currentLeverBuffer][(i * 2) + 1] & 0xff);
				tExpSmooth_setDest(&pedalSmoothers[i], LEAF_clip(0.0f, ((pedalValuesInt[i] * 0.0002490234375f) - 0.01f), 1.0f)); //   divided by 4096 multiplied by 1.02 and subtracting 0.01 to push it a little beyond the edges.
				//pedalScaled[i] = tExpSmooth_tick(&pedalSmoothers[i]);
			}
	*/

			for (int i = 0; i < 4; i++)
			{
				tExpSmooth_setDest(&knobSmoothers[i], (SPI_LEVERS[(i + 49) + (currentLeverBufferL * 74)] * 0.0078125)); //   divided by 128
				//knobScaled[i] = tExpSmooth_tick(&knobSmoothers[i]);
			}

			int modeBit = SPI_LEVERS[48 + (currentLeverBufferL * 74)];

			neck = (modeBit >> 4) & 1;
			dualSlider = (modeBit >> 3) & 1;

			edit = (modeBit >> 2) & 1;
			voice = SPI_LEVERS[55 + (currentLeverBufferL * 74)];

			octave = (((int32_t) (modeBit & 3) - 1 ) * 12.0f);
			//octave = powf(2.0f,((int32_t) (modeBit & 3) - 1 ));

			volumePedalInt = ((uint16_t)SPI_LEVERS[53 + (currentLeverBufferL * 74)] << 8) + ((uint16_t)SPI_LEVERS[54 + (currentLeverBufferL * 74)] & 0xff);
			volumePedal = volumePedalInt * 0.0002442002442f;
			tExpSmooth_setDest(&volumeSmoother,volumePedal);
		}
	}

	if ((voice == 0) ||  (voice == 1) || (voice == 2))
	{
		tVZFilter_setFreq(&noiseFilt, faster_mtof(params[3] * 128.0f));
		tVZFilter_setFreq(&noiseFilt2,faster_mtof(params[4] * 128.0f));
	}



	for (int i = 0; i < NUM_STRINGS_PER_BOARD; i++)
	{

		if (voice == 0)
		{

			if (stringInputs[i] > 0)
			{
				tLivingString2_setLevMode(&strings[i], (params[2] > 0.5f));

				tLivingString2_setTargetLev(&strings[i], params[0]);
			}

			else
			{

				tLivingString2_setTargetLev(&strings[i], 0.0f);
				tLivingString2_setLevMode(&strings[i], 0);
			}

			tLivingString2_setLevSmoothFactor(&strings[i], params[9] * 0.1f);

			tLivingString2_setLevStrength(&strings[i], params[10] * 0.1f);

			tLivingString2_setBrightness(&strings[i], knobScaled[3]);
			tLivingString2_setPickPos(&strings[i], knobScaled[2]);

			tLivingString2_setPrepPos(&strings[i], (knobScaled[0] * 0.8f) + 0.1f);
		}
		if (voice == 3)
		{
			tADSRT_setSustain(&envelopes[i][0], params[14]);
		}

	}
	//float posDiff = stringMappedPositions[0]-stringMappedPositions[1];
/*
	for (int i = firstString; i < lastStringPlusOne; i++)
	{
		//interpolate ratios for each of the 10 strings
		//float myMappedPos = stringMappedPositions[0];
		//float myMappedPos  = stringMappedPositions[1] + ((float) i * posDiff);
		float myMappedPos = 0.0f;

		if (dualSlider)
		{
			myMappedPos = LEAF_interpolation_linear(stringMappedPositions[0], stringMappedPositions[1], ((float)i) * 0.090909090909091f);
		}
		else
		{
			myMappedPos =  stringMappedPositions[0];
		}
		//then apply those ratios to the fundamental frequencies
		float tempFreq = ((1.0 / myMappedPos) * openStringFrequencies[i] *
					(LEAF_interpolation_linear(1.0f, pedals[0][i], pedalScaled[0])) *
					(LEAF_interpolation_linear(1.0f, pedals[1][i], pedalScaled[1])) *
					(LEAF_interpolation_linear(1.0f, pedals[2][i], pedalScaled[2])) *
					(LEAF_interpolation_linear(1.0f, pedals[3][i], pedalScaled[3])) *
					(LEAF_interpolation_linear(1.0f, pedals[5][i], pedalScaled[5])) *
					(LEAF_interpolation_linear(1.0f, pedals[6][i], pedalScaled[6])) *
					(LEAF_interpolation_linear(1.0f, pedals[6][i], pedalScaled[7])) *
					(LEAF_interpolation_linear(1.0f, pedals[7][i], pedalScaled[8])));

		tExpSmooth_setDest(&stringFreqSmoothers[i], tempFreq * octave);


	}
*/


	if (codecReady)
	{

		for (i = 0; i < (HALF_BUFFER_SIZE); i += 2)
		{
			float theSamples[2];
			theSamples[0] = ((float)(audioInBuffer[buffer_offset + i] << 8)) * INV_TWO_TO_31;
			theSamples[1] = ((float)(audioInBuffer[buffer_offset + i + 1] << 8)) * INV_TWO_TO_31;

			clipCatcher |= audioTick(theSamples);
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
	float audioInput = samples[0] + samples[1];

	float volumeSmoothed = tExpSmooth_tick(&volumeSmoother);

	for (int i = 0; i < 4; i++)
	{
		knobScaled[i] = tExpSmooth_tick(&knobSmoothers[i]);
	}

	for (int i = 0; i < NUM_STRINGS_PER_BOARD; i++)
	{
		stringFrequencies[i] = tExpSmooth_tick(&stringFreqSmoothers[i]);
	}

	int currentPluckBufferL = currentPluckBuffer;

	if (newPluck)
	{
		if ((SPI_PLUCK_RX[0 + (26*currentPluckBufferL)] == 254) && (SPI_PLUCK_RX[25 + (26*currentPluckBufferL)] == 253))
		{

			for (int i = 0; i < NUM_STRINGS_PER_BOARD; i++)
			{

				stringInputs[i] = (SPI_PLUCK_RX[((i+firstString)*2)+ 1 + (26*currentPluckBufferL)] << 8) + SPI_PLUCK_RX[((i+firstString)*2)+ 2 + (26*currentPluckBufferL)];

				/*
				if (maxVolumes[i] < stringInputs[i])
				{
					maxVolumes[i] = stringInputs[i];
					invMaxVolumes[i] = 1.0f / stringInputs[i];
				}

			`	*/
				if ((previousStringInputs[i] == 0) && (stringInputs[i] > 0))
				{

					float amplitz = stringInputs[i] * 0.000125f;
					//tExpSmooth_setVal(&smoother[i], amplitz);
					//tExpSmooth_setDest(&smoother[i], 0.0f);
					stringOctave[i] = octave;



					if (voice == 0)
					{
						tADSRT_on(&envelopes[i][0], amplitz);
						tADSRT_on(&envelopes[i][1], amplitz);
						tADSRT_on(&envelopes[i][2], amplitz);
						tADSRT_on(&fenvelopes[i], 1.0f);

						tLivingString2_setLevMode(&strings[i], (params[2] > 0.5f));

						tLivingString2_setTargetLev(&strings[i], params[0]);
						int delayLength = (int)strings[i]->waveLengthInSamples;
						int beforeLength = (delayLength * knobScaled[2]);
						int afterLength = (delayLength * (1.0f - knobScaled[2]));
						float beforePickIncrement;
						float afterPickIncrement;
						float pluckAmp = amplitz * params[11] * 4.0f;
						if (beforeLength > 0)
						{
							beforePickIncrement = pluckAmp / beforeLength;
						}
						else
						{
							beforePickIncrement = pluckAmp;
						}

						if (afterLength > 0)
						{
							afterPickIncrement = pluckAmp / afterLength;
						}
						else
						{
							afterPickIncrement = pluckAmp;
						}


						float value = 0.0f;
						for (int j = 0; j < delayLength; j++)
						{
							if (j < beforeLength)
							{
								value += beforePickIncrement;
								//value = tanhf(value);
								strings[i]->delLF->buff[(j+strings[i]->delLF->outPoint) & strings[i]->delLF->bufferMask] = value * 0.5f;
								strings[i]->delLB->buff[(j+strings[i]->delLB->outPoint) & strings[i]->delLB->bufferMask] = value * 0.5f;
							}
							else
							{
								value -= afterPickIncrement;
								//value = tanhf(value);
								strings[i]->delUF->buff[(j+strings[i]->delUF->outPoint) & strings[i]->delUF->bufferMask] = value * 0.5f;
								strings[i]->delUB->buff[(j+strings[i]->delUB->outPoint) & strings[i]->delUB->bufferMask] = value * 0.5f;
							}

							//strings[i]->delayLine->buff[(j+strings[i]->delayLine->outPoint) & strings[i]->delayLine->bufferMask] = value;
						}
						tLivingString2_setDecay(&strings[i], params[1] * 80.0f);
					}
					else if ((voice == 1) || (voice == 3))
					{
						tADSRT_setDecay(&envelopes[i][0], 1.0f + (20000.0f * knobScaled[3]));
						tADSRT_setDecay(&envelopes[i][1], 1.0f + (20000.0f * knobScaled[2]));
						tADSRT_on(&envelopes[i][0], amplitz);
						tADSRT_on(&envelopes[i][1], amplitz);
						tADSRT_on(&envelopes[i][2], 1.0f);
						tADSRT_on(&fenvelopes[i], 1.0f);
					}

					else if (voice == 2)
					{
						for (int j = 0; j < NUM_OVERTONES; j++)
						{
							//float thisDecay = 1.0f / ((decayAfParts[j] * stringFrequencies[i]) + decayBs[j]);
							float thisDecay;
							//float thisGain = map(LEAF_clip(132.0f, stringFrequencies[i], 370.0f), 123.0f, 370.0f, partials[j], partialsHigh[j]);
							float d1;
							float d2;
							float thisGain;
							int thisString = i + firstString;
							float stringFade;
							float fakedFreq = stringFrequencies[i] * (knobScaled[2] * 4.0f);
							if (thisString < 6)
							{
								stringFade = (float)thisString * 0.2f;
								float height2 = LEAF_clip(0.0f, map(fakedFreq, stringFundamentals[2][0], stringFundamentals[2][2], 0.0f, 2.0f), 1.99f);
								float height1 = LEAF_clip(0.0f, map(fakedFreq, stringFundamentals[1][0], stringFundamentals[1][2], 0.0f, 2.0f), 1.99f);
								int height1Int = floor(height1);
								float height1Float = height1 - height1Int;
								int height2Int = floor(height2);
								float height2Float = height2 - height2Int;

								float x1 =  (stringPartialGains[1][height1Int][j] * (1.0f - height1Float)) + (stringPartialGains[1][height1Int + 1][j] * height1Float);
								float x2 =  (stringPartialGains[2][height2Int][j] * (1.0f - height2Float)) + (stringPartialGains[2][height2Int + 1][j] * height2Float);
								thisGain = (x1 * stringFade) + (x2 * (1.0f - stringFade));


								if (height2 < 1.0f)
								{
									d2 = 1.0f / ((dAp[2][0][j] * LEAF_clip(stringFundamentals[2][0], fakedFreq, stringFundamentals[2][1])) + dBs[2][0][j]);
								}
								else
								{
									d2 = 1.0f / ((dAp[2][1][j] * LEAF_clip(stringFundamentals[2][1], fakedFreq, stringFundamentals[2][2])) + dBs[2][1][j]);
								}

								if (height1 < 1.0f)
								{
									d1 = 1.0f / ((dAp[1][0][j] * LEAF_clip(stringFundamentals[1][0], fakedFreq, stringFundamentals[1][1])) + dBs[1][0][j]);
								}
								else
								{
									d1 = 1.0f / ((dAp[1][1][j] * LEAF_clip(stringFundamentals[1][1], fakedFreq, stringFundamentals[1][2])) + dBs[1][1][j]);
								}

								thisDecay = (d1 * stringFade) + (d2 * (1.0f - stringFade));
							}
							else
							{
								stringFade = (float)(thisString - 6.0f) * 0.2f;
								float height2 = LEAF_clip(0.0f, map(fakedFreq, stringFundamentals[1][0], stringFundamentals[1][2], 0.0f, 2.0f), 1.99f);
								float height1 = LEAF_clip(0.0f, map(fakedFreq, stringFundamentals[0][0], stringFundamentals[0][2], 0.0f, 2.0f), 1.99f);
								int height1Int = floor(height1);
								float height1Float = height1 - height1Int;
								int height2Int = floor(height2);
								float height2Float = height2 - height2Int;

								float x1 =  stringPartialGains[0][height1Int][j] + (stringPartialGains[1][height1Int + 1][j] * height1Float);
								float x2 =  stringPartialGains[1][height2Int][j] + (stringPartialGains[2][height2Int + 1][j] * height2Float);
								thisGain = (x1 * stringFade) + (x2 * (1.0f - stringFade));

								if (height2 < 1.0f)
								{
									d2 = 1.0f / ((dAp[1][0][j] * LEAF_clip(stringFundamentals[1][0], fakedFreq, stringFundamentals[1][1])) + dBs[1][0][j]);
								}
								else
								{
									d2 = 1.0f / ((dAp[1][1][j] * LEAF_clip(stringFundamentals[1][1], fakedFreq, stringFundamentals[1][2])) + dBs[1][1][j]);
								}

								if (height1 < 1.0f)
								{
									d1 = 1.0f / ((dAp[0][0][j] * LEAF_clip(stringFundamentals[0][0], fakedFreq, stringFundamentals[0][1])) + dBs[0][0][j]);
								}
								else
								{
									d1 = 1.0f / ((dAp[0][1][j] * LEAF_clip(stringFundamentals[0][1], fakedFreq, stringFundamentals[0][2])) + dBs[0][1][j]);
								}

								thisDecay = (d1 * stringFade) + (d2 * (1.0f - stringFade));
							}
							thisDecay *= 2000.0f * knobScaled[1];
							tADSRT_setDecay(&additiveEnv[i][j], thisDecay * (randomFactors[currentRandom] * 1.0f));// * randomFactors[currentRandom]);
							tADSRT_on(&additiveEnv[i][j], amplitz * (thisGain * (randomFactors[currentRandom])));
							currentRandom++;
						}
						tADSRT_setDecay(&fenvelopes[i], 250.0f * params[7] + 1.0f);
						tADSRT_on(&fenvelopes[i],  amplitz);
						tADSRT_setDecay(&envelopes[i][1], 2000.0f * params[1] + 1.0f);
						tADSRT_on(&envelopes[i][1],  params[2] * 0.1f);
					}
					//float decayTime = powf(0.001f,1.0f/(stringFrequencies[i]*myDecay));


					//tVZFilter_setFreq(&noiseFilt, faster_mtof(amplitz * 25.0f + 60.0f));
					//tVZFilter_setFreq(&noiseFilt2, faster_mtof(amplitz * 10.0f + 80.0f));

				}
				else if ((previousStringInputs[i] > 0) && (stringInputs[i] == 0))
				{


					if (voice == 0)
					{
						tLivingString2_setTargetLev(&strings[i], 0.0f);
						tLivingString2_setLevMode(&strings[i], 0);
						tLivingString2_setDecay(&strings[i], 0.1f);
						tADSRT_off(&envelopes[i][0]);
						tADSRT_off(&envelopes[i][1]);
						tADSRT_off(&envelopes[i][2]);
						tADSRT_off(&fenvelopes[i]);
					}
					else if ((voice == 1)||(voice == 3))
					{
						tADSRT_off(&envelopes[i][0]);
						tADSRT_off(&envelopes[i][1]);
						tADSRT_off(&envelopes[i][2]);
						tADSRT_off(&fenvelopes[i]);
					}
					else if (voice == 2)
					{
						for (int j = 0; j < NUM_OVERTONES; j++)
						{
							tADSRT_off(&additiveEnv[i][j]);
						}
					}

				}

				previousStringInputs[i] = stringInputs[i];
			}
		}
		newPluck = 0;
	}




	float filtNoise;
	if (voice != 3)
	{
		filtNoise = tVZFilter_tickEfficient(&noiseFilt, tNoise_tick(&myNoise));
		filtNoise += tVZFilter_tickEfficient(&noiseFilt2, tNoise_tick(&myNoise));
	}
	samples[0]= 0.0f;
	//filtNoise= tNoise_tick(&myNoise);

	for (int i = 0; i < NUM_STRINGS_PER_BOARD; i++)
	{

		float Env1 = 0.0f;
		float Env2 = 0.0f;
		float env = 0.0f;


		Env1 = tADSRT_tick(&envelopes[i][0]);

		Env2 = tADSRT_tick(&envelopes[i][1]);
				//float Env3 = tADSRT_tick(&envelopes[i][2]);
		env = tADSRT_tick(&fenvelopes[i]); //noise envelope

		float tempSamp = 0.0f;

		if (voice == 0)
		{
			tLivingString2_setFreq(&strings[i], stringFrequencies[i]);


			if (neck == 0)
			{
				tLivingString2_setPrepIndex(&strings[i], knobScaled[1] * env);
			}
			else
			{
				tLivingString2_setPrepIndex(&strings[i], knobScaled[1]);
			}


			//tCycle_setFreq(&sines[i], stringFrequencies[i]);
			//tTriangle_setFreq(&tris[i], stringFrequencies[i]);
			//tADSRT_setDecay(&fenvelopes[i], knobScaled[2] * 22000.0f);


			//float tempSamp = (tCycle_tick(&sines[i])) * 0.5f;
			/*
			for (int j = 0; j< NUM_OSCS; j++)
			{
				tSawtooth_setFreq(&Ssaws[i][j], stringFrequencies[i] * detunes[j]);

				tempSamp += (tSawtooth_tick(&Ssaws[i][j]) * 0.5f);//filtNoise * theEnv) * env);
			}
			*/
			//tempSamp = tEfficientSVF_tick(&filts2[i], tempSamp * env);
			//tLivingString2_udpateDelays(&strings[i]);
			tempSamp = (tLivingString2_tick(&strings[i],(filtNoise * env) + (audioInput * 0.001f * params[5]) + (prevSamp[i] * (0.001f * params[5]))));//filtNoise * theEnv) * env);
			prevSamp[i] = 0.0f;
			for (int j = 0; j < NUM_STRINGS_PER_BOARD; j++)
			{
				if (j != i) //put sympathetic resonance in all strings but yourself
				{
					prevSamp[j]+=tempSamp * volumeSmoothed;
				}
			}
		}
		else if (voice == 1)
		{

			tEfficientSVF_setQ(&filts2[i], (params[13] * 10.0f) + 0.5f);
			tEfficientSVF_setFreq(&filts2[i], LEAF_clip(0, (knobScaled[0]*4095.0f) + (Env2 * knobScaled[1]* 4095.0f) + (stringMIDIPitches[i] * knobScaled[2] * 32.0f), 4095));

			tPBPulse_setFreq(&pulseW[i], stringFrequencies[i]);
			tPBPulse_setWidth(&pulseW[i], tCycle_tick(&LFOs[i][0]) * 0.4f + 0.5f);
			tempSamp = tPBPulse_tick(&pulseW[i]);
			tempSamp += (filtNoise * env);
			tempSamp = tEfficientSVF_tick(&filts2[i], tempSamp);
			tFeedbackLeveler_setTargetLevel(&levelers[i][0], params[4]);
			tFeedbackLeveler_setStrength(&levelers[i][0], params[5] * 0.1f);
			tFeedbackLeveler_setFactor(&levelers[i][0], params[6] * 0.1f);
			tFeedbackLeveler_setMode(&levelers[i][0], params[8] > 0.5f);
			tempSamp = tFeedbackLeveler_tick(&levelers[i][0], tempSamp);
			tempSamp *= Env1 * knobScaled[2];
		}

		else if (voice == 2)
		{
			//env = tADSRT_tick(&fenvelopes[i]); //noise envelope
			tempSamp = filtNoise * env;
			for (int j = 0; j < NUM_OVERTONES; j++)
			{

				float thisEnv = tADSRT_tickNoInterp(&additiveEnv[i][j]);
				float tempFreq = stringFrequencies[i] * (j+1) * ((params[0]* 0.001f * j) + 1.0f) * ((Env2 * params[1])+ 1.0f);

				if (tempFreq < 18000.0f)
				{
					tCycle_setFreq(&additive[i][j], tempFreq);
					//float upRamp = (j * invNumOvertones);
					//float downRamp = 1.0f - (j * invNumOvertones);

					//float freqWeight = (upRamp * knobScaled[0]) + (downRamp * (1.0f - knobScaled[0]));
					tempSamp += tCycle_tick(&additive[i][j]) * thisEnv;// * freqWeight;
				}

			}
		}

		else if (voice == 3)
		{

			//tEfficientSVF_setQ(&filts2[i], (params[13] * 10.0f) + 0.5f);
			//tEfficientSVF_setFreq(&filts2[i], LEAF_clip(0, (knobScaled[0]*4095.0f) + (Env2 * knobScaled[1]* 4095.0f) + (stringMIDIPitches[i] * knobScaled[2] * 32.0f), 4095));
			//tWaveSynth_setFreq(&wt[i], stringFrequencies[i]);
			//tWaveSynth_setIndex(&wt[i], LEAF_clip(0.0f, 1.0f, knobScaled[0] + Env2 * knobScaled[1]));
			//tempSamp = tWaveSynth_tick(&wt[i]);
			//tempSamp += (filtNoise * env);
			//tempSamp = tEfficientSVF_tick(&filts2[i], tempSamp);
			//tFeedbackLeveler_setTargetLevel(&levelers[i][0], params[4]);
			//tFeedbackLeveler_setStrength(&levelers[i][0], params[5] * 0.1f);
			//tFeedbackLeveler_setFactor(&levelers[i][0], params[6] * 0.1f);
			//tFeedbackLeveler_setMode(&levelers[i][0], params[8] > 0.5f);
			//tempSamp = tFeedbackLeveler_tick(&levelers[i][0], tempSamp);
			//tempSamp *= Env1;
		}


		samples[0] += tempSamp;
		prevSamp[i] = tempSamp;

	}

/*
	for (int i = 5; i < 10; i++)
	{
		//tLivingString2_setPrepPos(&strings[i], knobScaled[0]);
		tLivingString2_setBrightness(&strings[i], knobScaled[0]);
		tLivingString2_setPickupPos(&strings[i], knobScaled[1]);
		tLivingString2_setPickPos(&strings[i], knobScaled[3]);
		tLivingString2_setDecay(&strings[i], knobScaled[2]);
		float theEnv = tADSRT_tick(&fenvelopes[i]);
		//tLivingString2_setPrepIndex(&strings[i], knobScaled[1] * theEnv);
		stringFrequencies[i] = tExpSmooth_tick(&stringFreqSmoothers[i]);
		float env = tADSRT_tick(&envelopes[i]);
		tLivingString2_setFreq(&strings[i], stringFrequencies[i] * octave);
        tLivingString2_udpateDelays(&strings[i]);
		float tempSamp = (tLivingString2_tickEfficient(&strings[i], filtNoise * theEnv) * env);
		samples[0] += tempSamp;
		//tSawtooth_setFreq(&saws[i], stringFrequencies[i] * 7.0f);// + (tMBSaw_tick(&saws[i]) * 100.0f));
		//float fm = tSawtooth_tick(&saws[i]);

		//for (int j = 0; j < NUM_OSCS; j++)
		//{
			//tSawtooth_setFreq(&Ssaws[i][j], stringFrequencies[i] * detunes[j]);// + (fm * 150.0f));// * (1.0f + (7.0f *  theEnv)));
		//}

		//tSimpleLivingString_setFreq(&strings[i], stringFrequencies[i]);
		//tSimpleLivingString_setDampFreq(&strings[i], LEAF_clip(50.0f, (stringFrequencies[i] * 3.0f) + 6000.0f, 23000.0f));
		//tVZFilter_setFreq(&filts[i], LEAF_clip(30.0f, stringFrequencies[i]*((1.0f-knobScaled[0]) + 0.1f) * 16.0f, 10000.0f));
		//tVZFilter_setFreq(&filts[i], LEAF_clip(10.0f, stringFrequencies[i] * (1.0f + (16 .0f * theEnv)), 5000.0f));
		//tRosenbergGlottalPulse_setFreq(&pulse[i], stringFrequencies[i] * 0.999f);
		//float lfo1 = tCycle_tick(&mySine[i][0]) * 0.3f + 0.5f;
		//tRosenbergGlottalPulse_setOpenLengthAndPulseLength(&pulse[i],(tCycle_tick(&mySine[i][1]) * 0.2f + 0.5f) * lfo1, lfo1);
	}
*/

/*
	for (int i = 0; i < 10; i++)
	{
		//tempSamp = tSaw_tick(&saws[i]) * tADSR_tick(&envelopes[i]);
		//float tempSamp = 0.0f;
		//tMBSaw_syncIn(&Ssaws[i], tMBSaw_syncOut(&saws[i]));
		//samples[0] +=  tMBSaw_tick(&saws[i]) * tADSR_tick(&envelopes[i]);


		for (int j = 0; j < NUM_OSCS; j++)
		{
			tempSamp += tSawtooth_tick(&Ssaws[i][j]) * 0.5f;
		}

		//tempSamp = tVZFilter_tickEfficient(&filts[i], tempSamp * env);
		//tempSamp = tVZFilter_tickEfficient(&filts[i], tRosenbergGlottalPulse_tickHQ(&pulse[i]) * env);
		//tempSamp += tRosenbergGlottalPulse_tick(&pulse[i]) * env;
		//samples[0] += tempSamp;
		//samples[0] +=  tSimpleLivingString_tick(&strings[i], );

		//prevSamp[i] = 0.0f;
		//for (int j = 0; j < 10; j++)
		{
			//if (j != i) //put sympathetic resonance in all strings but yourself
			{
				//prevSamp[j]+=tempSamp;
			}
		}
	}
*/

	//samples[0] = tEfficientSVF_tick(&filts2[firstString], samples[0]);


	//tempNum= (fasterdbtoa((volumeSmoothed*60.0f) - 60.0f) * 0.4f) + (volumeSmoothed * 0.6f);
	float volIdx = LEAF_clip(47.0f, ((volumeSmoothed * 80.0f) + 47.0f), 127.0f);
	int volIdxInt = (int) volIdx;
	float alpha = volIdx-volIdxInt;
	int volIdxIntPlus = (volIdxInt + 1) & 127;
	float omAlpha = 1.0f - alpha;
	float out = volumeAmps128[volIdxInt] * omAlpha;
	out += volumeAmps128[volIdxIntPlus] * alpha;
	//tCycle_setFreq(&sines[0], 342.54f);
	//tempNum =
	//samples[0] = tCycle_tick(&sines[0]);
	samples[0] *= out;
	//samples[0] =
	samples[0] = (samples[0] * 0.25f);
	//samples[0] = tanhf(samples[0] * 0.25f);
	//samples[0] *= 0.25f;
	samples[1] = samples[0];
	return 0;
}




void midiIn (uint string, uint amplitude)
{
	if (amplitude > maxVolumes[string])
	{
		maxVolumes[string] = amplitude;
	}
	if (amplitude > 0)
	{
		theAmps[string] = 1.0f;
	}
	else
	{
		theAmps[string] = 0.0f;
	}
	if (theAmps[0] > 0.0f)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
	}
}

volatile int testInt = 0;



void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi == &hspi5)
	{
		/*
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);

		for (int i = 0; i < 26; i++)
		{
			pluck[i] = SPI_PLUCK_RX[i+26];
		}
		*/
		newPluck = 1;
		currentPluckBuffer = 1;
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

/*
		if ((SPI_PLUCK_RX[0] == 254) && (SPI_PLUCK_RX[21] == 253))
		{

			for (int i = 0; i < NUM_STRINGS; i++)
			{

				stringInputs[i] = (SPI_PLUCK_RX[(i*2)+1] << 8) + SPI_PLUCK_RX[(i*2)+2];

				if (maxVolumes[i] < stringInputs[i])
				{
					maxVolumes[i] = stringInputs[i];
					invMaxVolumes[i] = 1.0f / stringInputs[i];
				}

				if ((previousStringInputs[i] == 0) && (stringInputs[i] > 0))
				{
					//attack
					float amplitz = stringInputs[i] * invMaxVolumes[i];
					//tExpSmooth_setVal(&smoother[i], 1.0f);
					//tExpSmooth_setDest(&smoother[i], 0.0f);
					tADSRT_on(&envelopes[i], amplitz);
					tADSRT_on(&fenvelopes[i], amplitz);
					//tVZFilter_setFreq(&noiseFilt, faster_mtof(amplitz * 25.0f + 60.0f));
					//tVZFilter_setFreq(&noiseFilt2, faster_mtof(amplitz * 10.0f + 80.0f));

				}
				else if ((previousStringInputs[i] > 0) && (stringInputs[i] == 0))
				{
					tADSRT_off(&envelopes[i]);
					tADSRT_off(&fenvelopes[i]);
				}

				previousStringInputs[i] = stringInputs[i];
			}
		}


	*/

}

void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi == &hspi5)
	{
		/*
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
		for (int i = 0; i < 26; i++)
		{
			pluck[i] = SPI_PLUCK_RX[i];
		}
		*/
		newPluck = 1;
		currentPluckBuffer = 0;
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
