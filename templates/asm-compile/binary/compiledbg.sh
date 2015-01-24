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

ld -melf_i386 -A i386 --oformat elf32-i386 -o obj/%OUT_FILENAME%.o obj/%START_FILE%.o $(find obj -type f | grep -v %START_FILE%.o | grep -v %OUT_FILENAME%.o) -nostdlib -Ttext=%MEMORY_LOCATION% -e %ENTRY_POINT%
ld -melf_i386 -A i386 --oformat binary -o bin/%OUT_FILENAME%.bin obj/%OUT_FILENAME%.o -e %ENTRY_POINT%
