. ../compilefuncs.sh

rm -R -f obj
mkdir obj

compilegccdbg ext2/loader.c -fno-toplevel-reorder -Os
shrink obj/loader_s.o obj/loader.o
relocate 0x7C00 obj/ext2loader.o obj/loader_s.o

rm obj/loader.o
