################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/gpio.c \
../MCAL/pwm.c \
../MCAL/timer.c 

OBJS += \
./MCAL/gpio.o \
./MCAL/pwm.o \
./MCAL/timer.o 

C_DEPS += \
./MCAL/gpio.d \
./MCAL/pwm.d \
./MCAL/timer.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/%.o: ../MCAL/%.c MCAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\my projects\LightningAndVisibilityFinal\LightningAndVisibilityFinal\HAL" -I"D:\my projects\LightningAndVisibilityFinal\LightningAndVisibilityFinal\MCAL" -I"D:\my projects\LightningAndVisibilityFinal\LightningAndVisibilityFinal" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


