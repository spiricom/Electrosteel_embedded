################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../leaf/leaf/Externals/d_fft_mayer.c 

OBJS += \
./leaf/leaf/Externals/d_fft_mayer.o 

C_DEPS += \
./leaf/leaf/Externals/d_fft_mayer.d 


# Each subdirectory must supply rules for building sources it contributes
leaf/leaf/Externals/%.o leaf/leaf/Externals/%.su: ../leaf/leaf/Externals/%.c leaf/leaf/Externals/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32H743xx -DDEBUG -c -I/Users/jeffsnyder/dev/LEAF/leaf -I"/Users/jeffsnyder/dev/Electrosteel_embedded/Electrosteel_audio/Inc" -I../Drivers/CMSIS/Include -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Middlewares/Third_Party/FatFs/src -I../Drivers/STM32H7xx_HAL_Driver/Inc -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-leaf-2f-leaf-2f-Externals

clean-leaf-2f-leaf-2f-Externals:
	-$(RM) ./leaf/leaf/Externals/d_fft_mayer.d ./leaf/leaf/Externals/d_fft_mayer.o ./leaf/leaf/Externals/d_fft_mayer.su

.PHONY: clean-leaf-2f-leaf-2f-Externals

