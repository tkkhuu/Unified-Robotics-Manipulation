################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ACC.c \
../ADCSetup.c \
../DAC.c \
../Encoder.c \
../EndEffector.c \
../IRSensor.c \
../Junk.c \
../MathFunction.c \
../PIDController.c \
../SPI.c \
../TimerSetup.c \
../USARTSetup.c \
../main.c 

OBJS += \
./ACC.o \
./ADCSetup.o \
./DAC.o \
./Encoder.o \
./EndEffector.o \
./IRSensor.o \
./Junk.o \
./MathFunction.o \
./PIDController.o \
./SPI.o \
./TimerSetup.o \
./USARTSetup.o \
./main.o 

C_DEPS += \
./ACC.d \
./ADCSetup.d \
./DAC.d \
./Encoder.d \
./EndEffector.d \
./IRSensor.d \
./Junk.d \
./MathFunction.d \
./PIDController.d \
./SPI.d \
./TimerSetup.d \
./USARTSetup.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\Tri Khuu\Documents\Eclipse\workspace\RBELib\include" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=18432000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


