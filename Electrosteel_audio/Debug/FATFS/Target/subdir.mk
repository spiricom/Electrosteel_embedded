################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FATFS/Target/bsp_driver_sd.c \
../FATFS/Target/fatfs_platform.c \
../FATFS/Target/sd_diskio.c 

OBJS += \
./FATFS/Target/bsp_driver_sd.o \
./FATFS/Target/fatfs_platform.o \
./FATFS/Target/sd_diskio.o 

C_DEPS += \
./FATFS/Target/bsp_driver_sd.d \
./FATFS/Target/fatfs_platform.d \
./FATFS/Target/sd_diskio.d 


# Each subdirectory must supply rules for building sources it contributes
FATFS/Target/%.o FATFS/Target/%.su: ../FATFS/Target/%.c FATFS/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g -DDEBUG -DNO_DENORMAL_CHECK -DARM_MATH_CM7 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Drivers/CMSIS/Include -I"/Users/jeffsnyder/dev/Electrosteel_embedded/Electrosteel_audio/leaf" -I../Drivers/CMSIS/DSP/Include -I"/Users/jeffsnyder/dev/Electrosteel_embedded/Electrosteel_audio/Drivers/CMSIS/DSP/Include" -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Middlewares/Third_Party/FatFs/src -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Core/Inc -I../FATFS/Target -I../FATFS/App -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FATFS-2f-Target

clean-FATFS-2f-Target:
	-$(RM) ./FATFS/Target/bsp_driver_sd.d ./FATFS/Target/bsp_driver_sd.o ./FATFS/Target/bsp_driver_sd.su ./FATFS/Target/fatfs_platform.d ./FATFS/Target/fatfs_platform.o ./FATFS/Target/fatfs_platform.su ./FATFS/Target/sd_diskio.d ./FATFS/Target/sd_diskio.o ./FATFS/Target/sd_diskio.su

.PHONY: clean-FATFS-2f-Target

