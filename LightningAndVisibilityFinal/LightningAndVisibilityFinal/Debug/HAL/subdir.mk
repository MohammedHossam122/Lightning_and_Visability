################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/dc_motor.c \
../HAL/keypad.c \
../HAL/lcd.c 

OBJS += \
./HAL/dc_motor.o \
./HAL/keypad.o \
./HAL/lcd.o 

C_DEPS += \
./HAL/dc_motor.d \
./HAL/keypad.d \
./HAL/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c HAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\my projects\LightningAndVisibilityFinal\LightningAndVisibilityFinal\HAL" -I"D:\my projects\LightningAndVisibilityFinal\LightningAndVisibilityFinal\MCAL" -I"D:\my projects\LightningAndVisibilityFinal\LightningAndVisibilityFinal" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


