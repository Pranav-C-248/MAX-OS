.PHONY: all clean run dump

all: run

kernel.bin: kernel-entry.o kernel.o screen_driver.o interrupts.o idt.o isr.o keyboard.o shell.o port.o util.o time.o
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

kernel-entry.o: /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/assembly/kernel_entry.asm
	nasm $< -f elf -o $@

kernel.o: main/kernel.c 
	gcc -fno-pie -m32  -c $< -o $@

screen_driver.o: /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/screen_driver.c /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/screen_driver.h
	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

idt.o: /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/idt.c /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/idt.h
	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

isr.o: /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/isr.c /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/isr.h /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/idt.h
	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

util.o: /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/util.c /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/util.h
	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

port.o: /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/port.c /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/port.c
	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

time.o: /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/time.c /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/time.h
	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

shell.o : /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/shell.c /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/shell.h
	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

# memory.o: /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/memory.c /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/memory.h
# 	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

# tetris.o : main/tetris.c main/tetris.h
# 	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

keyboard.o: /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/keyboard.c /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/essentials/keyboard.h
	gcc -fno-pie -m32 -ffreestanding -c $< -o $@

interrupts.o: /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/assembly/interrupt.asm
	nasm $< -f elf -o $@

boot.bin: /mnt/d/Backup/azazel/Desktop/OS_DEV/MAX-OS/assembly/boot.asm
	nasm -f bin $< -o $@

final_raw_binary.bin: boot.bin kernel.bin
	cat $^ > $@

run: final_raw_binary.bin
	qemu-system-i386 -fda $<

clean:
	rm -f tetris.o boot.bin shell.o tetris.o kernel.bin final_raw_binary.bin kernel-entry.o kernel.o screen_driver.o idt.o isr.o keyboard.o interrupts.o util.o memory.o port.o time.o

dump: final_raw_binary.bin
	objdump -D -m i386 -b binary final_raw_binary.bin > dump.txt

kernel.elf: kernel-entry.o kernel.o screen_driver.o idt.o isr.o keyboard.o interrupts.o
	x86_64-elf-ld -m elf_i386 -o $@ -Ttext 0x1000 $^

debug: final_raw_binary.bin kernel.elf
	qemu-system-i386 -s -S -fda final_raw_binary.bin &
	i386-elf-gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"


