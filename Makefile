.PHONY: all clean run dump

all: run

kernel.bin: kernel-entry.o kernel.o util.o screen_driver.o interrupts.o idt.o isr.o shell.o keyboard.o port.o memory.o
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

kernel-entry.o: kernel_entry.asm
	nasm $< -f elf -o $@

kernel.o: kernel.c 
	gcc -fno-pie -m32  -c $< -o $@

screen_driver.o: screen_driver.c screen_driver.h
	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

idt.o: idt.c idt.h
	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

isr.o: isr.c isr.h idt.h
	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

util.o: util.c util.h
	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

port.o: port.c port.c
	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

memory.o: memory.c memory.h
	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

# time.o: time.c time.h
# 	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

shell.o : shell.c shell.h
	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

# tetris.o : tetris.c tetris.h
# 	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

keyboard.o: keyboard.c keyboard.h
	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

interrupts.o: interrupt.asm
	nasm $< -f elf -o $@

boot.bin: boot.asm
	nasm -f bin $< -o $@

final_raw_binary.bin: boot.bin kernel.bin
	cat $^ > $@

run: final_raw_binary.bin
	qemu-system-i386 -fda $<

clean:
	rm -f tetris.o boot.bin shell.o kernel.bin final_raw_binary.bin kernel-entry.o kernel.o screen_driver.o idt.o isr.o keyboard.o interrupts.o util.o

dump: final_raw_binary.bin
	objdump -D -m i386 -b binary final_raw_binary.bin > dump.txt

kernel.elf: kernel-entry.o kernel.o screen_driver.o idt.o isr.o keyboard.o interrupts.o
	x86_64-elf-ld -m elf_i386 -o $@ -Ttext 0x1000 $^

debug: final_raw_binary.bin kernel.elf
	qemu-system-i386 -s -S -fda final_raw_binary.bin &
	i386-elf-gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"


