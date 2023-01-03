################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../leaf/Externals/d_fft_mayer.c 

OBJS += \
./leaf/Externals/d_fft_mayer.o 

C_DEPS += \
./leaf/Externals/d_fft_mayer.d 


# Each subdirectory must supply rules for building sources it contributes
leaf/Externals/%.o leaf/Externals/%.su: ../leaf/Externals/%.c leaf/Externals/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g -DDEBUG -DNO_DENORMAL_CHECK -DARM_MATH_CM7 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Drivers/CMSIS/Include -I"/Users/jeffsnyder/dev/Electrosteel_embedded/Electrosteel_audio/leaf" -I../Drivers/CMSIS/DSP/Include -I"/Users/jeffsnyder/dev/Electrosteel_embedded/Electrosteel_audio/Drivers/CMSIS/DSP/Include" -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Middlewares/Third_Party/FatFs/src -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Core/Inc -I../FATFS/Target -I../FATFS/App -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-leaf-2f-Externals

clean-leaf-2f-Externals:
	-$(RM) ./leaf/Externals/d_fft_mayer.d ./leaf/Externals/d_fft_mayer.o ./leaf/Externals/d_fft_mayer.su

.PHONY: clean-leaf-2f-Externals

