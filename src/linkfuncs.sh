merge() {
    ld -r -melf_i386 -A i386 --oformat elf32-i386 -o $* -nostdlib
    status=$?
    if [ $status -ne 0 ]
    then
        exit $status
    fi
}

relocate() {
    entry=$1
    shift
    ld -melf_i386 -A i386 --oformat elf32-i386 -o $* -nostdlib -Ttext=$entry -e $entry
    status=$?
    if [ $status -ne 0 ]
    then
        exit $status
    fi
}

shrink() {
    ld -melf_i386 -A i386 --oformat elf32-i386 -o $* -nostdlib --gc-sections --strip-all
    status=$?
    if [ $status -ne 0 ]
    then
        exit $status
    fi
}

linkbinary() {
    entry=$1
    shift
    ld -melf_i386 -A i386 --oformat binary -o $* -nostdlib -Ttext=$entry -e $entry
    status=$?
    if [ $status -ne 0 ]
    then
        exit $status
    fi
}
