################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include STM32f103_Drivers/subdir.mk
-include RSA_Algorithm/subdir.mk
-include FreeRTOS/portable/MemMang/subdir.mk
-include FreeRTOS/portable/GCC/ARM_CM3/subdir.mk
-include FreeRTOS/subdir.mk
-include subdir.mk
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

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Session3_Uart_Com.axf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Session3_Uart_Com.list \

OBJCOPY_BIN += \
Session3_Uart_Com.bin \


# All Target
all: Session3_Uart_Com.axf secondary-outputs

# Tool invocations
Session3_Uart_Com.axf: $(OBJS) $(USER_OBJS) C:\Users\musta\Session3_Uart_Com\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -o "Session3_Uart_Com.axf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\musta\Session3_Uart_Com\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Session3_Uart_Com.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Session3_Uart_Com.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Session3_Uart_Com.list"
	@echo 'Finished building: $@'
	@echo ' '

Session3_Uart_Com.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Session3_Uart_Com.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
