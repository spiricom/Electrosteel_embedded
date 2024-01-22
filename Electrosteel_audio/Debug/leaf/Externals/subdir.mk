################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/jeffsnyder/dev/LEAF/leaf/Externals/d_fft_mayer.c 

OBJS += \
./leaf/Externals/d_fft_mayer.o 

C_DEPS += \
./leaf/Externals/d_fft_mayer.d 


# Each subdirectory must supply rules for building sources it contributes
leaf/Externals/d_fft_mayer.o: /Users/jeffsnyder/dev/LEAF/leaf/Externals/d_fft_mayer.c leaf/Externals/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g -DDEBUG -DSAFE_FILTER -DARM_MATH_CM7 -DNO_DENORMAL_CHECK -DUSE_HAL_DRIVER -DSTM32H743xx -c -I"/Users/jeffsnyder/dev/CMSIS/Include" -I"/Users/jeffsnyder/dev/LEAF/leaf" -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Middlewares/Third_Party/FatFs/src -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I"/Users/jeffsnyder/dev/LEAF/leaf" -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-leaf-2f-Externals

clean-leaf-2f-Externals:
	-$(RM) ./leaf/Externals/d_fft_mayer.cyclo ./leaf/Externals/d_fft_mayer.d ./leaf/Externals/d_fft_mayer.o ./leaf/Externals/d_fft_mayer.su

.PHONY: clean-leaf-2f-Externals

