prepare:
	dd if=/dev/zero of=bin/floppy.img bs=512 count=2880

bootloader:
	nasm -f bin src/bootloader.asm -o bin/bootloader.bin
	dd if=bin/bootloader.bin of=bin/floppy.img bs=512 count=1 conv=notrunc

stdlib:
	bcc -ansi -c src/std_lib.c -o src/std_lib.o

shell:
	bcc -ansi -c src/shell.c -o src/shell.o

kernel:
	nasm -f as86 src/kernel.asm -o src/kernel-asm.o
	bcc -ansi -c src/kernel.c -o src/kernel.o

link:
	ld86 -o bin/kernel.bin -d src/kernel.o src/kernel-asm.o src/std_lib.o src/shell.o	
	dd if=bin/kernel.bin of=bin/floppy.img bs=512 seek=1 count=15 conv=notrunc

build: prepare bootloader stdlib shell kernel link

clean:
	rm -f src/*.o bin/*.bin bin/floppy.img