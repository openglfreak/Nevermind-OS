rm -R -f bin
mkdir bin

ld -T link.ld
ld -melf_i386 --oformat binary -o bin/kernel.bin obj/kernel.o
