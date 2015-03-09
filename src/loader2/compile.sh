. ../compilefuncs.sh

rm -R -f obj
mkdir obj

compilegcc ext2/loader.c -fno-toplevel-reorder -Os
ld -r -melf_i386 -o obj/ext2loader.o obj/loader.o -Ttext 0x7C00 -e 0x7C00 --strip-all

rm obj/loader.o
