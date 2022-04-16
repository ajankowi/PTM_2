################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
SD_gotowy.lss \

FLASH_IMAGE += \
SD_gotowy.hex \

EEPROM_IMAGE += \
SD_gotowy.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: SD_gotowy.elf secondary-outputs

# Tool invocations
SD_gotowy.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,SD_gotowy.map -mmcu=atmega32 -o "SD_gotowy.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

SD_gotowy.lss: SD_gotowy.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S SD_gotowy.elf  >"SD_gotowy.lss"
	@echo 'Finished building: $@'
	@echo ' '

SD_gotowy.hex: SD_gotowy.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex SD_gotowy.elf  "SD_gotowy.hex"
	@echo 'Finished building: $@'
	@echo ' '

SD_gotowy.eep: SD_gotowy.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex SD_gotowy.elf  "SD_gotowy.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: SD_gotowy.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 SD_gotowy.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) SD_gotowy.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
