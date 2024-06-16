.PHONY: all clean run dump

all: run

kernel.bin: kernel-entry.o kernel.o
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

kernel-entry.o: kernel_entry.asm
	nasm $< -f elf -o $@

kernel.o: kernel.c
	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

boot.bin: boot.asm
	nasm -f bin $< -o $@

final_raw_binary.bin: boot.bin kernel.bin
	cat $^ > $@

run: final_raw_binary.bin
	qemu-system-i386  -fda  $<

clean:
	rm boot.bin kernel.bin final_raw_binary.bin kernel-entry.o kernel.o 
dump:final_raw_binary.bin
	objdump -D -m i386 -b binary final_raw_binary.bin > dump.txt