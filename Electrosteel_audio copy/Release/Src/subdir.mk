################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/audiostream.c \
../Src/bsp_driver_sd.c \
../Src/codec.c \
../Src/dma.c \
../Src/fatfs.c \
../Src/fatfs_platform.c \
../Src/fmc.c \
../Src/gpio.c \
../Src/i2c.c \
../Src/main.c \
../Src/rng.c \
../Src/sai.c \
../Src/sd_diskio.c \
../Src/sdmmc.c \
../Src/spi.c \
../Src/stm32h7xx_hal_msp.c \
../Src/stm32h7xx_it.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32h7xx.c 

OBJS += \
./Src/audiostream.o \
./Src/bsp_driver_sd.o \
./Src/codec.o \
./Src/dma.o \
./Src/fatfs.o \
./Src/fatfs_platform.o \
./Src/fmc.o \
./Src/gpio.o \
./Src/i2c.o \
./Src/main.o \
./Src/rng.o \
./Src/sai.o \
./Src/sd_diskio.o \
./Src/sdmmc.o \
./Src/spi.o \
./Src/stm32h7xx_hal_msp.o \
./Src/stm32h7xx_it.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32h7xx.o 

C_DEPS += \
./Src/audiostream.d \
./Src/bsp_driver_sd.d \
./Src/codec.d \
./Src/dma.d \
./Src/fatfs.d \
./Src/fatfs_platform.d \
./Src/fmc.d \
./Src/gpio.d \
./Src/i2c.d \
./Src/main.d \
./Src/rng.d \
./Src/sai.d \
./Src/sd_diskio.d \
./Src/sdmmc.d \
./Src/spi.d \
./Src/stm32h7xx_hal_msp.d \
./Src/stm32h7xx_it.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32h7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I"/Users/jeffsnyder/dev/Electrosteel_embedded/Electrosteel_audio/leaf" -I/Users/jeffsnyder/dev/LEAF/leaf -I/Users/jeffsnyder/dev/Electrosteel_embedded/Electrosteel_audio/Inc -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Middlewares/Third_Party/FatFs/src -I../Drivers/STM32H7xx_HAL_Driver/Inc -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/audiostream.d ./Src/audiostream.o ./Src/audiostream.su ./Src/bsp_driver_sd.d ./Src/bsp_driver_sd.o ./Src/bsp_driver_sd.su ./Src/codec.d ./Src/codec.o ./Src/codec.su ./Src/dma.d ./Src/dma.o ./Src/dma.su ./Src/fatfs.d ./Src/fatfs.o ./Src/fatfs.su ./Src/fatfs_platform.d ./Src/fatfs_platform.o ./Src/fatfs_platform.su ./Src/fmc.d ./Src/fmc.o ./Src/fmc.su ./Src/gpio.d ./Src/gpio.o ./Src/gpio.su ./Src/i2c.d ./Src/i2c.o ./Src/i2c.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/rng.d ./Src/rng.o ./Src/rng.su ./Src/sai.d ./Src/sai.o ./Src/sai.su ./Src/sd_diskio.d ./Src/sd_diskio.o ./Src/sd_diskio.su ./Src/sdmmc.d ./Src/sdmmc.o ./Src/sdmmc.su ./Src/spi.d ./Src/spi.o ./Src/spi.su ./Src/stm32h7xx_hal_msp.d ./Src/stm32h7xx_hal_msp.o ./Src/stm32h7xx_hal_msp.su ./Src/stm32h7xx_it.d ./Src/stm32h7xx_it.o ./Src/stm32h7xx_it.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32h7xx.d ./Src/system_stm32h7xx.o ./Src/system_stm32h7xx.su

.PHONY: clean-Src

