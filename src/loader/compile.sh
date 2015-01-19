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

ld -melf_i386 -A i386 --oformat binary -o bin/loader.bin /tmp/loader.asm.o $(echo $files | grep -v loader.asm.o) -nostdlib -Ttext=0x7C00 -e 0x7C00 -s

rm $files
