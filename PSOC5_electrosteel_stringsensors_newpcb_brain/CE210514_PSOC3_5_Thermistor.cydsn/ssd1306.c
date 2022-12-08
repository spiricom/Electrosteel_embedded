/*
 * ssd1306.c
 *
 *  Created on: Oct 8, 2019
 *      Author: jeffsnyder
 */


/*
 * ssd1306.c
 *
 *  Created on: Jul 6, 2018
 *      Author: jeffsnyder
 */

#include "ssd1306.h"
#include "main.h"


unsigned char buffer[1024];

//unsigned char buffer [] = {
//
//		0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//		0x00, 0x00, 0xC0, 0xC0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xC0, 0xC0,
//		0xC0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0,
//		0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80,
//		0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0,
//		0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//		0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
//		0x00, 0x00, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1F, 0xFE, 0xF0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80,
//		0xF0, 0xFE, 0x1F, 0x03, 0x00, 0x00, 0x00, 0xF0, 0xFE, 0x0F, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00,
//		0x00, 0x01, 0x01, 0x03, 0x0F, 0xFE, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0xFE, 0x0F, 0x03, 0x01, 0x01,
//		0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x06, 0x00, 0x00, 0x00, 0xF0, 0xFE, 0x0F, 0x03, 0x01, 0x01,
//		0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x0F, 0xFE, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
//		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x0F, 0xFE, 0xF0, 0x00, 0x00, 0x00,
//		0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0,
//		0xFE, 0x0F, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x06, 0x00, 0x00, 0x00, 0x00,
//		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x3F, 0xFC, 0xE0, 0xE0, 0xFC, 0x1F,
//		0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x3F, 0x78, 0x60, 0xC0, 0xC0, 0x80, 0x80, 0x80,
//		0x80, 0xC0, 0xC0, 0x60, 0x78, 0x3F, 0x07, 0x00, 0x00, 0x00, 0x07, 0x3F, 0x78, 0xE0, 0xC0, 0xC0,
//		0x80, 0x80, 0xC0, 0xC0, 0xE0, 0x70, 0x10, 0x00, 0x00, 0x00, 0x07, 0x3F, 0x78, 0x60, 0xC0, 0xC0,
//		0x80, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0x60, 0x78, 0x3F, 0x07, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
//		0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xC0, 0xE0, 0xE0, 0x78, 0x3F, 0x07, 0x00, 0x00, 0x00,
//		0xFF, 0xFF, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07,
//		0x3F, 0x78, 0xE0, 0xC0, 0xC0, 0x80, 0x80, 0xC0, 0xC0, 0xE0, 0x70, 0x10, 0x00, 0x00, 0x00, 0x00,
//		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00,
//		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01,
//		0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//		0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//		0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,
//		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
//		0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//		};



#define ssd1306_swap(a, b) { int16_t t = a; a = b; b = t; }
#define WIDTH SSD1306_LCDWIDTH
#define HEIGHT SSD1306_LCDHEIGHT

uint8_t displayBufferChunk[1025];

uint8_t OLED_xpos = 0;
uint8_t OLED_ypos = 0;



uint8_t OLED_i2c_address;
uint8_t OLED_externalVCC;


void ssd1306_begin(uint8_t vccstate)
{
	OLED_externalVCC = vccstate;

/*
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET); //PULL RESET LINE HIGH
	// VDD (3.3V) goes high at start, lets just chill for a ms
	HAL_Delay(1);
	// bring reset low
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET); //PULL RESET LINE HIGH
	// wait 10ms
	HAL_Delay(10);
	// bring out of reset
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET); //PULL RESET LINE HIGH
	// turn on VCC (9V?)
*/

	// Init sequence
	ssd1306_command(SSD1306_DISPLAYOFF);                    // 0xAE
	ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
	ssd1306_command(0x80);                                  // the suggested ratio 0x80

	ssd1306_command(SSD1306_SETMULTIPLEX);                  // 0xA8
	ssd1306_command(SSD1306_LCDHEIGHT - 1);

	ssd1306_command(SSD1306_SETDISPLAYOFFSET);              // 0xD3
	ssd1306_command(0x0);                                   // no offset
	ssd1306_command(SSD1306_SETSTARTLINE | 0x0);            // line #0
	ssd1306_command(SSD1306_CHARGEPUMP);                    // 0x8D
	if (vccstate == SSD1306_EXTERNALVCC)
	{ ssd1306_command(0x10); }
	else
	{ ssd1306_command(0x14); }
	ssd1306_command(SSD1306_MEMORYMODE);                    // 0x20
	ssd1306_command(0x00);                                  // 0x0 act like ks0108
	ssd1306_command(SSD1306_SEGREMAP | 0x1);
	ssd1306_command(SSD1306_COMSCANDEC);

	#if defined SSD1306_128_32
	ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
	ssd1306_command(0x02);
	ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
	ssd1306_command(0x8F);

	#elif defined SSD1306_128_64
	ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
	ssd1306_command(0x12);
	ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
	if (vccstate == SSD1306_EXTERNALVCC)
	{ ssd1306_command(0x9F); }
	else
	{ ssd1306_command(0xCF); }

	#elif defined SSD1306_96_16
	ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
	ssd1306_command(0x2);   //ada x12
	ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
	if (vccstate == SSD1306_EXTERNALVCC)
	{ ssd1306_command(0x10); }
	else
	{ ssd1306_command(0xAF); }

	#endif

	ssd1306_command(SSD1306_SETPRECHARGE);                  // 0xd9
	if (vccstate == SSD1306_EXTERNALVCC)
	{ ssd1306_command(0x22); }
	else
	{ ssd1306_command(0xF1); }
	ssd1306_command(SSD1306_SETVCOMDETECT);                 // 0xDB
	ssd1306_command(0x40);
	ssd1306_command(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
	ssd1306_command(SSD1306_NORMALDISPLAY);                 // 0xA6

	ssd1306_command(SSD1306_DEACTIVATE_SCROLL);

	ssd1306_command(SSD1306_DISPLAYON);//--turn on oled panel
}


void sdd1306_invertDisplay(uint8_t i) {
  if (i) {
    ssd1306_command(SSD1306_INVERTDISPLAY);
  } else {
    ssd1306_command(SSD1306_NORMALDISPLAY);
  }
}

void ssd1306_command(uint8_t c) {
	// I2C
	//	uint8_t control = 0x00;   // Co = 0, D/C = 0

	uint8_t i2c_message[2] = {0,0};
	I2Cbuff1[0] = 0x0;
    I2Cbuff1[1] = c;
	I2C_MasterWriteBlocking(SSD1306_I2C_ADDRESS, 2, I2C_1_MODE_COMPLETE_XFER);
}


// Dim the display
// dim = true: display is dimmed
// dim = false: display is normal
void ssd1306_dim(uint8_t dim) {
  uint8_t contrast;

  if (dim) {
    contrast = 0; // Dimmed display
  } else {
    if (OLED_externalVCC == SSD1306_EXTERNALVCC) {
      contrast = 0x9F;
    } else {
      contrast = 0xCF;
    }
  }
  // the range of contrast to too small to be really useful
  // it is useful to dim the display
  ssd1306_command(SSD1306_SETCONTRAST);
  ssd1306_command(contrast);
}



void ssd1306_display_full_buffer(void) {

	ssd1306_home();

//	for (int i = 0; i < 512; i++)
//	{
//		displayBufferChunk[0] = 0x40;
//		for (int x = 0; x < 16; x++)
//		{
//			displayBufferChunk[x+1] = buffer[i];
//			i++;
//		}
//		HAL_I2C_Master_Transmit_DMA(OLED_i2c_handle, OLED_i2c_address, displayBufferChunk, 17);
////		HAL_I2C_Master_Transmit(OLED_i2c_handle, OLED_i2c_address, displayBufferChunk, 17, 2000);
////		HAL_Delay(1);
//		i--;
//	}
    
     ssd1306_command(SSD1306_SETLOWCOLUMN | 0x0);  // low col = 0
    ssd1306_command(SSD1306_SETHIGHCOLUMN | 0x0);  // hi col = 0
    ssd1306_command(SSD1306_SETSTARTLINE | 0x0); // line #0
	
  


    //Serial.println(TWBR, DEC);
    //Serial.println(TWSR & 0x3, DEC);

    // I2C
    //height >>= 3;
    //width >>= 3;
	unsigned char height=64;
	unsigned char width=132; 
	unsigned char m_row = 0;
	unsigned char m_col = 2;
	
	
	height >>= 3;
	width >>= 3;
	//Serial.println(width);
	
	int p = 0;
	
	unsigned char i, j, k =0;

	
	for ( i = 0; i < height; i++) 
    {
		
		// send a bunch of data in one xmission
        ssd1306_command(0xB0 + i + m_row);//set page address
        ssd1306_command(m_col & 0xf);//set lower column address
        ssd1306_command(0x10 | (m_col >> 4));//set higher column address
		
        
        I2Cbuff1[0] = 0x40;

        

        for( j = 0; j < 8; j++)
        {      

            for (int b = 0; b < width; b++)
	        {
		        I2Cbuff1[b+1] = buffer[b + (width*k)];
	        }
            k++;
            I2C_MasterWriteBlocking(SSD1306_I2C_ADDRESS, width+1, I2C_1_MODE_COMPLETE_XFER);
        }
	}
	

    
    
    
    
    ////
    
   
	//HAL_I2C_Master_Transmit_DMA(OLED_i2c_handle, OLED_i2c_address, displayBufferChunk, 513);
}

void ssd1306_display_first_line(void) {

	ssd1306_home();

//	for (int i = 0; i < 512; i++)
//	{
//		displayBufferChunk[0] = 0x40;
//		for (int x = 0; x < 16; x++)
//		{
//			displayBufferChunk[x+1] = buffer[i];
//			i++;
//		}
//		HAL_I2C_Master_Transmit_DMA(OLED_i2c_handle, OLED_i2c_address, displayBufferChunk, 17);
////		HAL_I2C_Master_Transmit(OLED_i2c_handle, OLED_i2c_address, displayBufferChunk, 17, 2000);
////		HAL_Delay(1);
//		i--;
//	}
    
     ssd1306_command(SSD1306_SETLOWCOLUMN | 0x0);  // low col = 0
    ssd1306_command(SSD1306_SETHIGHCOLUMN | 0x0);  // hi col = 0
    ssd1306_command(SSD1306_SETSTARTLINE | 0x0); // line #0
	
  


    //Serial.println(TWBR, DEC);
    //Serial.println(TWSR & 0x3, DEC);

    // I2C
    //height >>= 3;
    //width >>= 3;
	unsigned char height=16;
	unsigned char width=132; 
	unsigned char m_row = 0;
	unsigned char m_col = 2;
	
	
	height >>= 3;
	width >>= 3;
	//Serial.println(width);
	
	int p = 0;
	
	unsigned char i, j, k =0;

	
	for ( i = 0; i < height; i++) 
    {
		
		// send a bunch of data in one xmission
        ssd1306_command(0xB0 + i + m_row);//set page address
        ssd1306_command(m_col & 0xf);//set lower column address
        ssd1306_command(0x10 | (m_col >> 4));//set higher column address
		
        
        I2Cbuff1[0] = 0x40;

        

        for( j = 0; j < 8; j++)
        {      

            for (int b = 0; b < width; b++)
	        {
		        I2Cbuff1[b+1] = buffer[b + (width*k)];
	        }
            k++;
            I2C_MasterWriteBlocking(SSD1306_I2C_ADDRESS, width+1, I2C_1_MODE_COMPLETE_XFER);
        }
	}
	

    
    
    
    
    ////
    
   
	//HAL_I2C_Master_Transmit_DMA(OLED_i2c_handle, OLED_i2c_address, displayBufferChunk, 513);
}

void ssd1306_home(void) {

	ssd1306_move_raw(0,0);
}

void ssd1306_move_raw(uint8_t row, uint8_t column){
	if(column > 127) { column = 127; }
	if(row > 7) { row = 7; }
	ssd1306_command(SSD1306_COLUMNADDR);
	ssd1306_command(column);   // Column start address (0 = reset)
	ssd1306_command(SSD1306_LCDWIDTH-1); // Column end address (127 = reset)

	ssd1306_command(SSD1306_PAGEADDR);
	ssd1306_command(row); // Page start address (0 = reset)
	ssd1306_command(3); // Page end address
}


void ssd1306_move(uint8_t row, uint8_t column) {

	if(column > 15) { column = 15; }
	if(row > 7) { row = 7; }
	ssd1306_move_raw(row,(uint8_t)(column << 3));
}


void ssd1306_write_internal(uint8_t* data, uint16_t numBytes) {
	for (uint16_t i = 0; i < numBytes; i++)
	{
		buffer[i+(OLED_xpos + (OLED_ypos * 128))] = data[i];

	}
}



void ssd1306_write(uint8_t* data, uint16_t numBytes) {

	I2Cbuff1[0] = 0x40;

	for (uint16_t i = 0; i < numBytes; i++)
	{
		I2Cbuff1[i+1] = data[i];
	}
    I2C_MasterWriteBlocking(SSD1306_I2C_ADDRESS, numBytes+1, I2C_1_MODE_COMPLETE_XFER);
	//HAL_I2C_Master_Transmit(OLED_i2c_handle, OLED_i2c_address, localBuffer, numBytes+1, 2000);

}

void ssd1306_write_2X(uint8_t* data, uint16_t numBytes) {

	uint8_t localBuffer[(numBytes*2)+1];

	I2Cbuff1[0] = 0x40;

	for (uint16_t i = 0; i < numBytes; i++)
	{
		I2Cbuff1[i+1] = data[i] >> 4;

	}
    I2C_MasterWriteBlocking(SSD1306_I2C_ADDRESS, (numBytes*2)+1, I2C_1_MODE_COMPLETE_XFER);
	//HAL_I2C_Master_Transmit(OLED_i2c_handle, OLED_i2c_address, localBuffer, (numBytes*2)+1, 2000);

	ssd1306_move(1,0);

	for (uint16_t i = 0; i < numBytes; i++)
	{
		I2Cbuff1[i+1] = data[i] & 0x0f;
	}
    I2C_MasterWriteBlocking(SSD1306_I2C_ADDRESS, (numBytes*2)+1, I2C_1_MODE_COMPLETE_XFER);
	//HAL_I2C_Master_Transmit(OLED_i2c_handle, OLED_i2c_address, localBuffer, (numBytes*2)+1, 2000);

}


