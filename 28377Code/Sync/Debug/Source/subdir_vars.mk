################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../Source/F2837xD_CodeStartBranch.asm \
../Source/F2837xD_DBGIER.asm \
../Source/F2837xD_usDelay.asm 

C_SRCS += \
../Source/F2837xD_Adc.c \
../Source/F2837xD_CpuTimers.c \
../Source/F2837xD_DefaultISR.c \
../Source/F2837xD_Dma.c \
../Source/F2837xD_ECap.c \
../Source/F2837xD_EPwm.c \
../Source/F2837xD_EQep.c \
../Source/F2837xD_Emif.c \
../Source/F2837xD_GlobalVariableDefs.c \
../Source/F2837xD_Gpio.c \
../Source/F2837xD_I2C.c \
../Source/F2837xD_Ipc.c \
../Source/F2837xD_Ipc_Driver.c \
../Source/F2837xD_Ipc_Driver_Lite.c \
../Source/F2837xD_Ipc_Driver_Util.c \
../Source/F2837xD_Mcbsp.c \
../Source/F2837xD_PieCtrl.c \
../Source/F2837xD_PieVect.c \
../Source/F2837xD_Sci.c \
../Source/F2837xD_Spi.c \
../Source/F2837xD_SysCtrl.c \
../Source/F2837xD_TempSensorConv.c \
../Source/F2837xD_Upp.c \
../Source/F2837xD_can.c \
../Source/F2837xD_sci_io.c \
../Source/F2837xD_sdfm_drivers.c \
../Source/F2837xD_struct.c 

C_DEPS += \
./Source/F2837xD_Adc.d \
./Source/F2837xD_CpuTimers.d \
./Source/F2837xD_DefaultISR.d \
./Source/F2837xD_Dma.d \
./Source/F2837xD_ECap.d \
./Source/F2837xD_EPwm.d \
./Source/F2837xD_EQep.d \
./Source/F2837xD_Emif.d \
./Source/F2837xD_GlobalVariableDefs.d \
./Source/F2837xD_Gpio.d \
./Source/F2837xD_I2C.d \
./Source/F2837xD_Ipc.d \
./Source/F2837xD_Ipc_Driver.d \
./Source/F2837xD_Ipc_Driver_Lite.d \
./Source/F2837xD_Ipc_Driver_Util.d \
./Source/F2837xD_Mcbsp.d \
./Source/F2837xD_PieCtrl.d \
./Source/F2837xD_PieVect.d \
./Source/F2837xD_Sci.d \
./Source/F2837xD_Spi.d \
./Source/F2837xD_SysCtrl.d \
./Source/F2837xD_TempSensorConv.d \
./Source/F2837xD_Upp.d \
./Source/F2837xD_can.d \
./Source/F2837xD_sci_io.d \
./Source/F2837xD_sdfm_drivers.d \
./Source/F2837xD_struct.d 

OBJS += \
./Source/F2837xD_Adc.obj \
./Source/F2837xD_CodeStartBranch.obj \
./Source/F2837xD_CpuTimers.obj \
./Source/F2837xD_DBGIER.obj \
./Source/F2837xD_DefaultISR.obj \
./Source/F2837xD_Dma.obj \
./Source/F2837xD_ECap.obj \
./Source/F2837xD_EPwm.obj \
./Source/F2837xD_EQep.obj \
./Source/F2837xD_Emif.obj \
./Source/F2837xD_GlobalVariableDefs.obj \
./Source/F2837xD_Gpio.obj \
./Source/F2837xD_I2C.obj \
./Source/F2837xD_Ipc.obj \
./Source/F2837xD_Ipc_Driver.obj \
./Source/F2837xD_Ipc_Driver_Lite.obj \
./Source/F2837xD_Ipc_Driver_Util.obj \
./Source/F2837xD_Mcbsp.obj \
./Source/F2837xD_PieCtrl.obj \
./Source/F2837xD_PieVect.obj \
./Source/F2837xD_Sci.obj \
./Source/F2837xD_Spi.obj \
./Source/F2837xD_SysCtrl.obj \
./Source/F2837xD_TempSensorConv.obj \
./Source/F2837xD_Upp.obj \
./Source/F2837xD_can.obj \
./Source/F2837xD_sci_io.obj \
./Source/F2837xD_sdfm_drivers.obj \
./Source/F2837xD_struct.obj \
./Source/F2837xD_usDelay.obj 

ASM_DEPS += \
./Source/F2837xD_CodeStartBranch.d \
./Source/F2837xD_DBGIER.d \
./Source/F2837xD_usDelay.d 

OBJS__QUOTED += \
"Source\F2837xD_Adc.obj" \
"Source\F2837xD_CodeStartBranch.obj" \
"Source\F2837xD_CpuTimers.obj" \
"Source\F2837xD_DBGIER.obj" \
"Source\F2837xD_DefaultISR.obj" \
"Source\F2837xD_Dma.obj" \
"Source\F2837xD_ECap.obj" \
"Source\F2837xD_EPwm.obj" \
"Source\F2837xD_EQep.obj" \
"Source\F2837xD_Emif.obj" \
"Source\F2837xD_GlobalVariableDefs.obj" \
"Source\F2837xD_Gpio.obj" \
"Source\F2837xD_I2C.obj" \
"Source\F2837xD_Ipc.obj" \
"Source\F2837xD_Ipc_Driver.obj" \
"Source\F2837xD_Ipc_Driver_Lite.obj" \
"Source\F2837xD_Ipc_Driver_Util.obj" \
"Source\F2837xD_Mcbsp.obj" \
"Source\F2837xD_PieCtrl.obj" \
"Source\F2837xD_PieVect.obj" \
"Source\F2837xD_Sci.obj" \
"Source\F2837xD_Spi.obj" \
"Source\F2837xD_SysCtrl.obj" \
"Source\F2837xD_TempSensorConv.obj" \
"Source\F2837xD_Upp.obj" \
"Source\F2837xD_can.obj" \
"Source\F2837xD_sci_io.obj" \
"Source\F2837xD_sdfm_drivers.obj" \
"Source\F2837xD_struct.obj" \
"Source\F2837xD_usDelay.obj" 

C_DEPS__QUOTED += \
"Source\F2837xD_Adc.d" \
"Source\F2837xD_CpuTimers.d" \
"Source\F2837xD_DefaultISR.d" \
"Source\F2837xD_Dma.d" \
"Source\F2837xD_ECap.d" \
"Source\F2837xD_EPwm.d" \
"Source\F2837xD_EQep.d" \
"Source\F2837xD_Emif.d" \
"Source\F2837xD_GlobalVariableDefs.d" \
"Source\F2837xD_Gpio.d" \
"Source\F2837xD_I2C.d" \
"Source\F2837xD_Ipc.d" \
"Source\F2837xD_Ipc_Driver.d" \
"Source\F2837xD_Ipc_Driver_Lite.d" \
"Source\F2837xD_Ipc_Driver_Util.d" \
"Source\F2837xD_Mcbsp.d" \
"Source\F2837xD_PieCtrl.d" \
"Source\F2837xD_PieVect.d" \
"Source\F2837xD_Sci.d" \
"Source\F2837xD_Spi.d" \
"Source\F2837xD_SysCtrl.d" \
"Source\F2837xD_TempSensorConv.d" \
"Source\F2837xD_Upp.d" \
"Source\F2837xD_can.d" \
"Source\F2837xD_sci_io.d" \
"Source\F2837xD_sdfm_drivers.d" \
"Source\F2837xD_struct.d" 

ASM_DEPS__QUOTED += \
"Source\F2837xD_CodeStartBranch.d" \
"Source\F2837xD_DBGIER.d" \
"Source\F2837xD_usDelay.d" 

C_SRCS__QUOTED += \
"../Source/F2837xD_Adc.c" \
"../Source/F2837xD_CpuTimers.c" \
"../Source/F2837xD_DefaultISR.c" \
"../Source/F2837xD_Dma.c" \
"../Source/F2837xD_ECap.c" \
"../Source/F2837xD_EPwm.c" \
"../Source/F2837xD_EQep.c" \
"../Source/F2837xD_Emif.c" \
"../Source/F2837xD_GlobalVariableDefs.c" \
"../Source/F2837xD_Gpio.c" \
"../Source/F2837xD_I2C.c" \
"../Source/F2837xD_Ipc.c" \
"../Source/F2837xD_Ipc_Driver.c" \
"../Source/F2837xD_Ipc_Driver_Lite.c" \
"../Source/F2837xD_Ipc_Driver_Util.c" \
"../Source/F2837xD_Mcbsp.c" \
"../Source/F2837xD_PieCtrl.c" \
"../Source/F2837xD_PieVect.c" \
"../Source/F2837xD_Sci.c" \
"../Source/F2837xD_Spi.c" \
"../Source/F2837xD_SysCtrl.c" \
"../Source/F2837xD_TempSensorConv.c" \
"../Source/F2837xD_Upp.c" \
"../Source/F2837xD_can.c" \
"../Source/F2837xD_sci_io.c" \
"../Source/F2837xD_sdfm_drivers.c" \
"../Source/F2837xD_struct.c" 

ASM_SRCS__QUOTED += \
"../Source/F2837xD_CodeStartBranch.asm" \
"../Source/F2837xD_DBGIER.asm" \
"../Source/F2837xD_usDelay.asm" 


