################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/croutine.c \
../FreeRTOS/event_groups.c \
../FreeRTOS/list.c \
../FreeRTOS/queue.c \
../FreeRTOS/stream_buffer.c \
../FreeRTOS/tasks.c \
../FreeRTOS/timers.c 

OBJS += \
./FreeRTOS/croutine.o \
./FreeRTOS/event_groups.o \
./FreeRTOS/list.o \
./FreeRTOS/queue.o \
./FreeRTOS/stream_buffer.o \
./FreeRTOS/tasks.o \
./FreeRTOS/timers.o 

C_DEPS += \
./FreeRTOS/croutine.d \
./FreeRTOS/event_groups.d \
./FreeRTOS/list.d \
./FreeRTOS/queue.d \
./FreeRTOS/stream_buffer.d \
./FreeRTOS/tasks.d \
./FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/croutine.o: ../FreeRTOS/croutine.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/musta/Session3_Uart_Com/RSA_Algorithm" -I"C:/Users/musta/Session3_Uart_Com/FreeRTOS/include" -I"C:/Users/musta/Session3_Uart_Com/FreeRTOS/portable/GCC/ARM_CM3" -I"C:/Users/musta/Session3_Uart_Com/STM32f103_Drivers/INC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/croutine.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FreeRTOS/event_groups.o: ../FreeRTOS/event_groups.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/musta/Session3_Uart_Com/RSA_Algorithm" -I"C:/Users/musta/Session3_Uart_Com/FreeRTOS/include" -I"C:/Users/musta/Session3_Uart_Com/FreeRTOS/portable/GCC/ARM_CM3" -I"C:/Users/musta/Session3_Uart_Com/STM32f103_Drivers/INC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/event_groups.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FreeRTOS/list.o: ../FreeRTOS/list.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/musta/Session3_Uart_Com/RSA_Algorithm" -I"C:/Users/musta/Session3_Uart_Com/FreeRTOS/include" -I"C:/Users/musta/Session3_Uart_Com/FreeRTOS/portable/GCC/ARM_CM3" -I"C:/Users/musta/Session3_Uart_Com/STM32f103_Drivers/INC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/list.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FreeRTOS/queue.o: ../FreeRTOS/queue.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/musta/Session3_Uart_Com/RSA_Algorithm" -I"C:/Users/musta/Session3_Uart_Com/FreeRTOS/include" -I"C:/Users/musta/Session3_Uart_Com/FreeRTOS/portable/GCC/ARM_CM3" -I"C:/Users/musta/Session3_Uart_Com/STM32f103_Drivers/INC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/queue.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FreeRTOS/stream_buffer.o: ../FreeRTOS/stream_buffer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/musta/Session3_Uart_Com/RSA_Algorithm" -I"C:/Users/musta/Session3_Uart_Com/FreeRTOS/include" -I"C:/Users/musta/Session3_Uart_Com/FreeRTOS/portable/GCC/ARM_CM3" -I"C:/Users/musta/Session3_Uart_Com/STM32f103_Drivers/INC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/stream_buffer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FreeRTOS/tasks.o: ../FreeRTOS/tasks.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/musta/Session3_Uart_Com/RSA_Algorithm" -I"C:/Users/musta/Session3_Uart_Com/FreeRTOS/include" -I"C:/Users/musta/Session3_Uart_Com/FreeRTOS/portable/GCC/ARM_CM3" -I"C:/Users/musta/Session3_Uart_Com/STM32f103_Drivers/INC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/tasks.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FreeRTOS/timers.o: ../FreeRTOS/timers.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/musta/Session3_Uart_Com/RSA_Algorithm" -I"C:/Users/musta/Session3_Uart_Com/FreeRTOS/include" -I"C:/Users/musta/Session3_Uart_Com/FreeRTOS/portable/GCC/ARM_CM3" -I"C:/Users/musta/Session3_Uart_Com/STM32f103_Drivers/INC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"FreeRTOS/timers.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

