mv obj/ext2loader.o /tmp/ext2loader.o
ld -melf_i386 -A i386 --oformat elf32-i386 -o obj/ext2loader.o /tmp/ext2loader.o $(find obj -type f | grep -v ext2loader.o | grep -v loader.o) -nostdlib -Ttext=0x7C00 -e 0x7C00
ld -melf_i386 -A i386 --oformat binary -o bin/ext2loader.bin obj/ext2loader.o
