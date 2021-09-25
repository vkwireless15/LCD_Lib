################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/SimpleGraphics/Coordinates.c \
../Core/SimpleGraphics/Font.c \
../Core/SimpleGraphics/Graphics_IO.c \
../Core/SimpleGraphics/SimpleGraphics.c \
../Core/SimpleGraphics/Touch.c 

OBJS += \
./Core/SimpleGraphics/Coordinates.o \
./Core/SimpleGraphics/Font.o \
./Core/SimpleGraphics/Graphics_IO.o \
./Core/SimpleGraphics/SimpleGraphics.o \
./Core/SimpleGraphics/Touch.o 

C_DEPS += \
./Core/SimpleGraphics/Coordinates.d \
./Core/SimpleGraphics/Font.d \
./Core/SimpleGraphics/Graphics_IO.d \
./Core/SimpleGraphics/SimpleGraphics.d \
./Core/SimpleGraphics/Touch.d 


# Each subdirectory must supply rules for building sources it contributes
Core/SimpleGraphics/%.o: ../Core/SimpleGraphics/%.c Core/SimpleGraphics/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F746xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"D:/Repo/GitHub/LCD_Lib/Core/SimpleGraphics" -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

