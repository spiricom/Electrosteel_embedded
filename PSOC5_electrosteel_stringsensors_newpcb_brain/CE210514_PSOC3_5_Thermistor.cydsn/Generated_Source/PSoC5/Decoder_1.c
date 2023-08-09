/* ============================================================================
 * File Name: QuadDecoder_SW
 *   Version 0.2  (build 20_8)
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
   
#include <Decoder_1.h> // must specify API prefix in Symbol->Properties->Doc.APIPrefix


// local type declaration does not need Decoder_1_ prefix
#define er_t int8_t // int8_t, uint8_t, ..., uint32_t, float32(single), float64(double)

static const signed char enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0}; // 

#define TIMED_OUT  0
#define SW_MASK  0x4                        // button  pin: 2
#define EN_MASK  0x3                        // encoder pins: 0,1
static volatile uint8 CYDATA SW_timeout;

CY_ISR_PROTO(Decoder_1_Tick_ISR);    // ISR for button switch timeout
CY_ISR_PROTO(Decoder_1_myDtrInt);    // interrupt on encoder pin states change
CY_ISR_PROTO(Decoder_1_myPollInt);   // interrupt on external polling clock

//====================================
//        private variables
//====================================

// ('static' is required for multiple instances)
// todo: move to Start()?
static er_t aPosition = Decoder_1_StartPosition; // encoder position (auto initialize to StartPosition)
static int8 aDirection;                                 // save last valid rotation direction:  +1 or -1
static volatile uint8 fPositionChanged;                 // flag indicating position change
#if (Decoder_1_BtnEnable)                      
    static uint8 fBtnPressed;                           // flag indicating button pressed
#endif    

static uint8 aInitialized = false;                      // started(1)/stopped(0)
uint8 Decoder_1_Enabled = true;                  // enabled(1)/disabled(0) (btn excluded)


// initialize values
static  er_t aIncrement   = 1;      // position increment
static  er_t aLowerBound  = -128;    // position lower bound
static  er_t aUpperBound  = 127;    // position upper bound
static uint8 aCheckBounds = false;   // check bounds flag

//====================================
//        private functions
//====================================
void  Decoder_1_SetInputsPullUp();       // set input pins state to Resistive Pull Up
void  Decoder_1_SetInputsHiZ();          // set input pins state to High Impedance Digital
//CY_INLINE
int8  Decoder_1_CheckRotation();         // rotation:  -1=CCW, 0=NAN, 1=CW (pol: 69->55 tic)


//==============================================================================
// Checks all asigned pins events and signals that encoder position changed
// return: 0-no change, -1-rotated CCW, +1-rotated CW
//==============================================================================

CY_INLINE int8 Decoder_1_CheckStatus() // todo: need return value?
{ 
    // 1. clear pins isr
    // 2. check button if enabled
    // 3. check rotation
      
    
    int8 en_dir = Decoder_1_CheckRotation(); // +11 ticks 
    
    if (en_dir==0) return 0;                        // no changes
    
    aDirection = en_dir;                            // store last (non-zero) direction of rotation
   
    fPositionChanged = 1;                           // update flag 
    
    return en_dir;                                  // value changed: -1=CCW, 1=CW 
} 


#if Decoder_1_IsrMode
    
//==============================================================================
// 
//  
// 
//                    STATE CHECK USING INTERRUPT METHOD->
// 
//  
// 
//  
//==============================================================================    
    
    
//==============================================================================
// Circuits@Home algorithm with pin interrupts
// returns direction of rotation:  -1=CCW, 0=NAN, 1=CW 
//==============================================================================

CY_INLINE int8 Decoder_1_CheckRotation() // checks pin status
{
    static uint8 index = 0;
    static  int8 Acc   = 0;                     //internal accumulator to accumulate 1/4 microsteps
    
    
    #if (Decoder_1_BtnEnable) 
        uint8 bits  = (Decoder_1_PINS3_PS & Decoder_1_PINS3_MASK) >> Decoder_1_PINS3_SHIFT;//+7tic (74 tic)
        
        if(((bits & SW_MASK) == 0) && (SW_timeout == TIMED_OUT))            // Btn pressed 
	    {
            SW_timeout = SW_DEBOUNCE_TIME;      // reset the debounce timer for this button
            Decoder_1_isrBtnSW_StartEx(Decoder_1_Tick_ISR);   // start debouncing timer isr
            return 0; // ignore encoder if button pressed
	    }             
        
        bits &= EN_MASK;  // pins state
    #else
        uint8 bits  = (Decoder_1_PINS2_PS & Decoder_1_PINS2_MASK) >> Decoder_1_PINS2_SHIFT;//+7tic (58 tic)
    #endif   
    

    if (Decoder_1_Enabled==0) return 0;  // decoder disabled
    

    #if (Decoder_1_InvertDir)
        bits  = ((bits&1)<<1) | ((bits&2)>>1);  // swap bits 1&2
    #endif
    
    
    index <<= 2;                                // remember previous state by shifting the lower bits up 2    
    index |= bits;                              // OR bits with var old_AB to set new value     
    Acc &= 0x03;                                // dont let it grow >3 or <-3
    Acc += enc_states[ index & 0x0f ];          // accumulate 1/4 steps   
  
    return Acc>>2;                              // -1=CCW, 0=NAN, 1=CW 
}

//==============================================================================
// Debouncing ISR - counts milliseconds elapsed after button press
// Rises semaphore flag when timeout
// Works on Button Pressed event
//==============================================================================
    
#if (Decoder_1_BtnEnable)
CY_ISR(Decoder_1_Tick_ISR)
{
	if(SW_timeout != 0) 
	{
		if(--SW_timeout == TIMED_OUT)   // edge was detected by the PICU. Decrement and check timeout.
		{
            // Timed out -> check if SW still pressed
			if((Decoder_1_PINS3_Read() & SW_MASK) == 0)  
			{
                Decoder_1_isrBtnSW_Stop();
                fBtnPressed = 1;        // set flag
			}
		}
	}
}

#endif //(_BtnEnable)


//==============================================================================
// Clears pins interrupt
// If pins isr is enabled, then must clear inside ISR to allow further isr events
//==============================================================================

CY_INLINE void Decoder_1_ClearInterrupt() // 
{
    
        #if (Decoder_1_BtnEnable)
            
            #if (CY_PSOC5)
                Decoder_1_PINS3_INTSTAT; 
            #else
                Decoder_1_PINS3_ClearInterrupt(); 
            #endif
            
        #else
            
            #if (CY_PSOC5)
                Decoder_1_PINS2_INTSTAT;     
            #else
                Decoder_1_PINS2_ClearInterrupt(); 
            #endif    
            
        #endif    
}


//==============================================================================
// interrupt on encoder pin states change
//==============================================================================

CY_ISR(Decoder_1_myDtrInt) 
{   
    Decoder_1_ClearInterrupt(); // must clear
    Decoder_1_CheckStatus();  
    Decoder_1_GetPositionChanged();
}    





#else // (!IsrMode)
 
//==============================================================================
// 
//  
// 
//                     STATE CHECK USING POLLING METHOD->
// 
//  
// 
//  
//==============================================================================    
    
    
//==============================================================================
// Circuits@Home algorithm w/o pins interrupt
// returns direction of rotation: -1=CCW, 0=NAN, 1=CW 
//==============================================================================

CY_INLINE int8 Decoder_1_CheckRotation()
{
    static uint8 index = 0;
    static  int8 Acc = 0;                       // internal accumulator to accumulate 1/4 microsteps

    #if (Decoder_1_BtnEnable)
        
	    if(SW_timeout == TIMED_OUT) // in idle state
	    {
            uint8 bit_SW = Decoder_1_pin_btn_Read(); // Btn pressed
            
            if(bit_SW != 0)                                 // Btn pressed while in idle state
            {
	        	SW_timeout = SW_DEBOUNCE_TIME;              // reset the debounce timer for this button
                return 0;                                   
            }    
	    }
        else                                                // debouncing countdown after button press  
	    {
		    if(--SW_timeout == TIMED_OUT)                   // Decrement and check for timeout.
		    { 
                if (Decoder_1_pin_btn_Read() == 0)   // check if SW still pressed 
			    {
                    fBtnPressed = 1;                        // Rises semaphore flag
			    }
		    }
	    }
                
        // read pins  
        uint8 bit_a = (Decoder_1_pin_A_PS & Decoder_1_pin_A_MASK) >> Decoder_1_pin_A_SHIFT; 
        uint8 bit_b = (Decoder_1_pin_B_PS & Decoder_1_pin_B_MASK) >> Decoder_1_pin_B_SHIFT;
        
    #else
        
        // read pins  
        uint8 bit_a = (Decoder_1_pin_A_PS & Decoder_1_pin_A_MASK) >> Decoder_1_pin_A_SHIFT; 
        uint8 bit_b = (Decoder_1_pin_B_PS & Decoder_1_pin_B_MASK) >> Decoder_1_pin_B_SHIFT;

    #endif    
    
    
    if (Decoder_1_Enabled==0) return 0;  // decoder disabled
    
    
    #if (Decoder_1_InvertDir)
        uint8 bits = ((bit_a << 1) | bit_b);
    #else
        uint8 bits = ((bit_b << 1) | bit_a);
    #endif

    
    index <<= 2;                                // remember previous state by shifting the lower bits up 2    
    index |= bits;                              // OR bits with var old_AB to set new value  
    Acc &= 0x03;                                // dont let it grow >3 or <-3
    Acc += enc_states[ index & 0x0f ];          // accumulate 1/4 steps                                       
    
    return Acc>>2;                              // -1=CCW, 0=NAN, 1=CW  
}


//==============================================================================
// interrupt on external clock for polling states
//==============================================================================

CY_ISR(Decoder_1_myPollInt) 
{   
    Decoder_1_CheckStatus(); 
}    


#endif //!IsrMode   


//==============================================================================
// 
//  
// 
//                   COMMON ROUTINES (ISR / POLL MODE)->
// 
//  
// 
//  
//==============================================================================

//==============================================================================
// Initialize encoder 
//==============================================================================

void Decoder_1_Start()
{ 
    #if Decoder_1_IsrMode
        Decoder_1_isrDtr_StartEx(Decoder_1_myDtrInt);//start isrDtr interrupt
    #else    
    #if Decoder_1_IsrInternal
        Decoder_1_isrPoll_StartEx(Decoder_1_myPollInt);//start isrPoll interrupt
    #endif 
    #endif 
    
    
    if (Decoder_1_InputsPullUp)
        Decoder_1_SetInputsPullUp();
    else    
        Decoder_1_SetInputsHiZ();
        
    aInitialized = true;                    // started
} 

//==============================================================================
// Stop encoder 
//==============================================================================

void Decoder_1_Stop()
{
    #if Decoder_1_IsrMode
        Decoder_1_isrDtr_Stop();     //stop isrDtr interrupt
    #else    
    #if Decoder_1_IsrInternal
        Decoder_1_isrPoll_Stop();    //staop isrPoll interrupt
    #endif
    #endif
    
    Decoder_1_SetInputsHiZ();
    
    aInitialized = false;                   // stopped
} 

//==============================================================================
// Set input pins state to Resistive Pull Up 
//==============================================================================

void Decoder_1_SetInputsPullUp()
{
    // important! Though initial drive mode is HiZ, the Initial Drive State must be set to High (1)
    // else button behavior is erratical
    
    #if Decoder_1_IsrMode
        
         #if (Decoder_1_BtnEnable)
            Decoder_1_PINS3_SetDriveMode (Decoder_1_PINS3_DM_RES_UP); // Resistive Pull Up
        #else
            Decoder_1_PINS2_SetDriveMode (Decoder_1_PINS2_DM_RES_UP); // Resistive Pull Up
        #endif 
        
    #else
        Decoder_1_pin_A_SetDriveMode (Decoder_1_pin_A_DM_RES_UP);     // Resistive Pull Up
        Decoder_1_pin_B_SetDriveMode (Decoder_1_pin_B_DM_RES_UP);     // Resistive Pull Up
        
        #if (Decoder_1_BtnEnable)
            Decoder_1_pin_btn_SetDriveMode (Decoder_1_pin_btn_DM_RES_UP); // Resistive Pull Up
        #endif
        
    #endif
    
}

//==============================================================================
// Set input pins state to High Impedance Digital 
//==============================================================================

void Decoder_1_SetInputsHiZ()
{
    #if Decoder_1_IsrMode
        
         #if (Decoder_1_BtnEnable)
            Decoder_1_PINS3_SetDriveMode (Decoder_1_PINS3_DM_DIG_HIZ); // High Impedance Digital
        #else
            Decoder_1_PINS2_SetDriveMode (Decoder_1_PINS2_DM_DIG_HIZ); // High Impedance Digital
        #endif 
        
    #else
        Decoder_1_pin_A_SetDriveMode (Decoder_1_pin_A_DM_DIG_HIZ);     // High Impedance Digital
        Decoder_1_pin_B_SetDriveMode (Decoder_1_pin_B_DM_DIG_HIZ);     // High Impedance Digital
        
        #if (Decoder_1_BtnEnable)
            Decoder_1_pin_btn_SetDriveMode (Decoder_1_pin_btn_DM_DIG_HIZ); //High Impedance Digital
        #endif
        
    #endif    
}

//==============================================================================
// Get encoder current position 
//==============================================================================

er_t  Decoder_1_GetPosition() { return aPosition; }


//==============================================================================
// Set encoder position
// value must be in range [lower_bound, upper_bound]
// return: 0-failed, 1-success
//==============================================================================

uint8 Decoder_1_SetPosition(er_t value)
{
    uint8 result = 0;
    
    if (aCheckBounds)
    {  
        if ((value >= aLowerBound) && (value <= aUpperBound))
        {
            {
                aPosition = value;      // update position
                aDirection = 0;         // no rotation (required if position updated in the main loop)
                fPositionChanged = 1;   // fire position changed event
            }    
            result = 1;                 // success
        }
    }
    else
    {
            {
                aPosition = value;      // update position
                aDirection = 0;         // no rotation (required if position updated in the main loop)
                fPositionChanged = 1;   // fire position changed event
            }    
            result = 1;                 // success
    }  
    
    return result;
}


//==============================================================================
// Get last direction of encoder rotation:
// return: -1=CCW, 1=CW, 0-none
//==============================================================================

int8  Decoder_1_GetDirection() { return aDirection; }


//==============================================================================
// Read button pressed flag, reset flag if non-zero
// return: 1- pressed, 0-not pressed
//==============================================================================
#if (Decoder_1_BtnEnable)
uint8 Decoder_1_GetBtnPressed()  
{
    uint8 result = fBtnPressed;
    if (fBtnPressed) fBtnPressed = 0; // reset flag for one-time use only
    return result;
}
#endif

//==============================================================================
// Return position changed flag, reset flag if non-zero
//
//==============================================================================

uint8 Decoder_1_GetPositionChanged()  
{
        
    // 4. check position bounds
    // 5. update position
    
    // this occures in the main loop->
    
    if (fPositionChanged==0) return 0;  // position did not change
       
    fPositionChanged=0;                 // reset flag 
    
    if (aDirection==0) return 1;        // typically when set position
    
    
    if (aCheckBounds)                   // check bounds 
                              
        if (aDirection > 0) {
            if ( aPosition > aUpperBound - aIncrement) return 0; // over or repeated UB            
            aPosition += aIncrement;
        }
        else
        //if (aDirection < 0)
        {
            if ( aPosition < aLowerBound + aIncrement) return 0; // below or repeated LB 
            aPosition -= aIncrement;
        }

    else
            
        aPosition = (aDirection==1)? aPosition + aIncrement : aPosition - aIncrement;  // update position

    
    return 1;                           // position changed
}

//==============================================================================
// Get Initialized status
// return: 1= started, 0= stopped
//==============================================================================

uint8 Decoder_1_GetInitStatus() { return aInitialized; }


//==============================================================================
// Set encoder increment
// value must be positive, non-zero value
// return: 0-fail, 1-success
//==============================================================================

uint8 Decoder_1_SetIncrement(er_t value)
{
    uint8 result = 0;

    if ( value > 0 ) 
    {
        aIncrement = value;
        result = 1;
    }
    
    return result;
}

//==============================================================================
// Set check bounds flag
// input: 1 - true, 0 - false 
//==============================================================================

uint8  Decoder_1_SetCheckBounds (uint8 value)
{
    uint8 result = 0;

    aCheckBounds = value;

    if (aCheckBounds)  
        result = (aLowerBound<=aPosition) && (aPosition<=aUpperBound);
    else
        result = 1;

    return result;
}


//==============================================================================
// Set encoder lower and upper bounds and resets position if out of range
// to avoid confusion, set new position prior to to updating bounds
// return: 0-failed, 1-success
//==============================================================================

uint8 Decoder_1_SetBounds (er_t lBound, er_t uBound)
{
    uint8 result = 0;
    
    if (lBound <= uBound) 
    {
        aLowerBound = lBound;
        aUpperBound = uBound;
        
        result = 1;
    }
    
    return result;
}

//==============================================================================
// Assign multiple encoder parameters at once
// return: 1= success, 0= fail
//==============================================================================

uint8 Decoder_1_Setup(er_t position, er_t increment, er_t lBound, er_t uBound, uint8 bounds)
{
    uint8  result = Decoder_1_SetBounds ( lBound, uBound ) &&
                    Decoder_1_SetPosition ( position )     && 
                    Decoder_1_SetIncrement ( increment )   &&
                    Decoder_1_SetCheckBounds( bounds );
    
    return result;
}

//==============================================================================
// Getters for Increment, LowerBound, UpperBound and CheckBounds
//==============================================================================

er_t  Decoder_1_GetIncrement()   { return aIncrement;   }
er_t  Decoder_1_GetLowerBound()  { return aLowerBound;  }
er_t  Decoder_1_GetUpperBound()  { return aUpperBound;  }
uint8 Decoder_1_GetCheckBounds() { return aCheckBounds; }




/* [] END OF FILE */
