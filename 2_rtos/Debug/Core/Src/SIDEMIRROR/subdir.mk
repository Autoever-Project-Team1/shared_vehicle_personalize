################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/SIDEMIRROR/sidemirror.c 

OBJS += \
./Core/Src/SIDEMIRROR/sidemirror.o 

C_DEPS += \
./Core/Src/SIDEMIRROR/sidemirror.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/SIDEMIRROR/%.o Core/Src/SIDEMIRROR/%.su Core/Src/SIDEMIRROR/%.cyclo: ../Core/Src/SIDEMIRROR/%.c Core/Src/SIDEMIRROR/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F091xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-SIDEMIRROR

clean-Core-2f-Src-2f-SIDEMIRROR:
	-$(RM) ./Core/Src/SIDEMIRROR/sidemirror.cyclo ./Core/Src/SIDEMIRROR/sidemirror.d ./Core/Src/SIDEMIRROR/sidemirror.o ./Core/Src/SIDEMIRROR/sidemirror.su

.PHONY: clean-Core-2f-Src-2f-SIDEMIRROR

