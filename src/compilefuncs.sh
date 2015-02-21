compilenasm() {
    d="$(pwd)"
    cd "${1%/*}"
    f="${1##*/}"
    shift
    nasm -f elf -o "$d/obj/${f%.*}.o" "$f" $*
    status=$?
    if [ $status -ne 0 ]
    then
        exit $status
    fi
    cd "$d"
}

compilegcc() {
    d="$(pwd)"
    cd "${1%/*}"
    f="${1##*/}"
    shift
    gcc -c -m32 -O3 -s -o "$d/obj/${f%.*}.o" "$f" -nostdlib -fno-stack-protector -fomit-frame-pointer -fno-exceptions $*
    status=$?
    if [ $status -ne 0 ]
    then
        exit $status
    fi
    cd "$d"
}

compilenasmdbg() {
    d="$(pwd)"
    cd "${1%/*}"
    f="${1##*/}"
    shift
    nasm -f elf -F dwarf -g -o "$d/obj/${f%.*}.o" "$f" $*
    status=$?
    if [ $status -ne 0 ]
    then
        exit $status
    fi
    cd "$d"
}

compilegccdbg() {
    d="$(pwd)"
    cd "${1%/*}"
    f="${1##*/}"
    shift
    gcc -Wall -c -ggdb3 -gno-strict-dwarf -m32 -Og -o "$d/obj/${f%.*}.o" "$f" -nostdlib -fno-stack-protector $*
    status=$?
    if [ $status -ne 0 ]
    then
        exit $status
    fi
    cd "$d"
}
