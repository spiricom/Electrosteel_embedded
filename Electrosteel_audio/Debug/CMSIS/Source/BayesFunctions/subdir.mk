################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/jeffsnyder/dev/CMSIS/Source/BayesFunctions/BayesFunctions.c \
/Users/jeffsnyder/dev/CMSIS/Source/BayesFunctions/BayesFunctionsF16.c \
/Users/jeffsnyder/dev/CMSIS/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f16.c \
/Users/jeffsnyder/dev/CMSIS/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.c 

OBJS += \
./CMSIS/Source/BayesFunctions/BayesFunctions.o \
./CMSIS/Source/BayesFunctions/BayesFunctionsF16.o \
./CMSIS/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f16.o \
./CMSIS/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.o 

C_DEPS += \
./CMSIS/Source/BayesFunctions/BayesFunctions.d \
./CMSIS/Source/BayesFunctions/BayesFunctionsF16.d \
./CMSIS/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f16.d \
./CMSIS/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/Source/BayesFunctions/BayesFunctions.o: /Users/jeffsnyder/dev/CMSIS/Source/BayesFunctions/BayesFunctions.c CMSIS/Source/BayesFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g -DDEBUG -DNO_DENORMAL_CHECK -DARM_MATH_CM7 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I"/Users/jeffsnyder/dev/CMSIS/Include" -I"/Users/jeffsnyder/dev/CMSIS/PrivateInclude" -I"/Users/jeffsnyder/dev/LEAF/leaf" -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Middlewares/Third_Party/FatFs/src -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I"/Users/jeffsnyder/dev/LEAF/leaf" -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
CMSIS/Source/BayesFunctions/BayesFunctionsF16.o: /Users/jeffsnyder/dev/CMSIS/Source/BayesFunctions/BayesFunctionsF16.c CMSIS/Source/BayesFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g -DDEBUG -DNO_DENORMAL_CHECK -DARM_MATH_CM7 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I"/Users/jeffsnyder/dev/CMSIS/Include" -I"/Users/jeffsnyder/dev/CMSIS/PrivateInclude" -I"/Users/jeffsnyder/dev/LEAF/leaf" -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Middlewares/Third_Party/FatFs/src -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I"/Users/jeffsnyder/dev/LEAF/leaf" -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
CMSIS/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f16.o: /Users/jeffsnyder/dev/CMSIS/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f16.c CMSIS/Source/BayesFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g -DDEBUG -DNO_DENORMAL_CHECK -DARM_MATH_CM7 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I"/Users/jeffsnyder/dev/CMSIS/Include" -I"/Users/jeffsnyder/dev/CMSIS/PrivateInclude" -I"/Users/jeffsnyder/dev/LEAF/leaf" -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Middlewares/Third_Party/FatFs/src -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I"/Users/jeffsnyder/dev/LEAF/leaf" -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
CMSIS/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.o: /Users/jeffsnyder/dev/CMSIS/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.c CMSIS/Source/BayesFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g -DDEBUG -DNO_DENORMAL_CHECK -DARM_MATH_CM7 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I"/Users/jeffsnyder/dev/CMSIS/Include" -I"/Users/jeffsnyder/dev/CMSIS/PrivateInclude" -I"/Users/jeffsnyder/dev/LEAF/leaf" -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Middlewares/Third_Party/FatFs/src -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I"/Users/jeffsnyder/dev/LEAF/leaf" -Ofast -ffunction-sections -fdata-sections -fno-strict-aliasing -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CMSIS-2f-Source-2f-BayesFunctions

clean-CMSIS-2f-Source-2f-BayesFunctions:
	-$(RM) ./CMSIS/Source/BayesFunctions/BayesFunctions.cyclo ./CMSIS/Source/BayesFunctions/BayesFunctions.d ./CMSIS/Source/BayesFunctions/BayesFunctions.o ./CMSIS/Source/BayesFunctions/BayesFunctions.su ./CMSIS/Source/BayesFunctions/BayesFunctionsF16.cyclo ./CMSIS/Source/BayesFunctions/BayesFunctionsF16.d ./CMSIS/Source/BayesFunctions/BayesFunctionsF16.o ./CMSIS/Source/BayesFunctions/BayesFunctionsF16.su ./CMSIS/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f16.cyclo ./CMSIS/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f16.d ./CMSIS/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f16.o ./CMSIS/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f16.su ./CMSIS/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.cyclo ./CMSIS/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.d ./CMSIS/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.o ./CMSIS/Source/BayesFunctions/arm_gaussian_naive_bayes_predict_f32.su

.PHONY: clean-CMSIS-2f-Source-2f-BayesFunctions

