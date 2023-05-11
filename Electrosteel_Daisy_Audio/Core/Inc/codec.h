/*
 * codec.h
 *
 *  Created on: Jul 6, 2022
 *      Author: jeffsnyder
 */

#ifndef INC_CODEC_H_
#define INC_CODEC_H_
#include "main.h"

#define MSB_FIRST_RJ  0x00
#define MSB_FIRST_LJ  0x01
#define I2S           0x02
#define DSP           0x03


#define WL_BITS_16  (0x00 << 2)
#define WL_BITS_20  (0x01 << 2)
#define WL_BITS_24  (0x02 << 2)
#define WL_BITS_32 (0x03 << 2)


int WriteControlRegister(I2C_HandleTypeDef* i2c, uint8_t address, uint16_t data);
void codec_init(I2C_HandleTypeDef* i2c);


/*
 *         enum class Format
        {
            MSB_FIRST_RJ = 0x00,
            MSB_FIRST_LJ = 0x01,
            I2S          = 0x02,
            DSP          = 0x03,
        };

        enum class WordLength
        {
            BITS_16 = (0x00 << 2),
            BITS_20 = (0x01 << 2),
            BITS_24 = (0x02 << 2),
            BITS_32 = (0x03 << 2),
        };

                void Defaults()
        {
            mcu_is_master = true;
            lr_swap       = false;
            csb_pin_state = false;
            fmt           = Format::MSB_FIRST_LJ;
            wl            = WordLength::BITS_24;
        }

        bool mcu_is_master;


        bool lr_swap;

        bool csb_pin_state;

        Format     fmt;
        WordLength wl;

 */


#endif /* INC_CODEC_H_ */
