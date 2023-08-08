/* ============================================================================
 * File Name: QuadDecoder_SW
 *   Version 0.2 (build 20_8)
 *
 * Description:
 *   Software implementation of quadrature decoder for rotary shaft encoders
 *   Implements quadrature decoder for rotary shaft encoders.
 *   Returns position and direction of rotation.
 *   8-bit, 16-bit, 32-bit, single or double position range.
 *   Optional button switch with debouncing.
 *   Optional increment step size.
 *   Optional range limits.
 *   Uses interrupt or polling technique.
 *
 * Credits:
 *   based on original algorithm by M. Kellett, Interfacing Micro-controllers with Incremental Shaft Encoders
 *   http://www.mkesc.co.uk/ise.pdf
 *
 * Note:
 *
 * ============================================================================
 * PROVIDED AS-IS, NO WARRANTY OF ANY KIND, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * FREE TO SHARE, USE AND MODIFY UNDER TERMS: CREATIVE COMMONS - SHARE ALIKE
 * ============================================================================
*/


#ifndef Decoder_1_H
#define Decoder_1_H
 
    
#include <project.h>
#include <cytypes.h>

    
#define SW_DEBOUNCE_TIME (50u)          // button switch debounce time (clock ticks) 
 
          
#define true  1
#define false 0


/***************************************
*        read-only parameters
***************************************/  
#define Decoder_1_EncoderRange  1   // position range type
#define Decoder_1_StartPosition 0   // preset position
#define Decoder_1_BtnEnable     false   // enable button switch 
#define Decoder_1_InvertDir     false   // forward/reverse direction
#define Decoder_1_IsrMode       true      // polling / interrupt to check pins state
#define Decoder_1_IsrInternal   true  // internal / external timer interrupt to check pins state   
#define Decoder_1_InputsPullUp  true   // pillUp / hiZ input pins drive mode  
    

// must use Decoder_1_ prefix to coexist multiple 'er_t' types in the project 
// use encoder built-in range types: int8_t, int16_t, int32_t, uint8_t, uint16_t, uint32_t, single, double        
#define Decoder_1_er_t int8_t // int8_t, uint8_t, ..., uint32_t, float32(single), float64(double)


/***************************************
*        global variables
***************************************/  
    
uint8 Decoder_1_Enabled;             // decoder enabled / disabled (button excluding) 



/***************************************
*        read-only variables
***************************************/  

// encapsulation->  
#define Decoder_1_BtnPressed      Decoder_1_GetBtnPressed()      // flag
#define Decoder_1_PositionChanged Decoder_1_GetPositionChanged() // flag    
#define Decoder_1_Position        Decoder_1_GetPosition()        // current position // todo: check read-only?
#define Decoder_1_Direction       Decoder_1_GetDirection()       // get last rotation direction:  +1 or -1 
#define Decoder_1_Initialized     Decoder_1_GetInitStatus()      // started / stopped    
#define Decoder_1_Increment       Decoder_1_GetIncrement()       // get position increment step
#define Decoder_1_CheckBounds     Decoder_1_GetCheckBounds()     // get check bounds flag 
#define Decoder_1_LowerBound      Decoder_1_GetLowerBound()      // get position lower bound
#define Decoder_1_UpperBound      Decoder_1_GetUpperBound()      // get position upper bound


    
/***************************************
*        Function Prototypes
***************************************/

void  Decoder_1_Start();                 // start encoder
void  Decoder_1_Stop();                  // stop encoder
uint8 Decoder_1_GetInitStatus();         // return started/stopped status

int8  Decoder_1_CheckStatus();           // return:  -1=CCW, 1=CW // rename as _PositionChange (?)
//int8  Decoder_1_CheckRotation();         // rotation:  -1=CCW, 0=NAN, 1=CW (pol: 69->55 tic)
void  Decoder_1_ClearInterrupt();        // clear pins interrupts 

Decoder_1_er_t  Decoder_1_GetPosition();           // get current encoder position
int8                   Decoder_1_GetDirection();          // last rotation direction:  -1=CCW, 1=CW, 0-none 
uint8                  Decoder_1_GetPositionChanged();    // return position changed flag
uint8                  Decoder_1_GetBtnPressed();         // read button pressed flag 
uint8                  Decoder_1_GetCheckBounds();        // return CheckBounds 
Decoder_1_er_t  Decoder_1_GetIncrement();          // return Increment
Decoder_1_er_t  Decoder_1_GetLowerBound();         // return LowerBound
Decoder_1_er_t  Decoder_1_GetUpperBound();         // return UpperBound

uint8 Decoder_1_SetPosition(Decoder_1_er_t value);            // set enoder position
uint8 Decoder_1_SetCheckBounds (uint8 value);                        // set check bounds property
uint8 Decoder_1_SetIncrement(Decoder_1_er_t value);           // set position increment
uint8 Decoder_1_SetBounds(Decoder_1_er_t lBound, Decoder_1_er_t uBound); // set bounds
uint8 Decoder_1_Setup(Decoder_1_er_t position, Decoder_1_er_t increment, Decoder_1_er_t lBound, Decoder_1_er_t uBound, uint8 bounds); // set all parameters

    
#endif /* Decoder_1_H */

/* [] END OF FILE */


