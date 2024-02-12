################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/jeffsnyder/dev/CMSIS/Source/arm_atan2_f32.c \
/Users/jeffsnyder/dev/CMSIS/Source/arm_common_tables.c \
/Users/jeffsnyder/dev/CMSIS/Source/arm_const_structs.c \
/Users/jeffsnyder/dev/CMSIS/Source/arm_cos_f32.c \
/Users/jeffsnyder/dev/CMSIS/Source/arm_fir_decimate_f32.c \
/Users/jeffsnyder/dev/CMSIS/Source/arm_fir_decimate_init_f32.c \
/Users/jeffsnyder/dev/CMSIS/Source/arm_fir_init_f32.c \
/Users/jeffsnyder/dev/CMSIS/Source/arm_fir_interpolate_f32.c \
/Users/jeffsnyder/dev/CMSIS/Source/arm_fir_interpolate_init_f32.c \
/Users/jeffsnyder/dev/CMSIS/Source/arm_sin_f32.c 

OBJS += \
./CMSIS/Source/arm_atan2_f32.o \
./CMSIS/Source/arm_common_tables.o \
./CMSIS/Source/arm_const_structs.o \
./CMSIS/Source/arm_cos_f32.o \
./CMSIS/Source/arm_fir_decimate_f32.o \
./CMSIS/Source/arm_fir_decimate_init_f32.o \
./CMSIS/Source/arm_fir_init_f32.o \
./CMSIS/Source/arm_fir_interpolate_f32.o \
./CMSIS/Source/arm_fir_interpolate_init_f32.o \
./CMSIS/Source/arm_sin_f32.o 

C_DEPS += \
./CMSIS/Source/arm_atan2_f32.d \
./CMSIS/Source/arm_common_tables.d \
./CMSIS/Source/arm_const_structs.d \
./CMSIS/Source/arm_cos_f32.d \
./CMSIS/Source/arm_fir_decimate_f32.d \
./CMSIS/Source/arm_fir_decimate_init_f32.d \
./CMSIS/Source/arm_fir_init_f32.d \
./CMSIS/Source/arm_fir_interpolate_f32.d \
./CMSIS/Source/arm_fir_interpolate_init_f32.d \
./CMSIS/Source/arm_sin_f32.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/Source/arm_atan2_f32.o: /Users/jeffsnyder/dev/CMSIS/Source/arm_atan2_f32.c CMSIS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_SPI_RELOAD_TRANSFER -DARM_MATH_LOOPUNROLL -DDHSE_VALUE=16000000 -DCORE_CM7 -DSTM32H750IB -DARM_MATH_CM7 -Dsram_layout -DDATA_IN_D2_SRAM -DBOOT_APP -DUSE_HAL_DRIVER -DSTM32H750xx -c -I"/Users/jeffsnyder/dev/CMSIS/Include" -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Ofast -ffunction-sections -fdata-sections -mslow-flash-data -fno-strict-aliasing -Wall -ggdb -fasm -Wno-stringop-overflow -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
CMSIS/Source/arm_common_tables.o: /Users/jeffsnyder/dev/CMSIS/Source/arm_common_tables.c CMSIS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_SPI_RELOAD_TRANSFER -DARM_MATH_LOOPUNROLL -DDHSE_VALUE=16000000 -DCORE_CM7 -DSTM32H750IB -DARM_MATH_CM7 -Dsram_layout -DDATA_IN_D2_SRAM -DBOOT_APP -DUSE_HAL_DRIVER -DSTM32H750xx -c -I"/Users/jeffsnyder/dev/CMSIS/Include" -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Ofast -ffunction-sections -fdata-sections -mslow-flash-data -fno-strict-aliasing -Wall -ggdb -fasm -Wno-stringop-overflow -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
CMSIS/Source/arm_const_structs.o: /Users/jeffsnyder/dev/CMSIS/Source/arm_const_structs.c CMSIS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_SPI_RELOAD_TRANSFER -DARM_MATH_LOOPUNROLL -DDHSE_VALUE=16000000 -DCORE_CM7 -DSTM32H750IB -DARM_MATH_CM7 -Dsram_layout -DDATA_IN_D2_SRAM -DBOOT_APP -DUSE_HAL_DRIVER -DSTM32H750xx -c -I"/Users/jeffsnyder/dev/CMSIS/Include" -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Ofast -ffunction-sections -fdata-sections -mslow-flash-data -fno-strict-aliasing -Wall -ggdb -fasm -Wno-stringop-overflow -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
CMSIS/Source/arm_cos_f32.o: /Users/jeffsnyder/dev/CMSIS/Source/arm_cos_f32.c CMSIS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_SPI_RELOAD_TRANSFER -DARM_MATH_LOOPUNROLL -DDHSE_VALUE=16000000 -DCORE_CM7 -DSTM32H750IB -DARM_MATH_CM7 -Dsram_layout -DDATA_IN_D2_SRAM -DBOOT_APP -DUSE_HAL_DRIVER -DSTM32H750xx -c -I"/Users/jeffsnyder/dev/CMSIS/Include" -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Ofast -ffunction-sections -fdata-sections -mslow-flash-data -fno-strict-aliasing -Wall -ggdb -fasm -Wno-stringop-overflow -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
CMSIS/Source/arm_fir_decimate_f32.o: /Users/jeffsnyder/dev/CMSIS/Source/arm_fir_decimate_f32.c CMSIS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_SPI_RELOAD_TRANSFER -DARM_MATH_LOOPUNROLL -DDHSE_VALUE=16000000 -DCORE_CM7 -DSTM32H750IB -DARM_MATH_CM7 -Dsram_layout -DDATA_IN_D2_SRAM -DBOOT_APP -DUSE_HAL_DRIVER -DSTM32H750xx -c -I"/Users/jeffsnyder/dev/CMSIS/Include" -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Ofast -ffunction-sections -fdata-sections -mslow-flash-data -fno-strict-aliasing -Wall -ggdb -fasm -Wno-stringop-overflow -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
CMSIS/Source/arm_fir_decimate_init_f32.o: /Users/jeffsnyder/dev/CMSIS/Source/arm_fir_decimate_init_f32.c CMSIS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_SPI_RELOAD_TRANSFER -DARM_MATH_LOOPUNROLL -DDHSE_VALUE=16000000 -DCORE_CM7 -DSTM32H750IB -DARM_MATH_CM7 -Dsram_layout -DDATA_IN_D2_SRAM -DBOOT_APP -DUSE_HAL_DRIVER -DSTM32H750xx -c -I"/Users/jeffsnyder/dev/CMSIS/Include" -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Ofast -ffunction-sections -fdata-sections -mslow-flash-data -fno-strict-aliasing -Wall -ggdb -fasm -Wno-stringop-overflow -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
CMSIS/Source/arm_fir_init_f32.o: /Users/jeffsnyder/dev/CMSIS/Source/arm_fir_init_f32.c CMSIS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_SPI_RELOAD_TRANSFER -DARM_MATH_LOOPUNROLL -DDHSE_VALUE=16000000 -DCORE_CM7 -DSTM32H750IB -DARM_MATH_CM7 -Dsram_layout -DDATA_IN_D2_SRAM -DBOOT_APP -DUSE_HAL_DRIVER -DSTM32H750xx -c -I"/Users/jeffsnyder/dev/CMSIS/Include" -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Ofast -ffunction-sections -fdata-sections -mslow-flash-data -fno-strict-aliasing -Wall -ggdb -fasm -Wno-stringop-overflow -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
CMSIS/Source/arm_fir_interpolate_f32.o: /Users/jeffsnyder/dev/CMSIS/Source/arm_fir_interpolate_f32.c CMSIS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_SPI_RELOAD_TRANSFER -DARM_MATH_LOOPUNROLL -DDHSE_VALUE=16000000 -DCORE_CM7 -DSTM32H750IB -DARM_MATH_CM7 -Dsram_layout -DDATA_IN_D2_SRAM -DBOOT_APP -DUSE_HAL_DRIVER -DSTM32H750xx -c -I"/Users/jeffsnyder/dev/CMSIS/Include" -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Ofast -ffunction-sections -fdata-sections -mslow-flash-data -fno-strict-aliasing -Wall -ggdb -fasm -Wno-stringop-overflow -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
CMSIS/Source/arm_fir_interpolate_init_f32.o: /Users/jeffsnyder/dev/CMSIS/Source/arm_fir_interpolate_init_f32.c CMSIS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_SPI_RELOAD_TRANSFER -DARM_MATH_LOOPUNROLL -DDHSE_VALUE=16000000 -DCORE_CM7 -DSTM32H750IB -DARM_MATH_CM7 -Dsram_layout -DDATA_IN_D2_SRAM -DBOOT_APP -DUSE_HAL_DRIVER -DSTM32H750xx -c -I"/Users/jeffsnyder/dev/CMSIS/Include" -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Ofast -ffunction-sections -fdata-sections -mslow-flash-data -fno-strict-aliasing -Wall -ggdb -fasm -Wno-stringop-overflow -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
CMSIS/Source/arm_sin_f32.o: /Users/jeffsnyder/dev/CMSIS/Source/arm_sin_f32.c CMSIS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_SPI_RELOAD_TRANSFER -DARM_MATH_LOOPUNROLL -DDHSE_VALUE=16000000 -DCORE_CM7 -DSTM32H750IB -DARM_MATH_CM7 -Dsram_layout -DDATA_IN_D2_SRAM -DBOOT_APP -DUSE_HAL_DRIVER -DSTM32H750xx -c -I"/Users/jeffsnyder/dev/CMSIS/Include" -I/Users/jeffsnyder/dev/LEAF/leaf -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Ofast -ffunction-sections -fdata-sections -mslow-flash-data -fno-strict-aliasing -Wall -ggdb -fasm -Wno-stringop-overflow -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CMSIS-2f-Source

clean-CMSIS-2f-Source:
	-$(RM) ./CMSIS/Source/arm_atan2_f32.cyclo ./CMSIS/Source/arm_atan2_f32.d ./CMSIS/Source/arm_atan2_f32.o ./CMSIS/Source/arm_atan2_f32.su ./CMSIS/Source/arm_common_tables.cyclo ./CMSIS/Source/arm_common_tables.d ./CMSIS/Source/arm_common_tables.o ./CMSIS/Source/arm_common_tables.su ./CMSIS/Source/arm_const_structs.cyclo ./CMSIS/Source/arm_const_structs.d ./CMSIS/Source/arm_const_structs.o ./CMSIS/Source/arm_const_structs.su ./CMSIS/Source/arm_cos_f32.cyclo ./CMSIS/Source/arm_cos_f32.d ./CMSIS/Source/arm_cos_f32.o ./CMSIS/Source/arm_cos_f32.su ./CMSIS/Source/arm_fir_decimate_f32.cyclo ./CMSIS/Source/arm_fir_decimate_f32.d ./CMSIS/Source/arm_fir_decimate_f32.o ./CMSIS/Source/arm_fir_decimate_f32.su ./CMSIS/Source/arm_fir_decimate_init_f32.cyclo ./CMSIS/Source/arm_fir_decimate_init_f32.d ./CMSIS/Source/arm_fir_decimate_init_f32.o ./CMSIS/Source/arm_fir_decimate_init_f32.su ./CMSIS/Source/arm_fir_init_f32.cyclo ./CMSIS/Source/arm_fir_init_f32.d ./CMSIS/Source/arm_fir_init_f32.o ./CMSIS/Source/arm_fir_init_f32.su ./CMSIS/Source/arm_fir_interpolate_f32.cyclo ./CMSIS/Source/arm_fir_interpolate_f32.d ./CMSIS/Source/arm_fir_interpolate_f32.o ./CMSIS/Source/arm_fir_interpolate_f32.su ./CMSIS/Source/arm_fir_interpolate_init_f32.cyclo ./CMSIS/Source/arm_fir_interpolate_init_f32.d ./CMSIS/Source/arm_fir_interpolate_init_f32.o ./CMSIS/Source/arm_fir_interpolate_init_f32.su ./CMSIS/Source/arm_sin_f32.cyclo ./CMSIS/Source/arm_sin_f32.d ./CMSIS/Source/arm_sin_f32.o ./CMSIS/Source/arm_sin_f32.su

.PHONY: clean-CMSIS-2f-Source

