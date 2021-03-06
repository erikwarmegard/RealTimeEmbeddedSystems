# Makefile for Raspberry Pi 3

OBJS	= lib/piface.o lib/rpi-armtimer.o lib/rpi-gpio.o lib/rpi-interrupts.o lib/rpi-systimer.o lib/startup.o lib/syscalls.o lib/tinythreads.o main.o
ELF		= rteskernel4.elf
MAIN	= rteskernel4.img

CROSS	= arm-none-eabi-
CC		= $(CROSS)gcc
AS		= $(CROSS)as
SIZE	= $(CROSS)size
OCOPY	= $(CROSS)objcopy

CFLAGS	= -march=armv8-a -mcpu=cortex-a53 -mfpu=vfp -mfloat-abi=soft -ffunction-sections -fdata-sections -fno-common -g -std=gnu99 -Wall -Wextra -Os -Ilib -DRPI3=1 -DIOBPLUS=1

LFLAGS	= -static -nostartfiles -lc -lgcc -specs=nano.specs -Wl,--gc-sections
LSCRIPT	= lib/rpi3.ld

LDFLAGS	+= -u _printf_float

.PHONY: all clean run

all: $(MAIN)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

$(ELF): $(OBJS)
	$(CC) -T $(LSCRIPT) $(CFLAGS) $(LFLAGS) $(LDFLAGS) -o $@ $^
	$(SIZE) $@

$(MAIN): $(ELF)
	$(OCOPY) $< -O binary $@

clean:
#   OS dependent. Change accordingly
#	del /Q /F $(MAIN) $(ELF) $(OBJS)
#	rm -f $(MAIN) $(ELF) $(OBJS)

run: $(MAIN)