.PHONY: all clean run dump debug

# Define the cross-compiler tools
CC=x86_64-elf-gcc
LD=x86_64-elf-ld
AS=nasm

# Compiler and linker flags
CFLAGS=-m32 -ffreestanding -fno-pie -nostdlib
LDFLAGS=-Ttext 0x1000 --oformat binary

all: final_raw_binary.bin

kernel.bin: kernel-entry.o kernel.o screen_driver.o interrupts.o idt.o isr.o keyboard.o shell.o port.o util.o time.o tetris.o
	$(LD) -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

kernel-entry.o: /Users/manaskumar/Desktop/MAX-OS-P1/assembly/kernel_entry.asm
	$(AS) $< -f elf -o $@

kernel.o: /Users/manaskumar/Desktop/MAX-OS-P1/main/kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

screen_driver.o: /Users/manaskumar/Desktop/MAX-OS-P1/essentials/screen_driver.c /Users/manaskumar/Desktop/MAX-OS-P1/essentials/screen_driver.h
	$(CC) $(CFLAGS) -c $< -o $@

idt.o: /Users/manaskumar/Desktop/MAX-OS-P1/essentials/idt.c /Users/manaskumar/Desktop/MAX-OS-P1/essentials/idt.h
	$(CC) $(CFLAGS) -c $< -o $@

isr.o: /Users/manaskumar/Desktop/MAX-OS-P1/essentials/isr.c /Users/manaskumar/Desktop/MAX-OS-P1/essentials/isr.h /Users/manaskumar/Desktop/MAX-OS-P1/essentials/idt.h
	$(CC) $(CFLAGS) -c $< -o $@

util.o: /Users/manaskumar/Desktop/MAX-OS-P1/essentials/util.c /Users/manaskumar/Desktop/MAX-OS-P1/essentials/util.h
	$(CC) $(CFLAGS) -c $< -o $@

port.o: /Users/manaskumar/Desktop/MAX-OS-P1/essentials/port.c /Users/manaskumar/Desktop/MAX-OS-P1/essentials/port.h
	$(CC) $(CFLAGS) -c $< -o $@

time.o: /Users/manaskumar/Desktop/MAX-OS-P1/essentials/time.c /Users/manaskumar/Desktop/MAX-OS-P1/essentials/time.h
	$(CC) $(CFLAGS) -c $< -o $@

shell.o: /Users/manaskumar/Desktop/MAX-OS-P1/essentials/shell.c /Users/manaskumar/Desktop/MAX-OS-P1/essentials/shell.h
	$(CC) $(CFLAGS) -c $< -o $@

tetris.o: /Users/manaskumar/Desktop/MAX-OS-P1/main/tetris.c /Users/manaskumar/Desktop/MAX-OS-P1/main/tetris.h
	$(CC) $(CFLAGS) -c $< -o $@

keyboard.o: /Users/manaskumar/Desktop/MAX-OS-P1/essentials/keyboard.c /Users/manaskumar/Desktop/MAX-OS-P1/essentials/keyboard.h
	$(CC) $(CFLAGS) -c $< -o $@

interrupts.o: /Users/manaskumar/Desktop/MAX-OS-P1/assembly/interrupt.asm
	$(AS) $< -f elf -o $@

boot.bin: /Users/manaskumar/Desktop/MAX-OS-P1/assembly/boot.asm
	$(AS) -f bin $< -o $@

final_raw_binary.bin: boot.bin kernel.bin
	cat $^ > $@

run: final_raw_binary.bin
	qemu-system-i386 -fda $<

clean:
	rm -f boot.bin shell.o kernel.bin final_raw_binary.bin kernel-entry.o kernel.o screen_driver.o idt.o isr.o keyboard.o interrupts.o util.o port.o time.o tetris.o

dump: final_raw_binary.bin
	objdump -D -m i386 -b binary final_raw_binary.bin > dump.txt

kernel.elf: kernel-entry.o kernel.o screen_driver.o idt.o isr.o keyboard.o interrupts.o shell.o port.o util.o time.o tetris.o
	$(LD) -m elf_i386 -o $@ -Ttext 0x1000 $^

debug: final_raw_binary.bin kernel.elf
	qemu-system-i386 -s -S -fda final_raw_binary.bin &
	i386-elf-gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"
