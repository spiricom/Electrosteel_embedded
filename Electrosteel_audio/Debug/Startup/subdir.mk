################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32h743zitx.s 

OBJS += \
./Startup/startup_stm32h743zitx.o 

S_DEPS += \
./Startup/startup_stm32h743zitx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/startup_stm32h743zitx.o: ../Startup/startup_stm32h743zitx.s Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -c -I"/Users/josnyder/dev/Electrosteel_audio/leaf/leaf" -x assembler-with-cpp -MMD -MP -MF"Startup/startup_stm32h743zitx.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

