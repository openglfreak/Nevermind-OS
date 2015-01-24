rm -R -f bin
mkdir bin
rm -R -f obj

for f in *.asm
do
    nasm -f elf -o /tmp/${f##*/}.o $f
    status=$?
    if [ $status -ne 0 ]
    then
        exit $status
    fi
    files="$files /tmp/${f##*/}.o"
done

ld -melf_i386 -A i386 --oformat binary -o bin/%OUT_FILENAME%.bin /tmp/%START_FILE%.o $(echo $files | grep -v %START_FILE%.o) -nostdlib -Ttext=%MEMORY_LOCATION% -e %ENTRY_POINT% -s

rm $files
