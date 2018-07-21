################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/testcppcreate.cpp \
../src/testcppcreateall.cpp \
../src/testcppmain.cpp \
../src/testcppquery.cpp \
../src/testcppschema.cpp 

OBJS += \
./src/testcppcreate.o \
./src/testcppcreateall.o \
./src/testcppmain.o \
./src/testcppquery.o \
./src/testcppschema.o 

CPP_DEPS += \
./src/testcppcreate.d \
./src/testcppcreateall.d \
./src/testcppmain.d \
./src/testcppquery.d \
./src/testcppschema.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/ThingSpan/15.7/include -includeooObjy.h -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -std=c++11 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


