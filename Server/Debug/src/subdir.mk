################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Messsage.c \
../src/Network.c \
../src/Operations.c \
../src/Server.c 

OBJS += \
./src/Messsage.o \
./src/Network.o \
./src/Operations.o \
./src/Server.o 

C_DEPS += \
./src/Messsage.d \
./src/Network.d \
./src/Operations.d \
./src/Server.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


