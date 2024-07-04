.PHONY: all clean run dump

# Define the cross-compiler tools
CC=x86_64-elf-gcc
LD=x86_64-elf-ld
AS=nasm

# Compiler and linker flags
CFLAGS=-m32 -ffreestanding -fno-pie -nostdlib
LDFLAGS=-Ttext 0x1000 --oformat binary

all: final_raw_binary.bin

kernel.bin: kernel-entry.o kernel.o screen_driver.o file_system.o string.o
	$(LD) -m elf_i386 -o $@ $(LDFLAGS) $^

kernel-entry.o: kernel_entry.asm
	$(AS) -f elf32 $< -o $@

kernel.o: kernel.c screen_driver.h file_system.h string.h
	$(CC) $(CFLAGS) -c $< -o $@

screen_driver.o: screen_driver.c screen_driver.h
	$(CC) $(CFLAGS) -c $< -o $@

file_system.o: file_system.c file_system.h string.h
	$(CC) $(CFLAGS) -c $< -o $@

string.o: string.c string.h
	$(CC) $(CFLAGS) -c $< -o $@

boot.bin: boot.asm
	$(AS) -f bin $< -o $@

final_raw_binary.bin: boot.bin kernel.bin
	cat $^ > $@

run: final_raw_binary.bin
	qemu-system-i386 -fda $<

clean:
	rm -f boot.bin kernel.bin final_raw_binary.bin kernel-entry.o kernel.o screen_driver.o file_system.o string.o

dump: final_raw_binary.bin
	objdump -D -m i386 -b binary $< > dump.txt
