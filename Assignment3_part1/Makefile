# Makefile for Raspberry Pi 3

OBJS = lib/startup.o lib/syscalls.o lib/tinythreads.o lib/piface.o lib/iexp.o main.o
ELF	    = rteskernel4.elf
MAIN	= rteskernel4.img

CROSS	= arm-none-eabi-
CC	    = $(CROSS)gcc
SIZE	= $(CROSS)size
OCOPY	= $(CROSS)objcopy

CFLAGS	= -march=armv8-a -mfpu=vfp -mfloat-abi=soft -ffunction-sections -fdata-sections -fno-common -g -std=gnu99 -Wall -Wextra -Os -Ilib
LFLAGS	= -static -nostartfiles -lc -lgcc -specs=nano.specs -Wl,--gc-sections
LSCRIPT	= lib/rpi3.ld

.PHONY: all clean run

all: $(MAIN)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

$(ELF): $(OBJS)
	$(CC) -T$(LSCRIPT) $(CFLAGS) $(LFLAGS) -o $@ $^
	$(SIZE) $@

$(MAIN): $(ELF)
	$(OCOPY) $< -O binary $@

clean:
	rm -f $(MAIN) $(ELF) $(OBJS)

run: $(MAIN)

