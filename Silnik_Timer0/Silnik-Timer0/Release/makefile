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
Silnik-Timer0.lss \

FLASH_IMAGE += \
Silnik-Timer0.hex \

EEPROM_IMAGE += \
Silnik-Timer0.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Silnik-Timer0.elf secondary-outputs

# Tool invocations
Silnik-Timer0.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Silnik-Timer0.map -mmcu=atmega32 -o "Silnik-Timer0.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Silnik-Timer0.lss: Silnik-Timer0.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Silnik-Timer0.elf  >"Silnik-Timer0.lss"
	@echo 'Finished building: $@'
	@echo ' '

Silnik-Timer0.hex: Silnik-Timer0.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Silnik-Timer0.elf  "Silnik-Timer0.hex"
	@echo 'Finished building: $@'
	@echo ' '

Silnik-Timer0.eep: Silnik-Timer0.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Silnik-Timer0.elf  "Silnik-Timer0.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Silnik-Timer0.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Silnik-Timer0.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Silnik-Timer0.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
