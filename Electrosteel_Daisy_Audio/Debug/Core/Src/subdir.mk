################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/audio.c \
../Core/Src/bdma.c \
../Core/Src/codec.c \
../Core/Src/dma.c \
../Core/Src/fmc.c \
../Core/Src/gpio.c \
../Core/Src/i2c.c \
../Core/Src/main.c \
../Core/Src/rng.c \
../Core/Src/sai.c \
../Core/Src/sdmmc.c \
../Core/Src/spi.c \
../Core/Src/startup_stm32h750xx.c \
../Core/Src/stm32h7xx_hal_msp.c \
../Core/Src/stm32h7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32h7xx.c 

OBJS += \
./Core/Src/audio.o \
./Core/Src/bdma.o \
./Core/Src/codec.o \
./Core/Src/dma.o \
./Core/Src/fmc.o \
./Core/Src/gpio.o \
./Core/Src/i2c.o \
./Core/Src/main.o \
./Core/Src/rng.o \
./Core/Src/sai.o \
./Core/Src/sdmmc.o \
./Core/Src/spi.o \
./Core/Src/startup_stm32h750xx.o \
./Core/Src/stm32h7xx_hal_msp.o \
./Core/Src/stm32h7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32h7xx.o 

C_DEPS += \
./Core/Src/audio.d \
./Core/Src/bdma.d \
./Core/Src/codec.d \
./Core/Src/dma.d \
./Core/Src/fmc.d \
./Core/Src/gpio.d \
./Core/Src/i2c.d \
./Core/Src/main.d \
./Core/Src/rng.d \
./Core/Src/sai.d \
./Core/Src/sdmmc.d \
./Core/Src/spi.d \
./Core/Src/startup_stm32h750xx.d \
./Core/Src/stm32h7xx_hal_msp.d \
./Core/Src/stm32h7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32h7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DITCMRAM -DUSE_SPI_RELOAD_TRANSFER -DARM_MATH_LOOPUNROLL -DDHSE_VALUE=16000000 -DCORE_CM7 -DSTM32H750IB -DARM_MATH_CM7 -Dsram_layout -DDATA_IN_D2_SRAM -DBOOT_APP -DUSE_HAL_DRIVER -DSTM32H750xx -c -I"/Users/jeffsnyder/dev/CMSIS/Include" -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -ggdb -fasm -Wno-stringop-overflow -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/audio.cyclo ./Core/Src/audio.d ./Core/Src/audio.o ./Core/Src/audio.su ./Core/Src/bdma.cyclo ./Core/Src/bdma.d ./Core/Src/bdma.o ./Core/Src/bdma.su ./Core/Src/codec.cyclo ./Core/Src/codec.d ./Core/Src/codec.o ./Core/Src/codec.su ./Core/Src/dma.cyclo ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/dma.su ./Core/Src/fmc.cyclo ./Core/Src/fmc.d ./Core/Src/fmc.o ./Core/Src/fmc.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/rng.cyclo ./Core/Src/rng.d ./Core/Src/rng.o ./Core/Src/rng.su ./Core/Src/sai.cyclo ./Core/Src/sai.d ./Core/Src/sai.o ./Core/Src/sai.su ./Core/Src/sdmmc.cyclo ./Core/Src/sdmmc.d ./Core/Src/sdmmc.o ./Core/Src/sdmmc.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/startup_stm32h750xx.cyclo ./Core/Src/startup_stm32h750xx.d ./Core/Src/startup_stm32h750xx.o ./Core/Src/startup_stm32h750xx.su ./Core/Src/stm32h7xx_hal_msp.cyclo ./Core/Src/stm32h7xx_hal_msp.d ./Core/Src/stm32h7xx_hal_msp.o ./Core/Src/stm32h7xx_hal_msp.su ./Core/Src/stm32h7xx_it.cyclo ./Core/Src/stm32h7xx_it.d ./Core/Src/stm32h7xx_it.o ./Core/Src/stm32h7xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32h7xx.cyclo ./Core/Src/system_stm32h7xx.d ./Core/Src/system_stm32h7xx.o ./Core/Src/system_stm32h7xx.su

.PHONY: clean-Core-2f-Src

