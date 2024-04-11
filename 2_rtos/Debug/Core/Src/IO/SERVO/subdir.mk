################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/IO/SERVO/servo.c 

OBJS += \
./Core/Src/IO/SERVO/servo.o 

C_DEPS += \
./Core/Src/IO/SERVO/servo.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/IO/SERVO/%.o Core/Src/IO/SERVO/%.su Core/Src/IO/SERVO/%.cyclo: ../Core/Src/IO/SERVO/%.c Core/Src/IO/SERVO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F091xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-IO-2f-SERVO

clean-Core-2f-Src-2f-IO-2f-SERVO:
	-$(RM) ./Core/Src/IO/SERVO/servo.cyclo ./Core/Src/IO/SERVO/servo.d ./Core/Src/IO/SERVO/servo.o ./Core/Src/IO/SERVO/servo.su

.PHONY: clean-Core-2f-Src-2f-IO-2f-SERVO

