KERNEL = bin/kernel.elf
ASM_FLAGS = -mcpu=arm1176jzf-s
CFLAGS = $(ASM_FLAGS) -ffreestanding -I src/include
LDFLAGS = -T linker.ld -nostartfiles -nostdlib
TOOLCHAIN ?= arm-none-eabi-
C_SOURCES = $(wildcard src/*.c)
ASM_SOURCES = $(wildcard src/*.s)
C_OBJS = $(C_SOURCES:src/%.c=bin/%.co)
ASM_OBJS = $(ASM_SOURCES:src/%.s=bin/%.o)
.PHONY: build run clean
build: $(KERNEL)
$(KERNEL): $(ASM_OBJS) $(C_OBJS)
	$(TOOLCHAIN)gcc -o $@ $(LDFLAGS) $(CFLAGS) $^
bin/%.co: src/%.c | bin
	$(TOOLCHAIN)gcc -c -o $@ $(CFLAGS) $<
bin/%.o: src/%.s | bin
	$(TOOLCHAIN)as -o $@ $(ASM_FLAGS) $<
bin:
	mkdir $@
run:
	qemu-system-arm -M raspi0 -m 512M -kernel $(KERNEL)
clean:
	rm -rf bin
