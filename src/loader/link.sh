mv obj/ext2loader.o /tmp/ext2loader.o
ld -melf_i386 -A i386 --oformat binary -o bin/ext2loader.bin /tmp/ext2loader.o $(echo $files | grep -v loader.asm.o) -nostdlib -Ttext=0x7C00 -e 0x7C00 -s
