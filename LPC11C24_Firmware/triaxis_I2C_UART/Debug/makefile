################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: triaxis_I2C_UART.axf

# Tool invocations
triaxis_I2C_UART.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\aiellog\Documents\MCUXpressoIDE_10.0.2_411\workspace\lpc_chip_11cxx_lib\Debug" -Xlinker -Map="triaxis_I2C_UART.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0 -mthumb -T "triaxis_I2C_UART_Debug.ld" -o "triaxis_I2C_UART.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) triaxis_I2C_UART.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "triaxis_I2C_UART.axf"; # arm-none-eabi-objcopy -v -O binary "triaxis_I2C_UART.axf" "triaxis_I2C_UART.bin" ; # checksum -p LPC11C24_301 -d "triaxis_I2C_UART.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
