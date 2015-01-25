. ../compilefuncs.sh

rm -R -f bin
mkdir bin
rm -R -f obj
mkdir obj

compilenasm ext2/ext2loader.asm
mv obj/ext2loader.o /tmp/ext2loader.o
ld -melf_i386 -o obj/ext2loader.o /tmp/ext2loader.o -Ttext 0x7C00 -e 0x7C00 --strip-all
