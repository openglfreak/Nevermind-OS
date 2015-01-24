compilenasm() {
    d="$(pwd)"
    cd "${1%/*}"
    f="${1##*/}"
    nasm -f elf -o "$d/obj/${f%.*}.o" "$f"
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
    gcc -c -m32 -O3 -s -o "$d/obj/${f%.*}.o" "$f" -nostdinc
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
    nasm -f elf -F dwarf -g -o "$d/obj/${f%.*}.o" "$f"
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
    gcc -Wall -c -ggdb3 -gno-strict-dwarf -m32 -Og -o "$d/obj/${f%.*}.o" "$f" -nostdinc
    status=$?
    if [ $status -ne 0 ]
    then
        exit $status
    fi
    cd "$d"
}
