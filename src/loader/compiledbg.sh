rm -R -f bin
mkdir bin
rm -R -f obj
mkdir obj

for f in *.asm
do
    nasm -f elf -F dwarf -g -o obj/${f##*/}.o $f
    status=$?
    if [ $status -ne 0 ]
    then
        exit $status
    fi
done

ld -melf_i386 -A i386 --oformat elf32-i386 -o obj/loader.o obj/loader.asm.o $(find obj -type f | grep -v loader.asm.o | grep -v loader.o) -nostdlib -Ttext=0x7C00 -e 0x7C00
ld -melf_i386 -A i386 --oformat binary -o bin/loader.bin obj/loader.o -e 0x7C00
