################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f303xe.s 

OBJS += \
./startup/startup_stm32f303xe.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I"C:/Users/xswsx/git/IPL_Weiche/IPL_Weiche/inc" -I"C:/Users/xswsx/git/IPL_Weiche/IPL_Weiche/CMSIS/core" -I"C:/Users/xswsx/git/IPL_Weiche/IPL_Weiche/CMSIS/device" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


