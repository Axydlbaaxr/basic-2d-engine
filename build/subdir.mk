################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../PStoXPM.cc 

CPP_SRCS += \
../CmdLine.cpp \
../Color.cpp \
../Command.cpp \
../Line.cpp \
../PSFile.cpp \
../XPMData.cpp 

CPP_DEPS += \
./CmdLine.d \
./Color.d \
./Command.d \
./Line.d \
./PSFile.d \
./XPMData.d 

OBJS += \
./CmdLine.o \
./Color.o \
./Command.o \
./Line.o \
./PSFile.o \
./PStoXPM.o \
./XPMData.o 

CC_DEPS += \
./PStoXPM.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


