. ../compilefuncs.sh

rm -R -f obj
mkdir obj

compilenasmdbg start/start16.asm
status=$?
if [ $status -ne 0 ]
then
    exit $status
fi
compilegccdbg start/start32.c
status=$?
if [ $status -ne 0 ]
then
    exit $status
fi

ld -melf_i386 -o obj/start.o obj/start16.o obj/start32.o -Ttext 0xF000 -e 0xF000
