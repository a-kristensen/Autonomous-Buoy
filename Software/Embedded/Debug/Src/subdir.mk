################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/freertos.c \
../Src/gpio.c \
../Src/iwdg.c \
../Src/main.c \
../Src/spi.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_hal_timebase_TIM.c \
../Src/stm32f4xx_it.c \
../Src/syscalls.c \
../Src/system_stm32f4xx.c \
../Src/usart.c \
../Src/wwdg.c 

OBJS += \
./Src/freertos.o \
./Src/gpio.o \
./Src/iwdg.o \
./Src/main.o \
./Src/spi.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_hal_timebase_TIM.o \
./Src/stm32f4xx_it.o \
./Src/syscalls.o \
./Src/system_stm32f4xx.o \
./Src/usart.o \
./Src/wwdg.o 

C_DEPS += \
./Src/freertos.d \
./Src/gpio.d \
./Src/iwdg.d \
./Src/main.d \
./Src/spi.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_hal_timebase_TIM.d \
./Src/stm32f4xx_it.d \
./Src/syscalls.d \
./Src/system_stm32f4xx.d \
./Src/usart.d \
./Src/wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F429xx -I"C:/Users/Neophyte/Desktop/Autobuoy/Inc" -I"C:/Users/Neophyte/Desktop/Autobuoy/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Neophyte/Desktop/Autobuoy/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Neophyte/Desktop/Autobuoy/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/Neophyte/Desktop/Autobuoy/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Neophyte/Desktop/Autobuoy/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/Neophyte/Desktop/Autobuoy/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/Neophyte/Desktop/Autobuoy/Drivers/CMSIS/Include" -I"C:/Users/Neophyte/Desktop/Autobuoy/Inc"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


