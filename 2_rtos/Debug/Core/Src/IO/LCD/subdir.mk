################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/IO/LCD/lcd.c \
../Core/Src/IO/LCD/lcd_cfg.c 

OBJS += \
./Core/Src/IO/LCD/lcd.o \
./Core/Src/IO/LCD/lcd_cfg.o 

C_DEPS += \
./Core/Src/IO/LCD/lcd.d \
./Core/Src/IO/LCD/lcd_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/IO/LCD/%.o Core/Src/IO/LCD/%.su Core/Src/IO/LCD/%.cyclo: ../Core/Src/IO/LCD/%.c Core/Src/IO/LCD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F091xC -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-IO-2f-LCD

clean-Core-2f-Src-2f-IO-2f-LCD:
	-$(RM) ./Core/Src/IO/LCD/lcd.cyclo ./Core/Src/IO/LCD/lcd.d ./Core/Src/IO/LCD/lcd.o ./Core/Src/IO/LCD/lcd.su ./Core/Src/IO/LCD/lcd_cfg.cyclo ./Core/Src/IO/LCD/lcd_cfg.d ./Core/Src/IO/LCD/lcd_cfg.o ./Core/Src/IO/LCD/lcd_cfg.su

.PHONY: clean-Core-2f-Src-2f-IO-2f-LCD

