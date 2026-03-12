################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/josnyder/dev/LEAF/leaf/Externals/d_fft_mayer.c 

OBJS += \
./leaf/Externals/d_fft_mayer.o 

C_DEPS += \
./leaf/Externals/d_fft_mayer.d 


# Each subdirectory must supply rules for building sources it contributes
leaf/Externals/d_fft_mayer.o: /Users/josnyder/dev/LEAF/leaf/Externals/d_fft_mayer.c leaf/Externals/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DDEBUG -DUSE_SPI_RELOAD_TRANSFER -DDHSE_VALUE=16000000 -DCORE_CM7 -DSTM32H750IB -Dsram_layout -DDATA_IN_D2_SRAM -DBOOT_APP -DUSE_HAL_DRIVER -DSTM32H750xx -DUSE_PWR_LDO_SUPPLY -c -I"/Users/josnyder/dev/Electrosteel_embedded/Electrosteel_Daisy_Audio/Drivers/STM32H7xx_HAL_Driver/Inc" -I"/Users/josnyder/dev/LEAF/leaf" -I"/Users/josnyder/dev/Electrosteel_embedded/Electrosteel_Daisy_Audio/Core/Inc" -I/Users/josnyder/dev/LEAF/leaf -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -Ofast -ffunction-sections -fdata-sections -mslow-flash-data -fno-strict-aliasing -Wall -ggdb -fasm -Wno-stringop-overflow -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-leaf-2f-Externals

clean-leaf-2f-Externals:
	-$(RM) ./leaf/Externals/d_fft_mayer.cyclo ./leaf/Externals/d_fft_mayer.d ./leaf/Externals/d_fft_mayer.o ./leaf/Externals/d_fft_mayer.su

.PHONY: clean-leaf-2f-Externals

