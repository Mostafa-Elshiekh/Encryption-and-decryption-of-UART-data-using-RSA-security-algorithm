################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RSA_Algorithm/RSA_Algorithm.c 

OBJS += \
./RSA_Algorithm/RSA_Algorithm.o 

C_DEPS += \
./RSA_Algorithm/RSA_Algorithm.d 


# Each subdirectory must supply rules for building sources it contributes
RSA_Algorithm/RSA_Algorithm.o: ../RSA_Algorithm/RSA_Algorithm.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/musta/Session3_Uart_Com/RSA_Algorithm" -I"C:/Users/musta/Session3_Uart_Com/FreeRTOS/include" -I"C:/Users/musta/Session3_Uart_Com/FreeRTOS/portable/GCC/ARM_CM3" -I"C:/Users/musta/Session3_Uart_Com/STM32f103_Drivers/INC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"RSA_Algorithm/RSA_Algorithm.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

