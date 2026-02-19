CFLAGS := -o out.elf -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Wall -Wextra -Werror -g -Og
CSOURCES := ./main.c ./syscalls.c ./uart.c ./CMSIS/Device/Source/system_stm32f4xx.c ./init.c ./startup.c
CINCLUDE := -I./CMSIS/Core/Include -I./CMSIS/Core/Include/m-profile -I./CMSIS/Device/Include
OUTPUT := -o out.elf
LINK := -T ./linkerscript_picolibc.ld

GCC := arm-none-eabi-gcc
GCCFLAGS:= -specs=picolibc.specs

CLANG := clang
CLANGFLAGS := --target=arm-none-eabi

gcc:
	$(GCC) $(CSOURCES) $(GCCCSOURCES) $(LINK) $(CFLAGS) $(GCCFLAGS) $(CINCLUDE) $(OUTPUT)

clang:
	$(CLANG) $(CSOURCES) $(CLANGCSOURCES) $(LINK) $(CFLAGS) $(CLANGFLAGS) $(CINCLUDE) $(OUTPUT)

.PHONY: clean flash

clean: 
	-del *.elf 
	-del *.bin 
	-del *.hex

flash: 
	pyocd load out.elf