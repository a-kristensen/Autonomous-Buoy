################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/WindTask/WindTask.c 

OBJS += \
./Src/WindTask/WindTask.o 

C_DEPS += \
./Src/WindTask/WindTask.d 


# Each subdirectory must supply rules for building sources it contributes
Src/WindTask/%.o: ../Src/WindTask/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F429xx -I"C:/Users/Neophyte/Desktop/Autobuoy/Inc" -I"C:/Users/Neophyte/Desktop/Autobuoy/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Neophyte/Desktop/Autobuoy/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Neophyte/Desktop/Autobuoy/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/Neophyte/Desktop/Autobuoy/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Neophyte/Desktop/Autobuoy/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/Neophyte/Desktop/Autobuoy/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/Neophyte/Desktop/Autobuoy/Drivers/CMSIS/Include" -I"C:/Users/Neophyte/Desktop/Autobuoy/Inc"  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


