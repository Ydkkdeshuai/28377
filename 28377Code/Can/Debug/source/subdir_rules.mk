################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
source/%.obj: ../source/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/Tools/Study_Tools/CCS/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --cla_support=cla1 --include_path="D:/Tools/Study_Tools/CCS/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/Data/QQ/3307793931/FileRecv/example/lab30_can_loopback_interrupts" --include_path="D:/Data/QQ/3307793931/FileRecv/example/lab30_can_loopback_interrupts/include" -g --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/%.obj: ../source/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/Tools/Study_Tools/CCS/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --cla_support=cla1 --include_path="D:/Tools/Study_Tools/CCS/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/Data/QQ/3307793931/FileRecv/example/lab30_can_loopback_interrupts" --include_path="D:/Data/QQ/3307793931/FileRecv/example/lab30_can_loopback_interrupts/include" -g --diag_wrap=off --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


