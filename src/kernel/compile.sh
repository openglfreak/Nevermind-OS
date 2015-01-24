. ../compilefuncs.sh

rm -R -f obj
mkdir obj

compilenasm start/start16.asm
compilegcc start/start32.c
ld -melf_i386 -o obj/start.o obj/start16.o obj/start32.o -Ttext 0xF000 -e 0xF000
