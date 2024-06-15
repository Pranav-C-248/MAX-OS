.PHONY: all clean run

all: final_raw_binary.bin

kernel-entry.o: kernel_entry.asm
	nasm $< -f elf32 -o $@

kernel.o: kernel.c
	gcc -m32 -ffreestanding -nostdlib -nostdinc -c $< -o $@

kernel.tmp: kernel-entry.o kernel.o
	ld -m i386pe -o $@ -Ttext 0x1000 $^ 

kernel.bin: kernel.tmp
	objcopy -O binary -j .text  kernel.tmp kernel.bin

boot.bin: boot.asm
	nasm -f bin $< -o $@

final_raw_binary.bin: boot.bin kernel.bin
	type boot.bin  kernel.bin > $@

run: final_raw_binary.bin
	qemu-system-i386 -fda $<

clean:
	del boot.bin kernel.bin final_raw_binary.bin kernel-entry.o kernel.o kernel.tmp
