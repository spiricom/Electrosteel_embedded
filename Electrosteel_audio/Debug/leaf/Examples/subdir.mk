################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../leaf/Examples/basic-oscillators.c 

OBJS += \
./leaf/Examples/basic-oscillators.o 

C_DEPS += \
./leaf/Examples/basic-oscillators.d 


# Each subdirectory must supply rules for building sources it contributes
leaf/Examples/basic-oscillators.o: ../leaf/Examples/basic-oscillators.c leaf/Examples/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32H743xx -DDEBUG -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Middlewares/Third_Party/FatFs/src -I../Drivers/STM32H7xx_HAL_Driver/Inc -I"/Users/josnyder/dev/Electrosteel_audio/leaf/leaf" -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"leaf/Examples/basic-oscillators.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

