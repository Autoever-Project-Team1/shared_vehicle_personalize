################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/PROTOCOL/protocol.c 

OBJS += \
./Core/Src/PROTOCOL/protocol.o 

C_DEPS += \
./Core/Src/PROTOCOL/protocol.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/PROTOCOL/%.o Core/Src/PROTOCOL/%.su Core/Src/PROTOCOL/%.cyclo: ../Core/Src/PROTOCOL/%.c Core/Src/PROTOCOL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F091xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-PROTOCOL

clean-Core-2f-Src-2f-PROTOCOL:
	-$(RM) ./Core/Src/PROTOCOL/protocol.cyclo ./Core/Src/PROTOCOL/protocol.d ./Core/Src/PROTOCOL/protocol.o ./Core/Src/PROTOCOL/protocol.su

.PHONY: clean-Core-2f-Src-2f-PROTOCOL

