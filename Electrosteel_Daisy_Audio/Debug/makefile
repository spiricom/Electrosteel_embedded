################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include leaf/Src/subdir.mk
-include leaf/Inc/subdir.mk
-include leaf/Externals/subdir.mk
-include Middlewares/Third_Party/FatFs/src/option/subdir.mk
-include Middlewares/Third_Party/FatFs/src/subdir.mk
-include FATFS/Target/subdir.mk
-include FATFS/App/subdir.mk
-include Drivers/STM32H7xx_HAL_Driver/Src/subdir.mk
-include Core/Src/subdir.mk
-include CMSIS/Source/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Electrosteel_Daisy_Audio
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Electrosteel_Daisy_Audio.elf \

MAP_FILES += \
Electrosteel_Daisy_Audio.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Electrosteel_Daisy_Audio.list \

OBJCOPY_BIN += \
Electrosteel_Daisy_Audio.bin \


# All Target
all: main-build

# Main-build Target
main-build: Electrosteel_Daisy_Audio.elf secondary-outputs

# Tool invocations
Electrosteel_Daisy_Audio.elf Electrosteel_Daisy_Audio.map: $(OBJS) $(USER_OBJS) /Users/jeffsnyder/dev/Electrosteel_embedded/Electrosteel_Daisy_Audio/STM32H750IBKX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Electrosteel_Daisy_Audio.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"/Users/jeffsnyder/dev/Electrosteel_embedded/Electrosteel_Daisy_Audio/STM32H750IBKX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Electrosteel_Daisy_Audio.map" -Wl,--cref -Wl,--gc-sections -nodefaultlibs -static -lnosys --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Electrosteel_Daisy_Audio.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Electrosteel_Daisy_Audio.list"
	@echo 'Finished building: $@'
	@echo ' '

Electrosteel_Daisy_Audio.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Electrosteel_Daisy_Audio.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Electrosteel_Daisy_Audio.bin Electrosteel_Daisy_Audio.elf Electrosteel_Daisy_Audio.list Electrosteel_Daisy_Audio.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
