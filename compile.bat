cls

@nasm "16 bit\loader.asm" -o bin\loader

@gcc -w -s -Iinclude -fno-builtin -nostdinc -nostdlib -c "32 bit/main.c"

REM @gcc -s -Iinclude -fno-builtin -nostdinc -nostdlib -c "32 bit/main.c" "32 bit/stream.c" "32 bit/display output.c" "32 bit/memory manager/allocator.c" "32 bit/drivers/ports.c" "32 bit/drivers/keyboard/input stream.c"
REM gcc -s -Iinclude -fno-builtin -nostdinc -nostdlib -c "32 bit/drivers/sound blaster 16/output stream.c" -o a.o

REM @tcc -w -fno-builtin -nostdinc -nostdlib -c "32 bit/main.c" -o main.o

@ld -T script.ld -o kernel.bin main.o
@objcopy -O binary -R .note -R .comment -S kernel.bin bin/code

@"save to virtual disk.exe"
@clean.bat