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


#ifndef `$INSTANCE_NAME`_H
#define `$INSTANCE_NAME`_H
 
    
#include <project.h>
#include <cytypes.h>

    
#define SW_DEBOUNCE_TIME (50u)          // button switch debounce time (clock ticks) 
 
          
#define true  1
#define false 0


/***************************************
*        read-only parameters
***************************************/  
#define `$INSTANCE_NAME`_EncoderRange  `=$encoder_range `   // position range type
#define `$INSTANCE_NAME`_StartPosition `=$start_position`   // preset position
#define `$INSTANCE_NAME`_BtnEnable     `=$btn_enable    `   // enable button switch 
#define `$INSTANCE_NAME`_InvertDir     `=$invert_dir    `   // forward/reverse direction
#define `$INSTANCE_NAME`_IsrMode       `=$state_check==sc_isr`      // polling / interrupt to check pins state
#define `$INSTANCE_NAME`_IsrInternal   `=$timer_isr==isr_internal`  // internal / external timer interrupt to check pins state   
#define `$INSTANCE_NAME`_InputsPullUp  `=$input_mode==inp_pullup`   // pillUp / hiZ input pins drive mode  
    

// must use `$INSTANCE_NAME`_ prefix to coexist multiple 'er_t' types in the project 
// use encoder built-in range types: int8_t, int16_t, int32_t, uint8_t, uint16_t, uint32_t, single, double        
#define `$INSTANCE_NAME`_er_t `=GetNameForEnum("encoder_range_type", $encoder_range)` // int8_t, uint8_t, ..., uint32_t, float32(single), float64(double)


/***************************************
*        global variables
***************************************/  
    
uint8 `$INSTANCE_NAME`_Enabled;             // decoder enabled / disabled (button excluding) 



/***************************************
*        read-only variables
***************************************/  

// encapsulation->  
#define `$INSTANCE_NAME`_BtnPressed      `$INSTANCE_NAME`_GetBtnPressed()      // flag
#define `$INSTANCE_NAME`_PositionChanged `$INSTANCE_NAME`_GetPositionChanged() // flag    
#define `$INSTANCE_NAME`_Position        `$INSTANCE_NAME`_GetPosition()        // current position // todo: check read-only?
#define `$INSTANCE_NAME`_Direction       `$INSTANCE_NAME`_GetDirection()       // get last rotation direction:  +1 or -1 
#define `$INSTANCE_NAME`_Initialized     `$INSTANCE_NAME`_GetInitStatus()      // started / stopped    
#define `$INSTANCE_NAME`_Increment       `$INSTANCE_NAME`_GetIncrement()       // get position increment step
#define `$INSTANCE_NAME`_CheckBounds     `$INSTANCE_NAME`_GetCheckBounds()     // get check bounds flag 
#define `$INSTANCE_NAME`_LowerBound      `$INSTANCE_NAME`_GetLowerBound()      // get position lower bound
#define `$INSTANCE_NAME`_UpperBound      `$INSTANCE_NAME`_GetUpperBound()      // get position upper bound


    
/***************************************
*        Function Prototypes
***************************************/

void  `$INSTANCE_NAME`_Start();                 // start encoder
void  `$INSTANCE_NAME`_Stop();                  // stop encoder
uint8 `$INSTANCE_NAME`_GetInitStatus();         // return started/stopped status

int8  `$INSTANCE_NAME`_CheckStatus();           // return:  -1=CCW, 1=CW // rename as _PositionChange (?)
//int8  `$INSTANCE_NAME`_CheckRotation();         // rotation:  -1=CCW, 0=NAN, 1=CW (pol: 69->55 tic)
void  `$INSTANCE_NAME`_ClearInterrupt();        // clear pins interrupts 

`$INSTANCE_NAME`_er_t  `$INSTANCE_NAME`_GetPosition();           // get current encoder position
int8                   `$INSTANCE_NAME`_GetDirection();          // last rotation direction:  -1=CCW, 1=CW, 0-none 
uint8                  `$INSTANCE_NAME`_GetPositionChanged();    // return position changed flag
uint8                  `$INSTANCE_NAME`_GetBtnPressed();         // read button pressed flag 
uint8                  `$INSTANCE_NAME`_GetCheckBounds();        // return CheckBounds 
`$INSTANCE_NAME`_er_t  `$INSTANCE_NAME`_GetIncrement();          // return Increment
`$INSTANCE_NAME`_er_t  `$INSTANCE_NAME`_GetLowerBound();         // return LowerBound
`$INSTANCE_NAME`_er_t  `$INSTANCE_NAME`_GetUpperBound();         // return UpperBound

uint8 `$INSTANCE_NAME`_SetPosition(`$INSTANCE_NAME`_er_t value);            // set enoder position
uint8 `$INSTANCE_NAME`_SetCheckBounds (uint8 value);                        // set check bounds property
uint8 `$INSTANCE_NAME`_SetIncrement(`$INSTANCE_NAME`_er_t value);           // set position increment
uint8 `$INSTANCE_NAME`_SetBounds(`$INSTANCE_NAME`_er_t lBound, `$INSTANCE_NAME`_er_t uBound); // set bounds
uint8 `$INSTANCE_NAME`_Setup(`$INSTANCE_NAME`_er_t position, `$INSTANCE_NAME`_er_t increment, `$INSTANCE_NAME`_er_t lBound, `$INSTANCE_NAME`_er_t uBound, uint8 bounds); // set all parameters

    
#endif /* `$INSTANCE_NAME`_H */

/* [] END OF FILE */


