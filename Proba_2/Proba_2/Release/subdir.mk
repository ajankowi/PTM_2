################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HD44780.c \
../VL53L0X.c \
../i2cmaster.c \
../main.c \
../millis.c \
../vl53l0xExample.c 

OBJS += \
./HD44780.o \
./VL53L0X.o \
./i2cmaster.o \
./main.o \
./millis.o \
./vl53l0xExample.o 

C_DEPS += \
./HD44780.d \
./VL53L0X.d \
./i2cmaster.d \
./main.d \
./millis.d \
./vl53l0xExample.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


