################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/HEADLIGHT/headlight.c 

OBJS += \
./Core/Src/HEADLIGHT/headlight.o 

C_DEPS += \
./Core/Src/HEADLIGHT/headlight.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/HEADLIGHT/%.o Core/Src/HEADLIGHT/%.su Core/Src/HEADLIGHT/%.cyclo: ../Core/Src/HEADLIGHT/%.c Core/Src/HEADLIGHT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F091xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-HEADLIGHT

clean-Core-2f-Src-2f-HEADLIGHT:
	-$(RM) ./Core/Src/HEADLIGHT/headlight.cyclo ./Core/Src/HEADLIGHT/headlight.d ./Core/Src/HEADLIGHT/headlight.o ./Core/Src/HEADLIGHT/headlight.su

.PHONY: clean-Core-2f-Src-2f-HEADLIGHT

