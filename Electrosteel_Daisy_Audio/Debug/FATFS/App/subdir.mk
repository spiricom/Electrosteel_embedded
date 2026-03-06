################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FATFS/App/fatfs.c 

OBJS += \
./FATFS/App/fatfs.o 

C_DEPS += \
./FATFS/App/fatfs.d 


# Each subdirectory must supply rules for building sources it contributes
FATFS/App/%.o FATFS/App/%.su FATFS/App/%.cyclo: ../FATFS/App/%.c FATFS/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DDEBUG -DUSE_SPI_RELOAD_TRANSFER -DDHSE_VALUE=16000000 -DCORE_CM7 -DSTM32H750IB -Dsram_layout -DDATA_IN_D2_SRAM -DBOOT_APP -DUSE_HAL_DRIVER -DSTM32H750xx -DUSE_PWR_LDO_SUPPLY -c -I"/Users/josnyder/dev/Electrosteel_embedded/Electrosteel_Daisy_Audio/Drivers/STM32H7xx_HAL_Driver/Inc" -I"/Users/josnyder/dev/Electrosteel_embedded/Electrosteel_Daisy_Audio/Core/Inc" -I/Users/josnyder/dev/LEAF/leaf -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -Ofast -ffunction-sections -fdata-sections -mslow-flash-data -fno-strict-aliasing -Wall -ggdb -fasm -Wno-stringop-overflow -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FATFS-2f-App

clean-FATFS-2f-App:
	-$(RM) ./FATFS/App/fatfs.cyclo ./FATFS/App/fatfs.d ./FATFS/App/fatfs.o ./FATFS/App/fatfs.su

.PHONY: clean-FATFS-2f-App

