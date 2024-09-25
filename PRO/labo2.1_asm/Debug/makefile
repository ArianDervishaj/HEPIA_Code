################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: labo2.1_asm.axf

# Tool invocations
labo2.1_asm.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="labo2.1_asm.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "labo2_1_asm_Debug.ld" -o "labo2.1_asm.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) labo2.1_asm.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "labo2.1_asm.axf"; # arm-none-eabi-objcopy -O binary "labo2.1_asm.axf" "labo2.1_asm.bin" ; checksum -p LPC1769 -d "labo2.1_asm.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
