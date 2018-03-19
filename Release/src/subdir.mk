################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Run.cpp \
../src/testcppcreate.cpp \
../src/testcppmain.cpp \
../src/testcppquery.cpp 

OBJS += \
./src/Run.o \
./src/testcppcreate.o \
./src/testcppmain.o \
./src/testcppquery.o 

CPP_DEPS += \
./src/Run.d \
./src/testcppcreate.d \
./src/testcppmain.d \
./src/testcppquery.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/home/brian/ThingSpan/15.6/include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


