cls

@nasm "16 bit\loader.asm" -o bin\loader

@gcc -w -s -Iinclude -fno-builtin -nostdinc -nostdlib -c "32 bit/main.c"

@ld -T script.ld -o kernel.bin main.o
@objcopy -O binary -R .note -R .comment -S kernel.bin bin/code

@"save to virtual disk.exe"
@clean.bat