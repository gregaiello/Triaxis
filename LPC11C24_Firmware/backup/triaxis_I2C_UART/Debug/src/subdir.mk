################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc11xx.c \
../src/sysinit.c \
../src/triaxis_I2C_UART.c 

OBJS += \
./src/cr_startup_lpc11xx.o \
./src/sysinit.o \
./src/triaxis_I2C_UART.o 

C_DEPS += \
./src/cr_startup_lpc11xx.d \
./src/sysinit.d \
./src/triaxis_I2C_UART.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -DNO_BOARD_LIB -DCORE_M0 -D__USE_LPCOPEN -D__LPC11XX__ -I"C:\Users\aiellog\Documents\MCUXpressoIDE_10.0.2_411\workspace\lpc_chip_11cxx_lib\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


