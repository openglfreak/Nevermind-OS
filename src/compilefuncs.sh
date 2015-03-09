stdincname="stddefs.h"

inverse_search() {
    local d="$(pwd)"
    while [ "$(pwd)" != "/" ]
    do
        if [ "$(find . -maxdepth 1 -type f -name $1)" != "" ]
        then
            echo $(pwd)
            cd "$d"
            return 0
        fi
        cd ..
    done
    cd "$d"
    return 1
}

getstdinc() {
    if [ "$stdincrel" == "$(pwd)" ] && [ -f "$stdinc" ]
    then
        echo "$stdinc"
    else
        stdincrel="$(pwd)"
        stdinc="$(inverse_search $stdincname)/$stdincname"
        echo $stdinc
    fi
}

compilenasm() {
    local d="$(pwd)"
    cd "${1%/*}"
    local f="${1##*/}"
    shift
    nasm $* -f elf -o "$d/obj/${f%.*}.o" "$f"
    local status=$?
    if [ $status -ne 0 ]
    then
        exit $status
    fi
    cd "$d"
}

compilegcc() {
    local d="$(pwd)"
    cd "${1%/*}"
    local f="${1##*/}"
    shift
    local inc="$(getstdinc)"
    if [ "$inc" != "" ]
    then
        inc="-include $inc"
    fi
    gcc -c -m32 -O3 -s -o "$d/obj/${f%.*}.o" "$f" $inc -nostdlib -fno-stack-protector -fomit-frame-pointer -fno-exceptions -fno-asynchronous-unwind-tables $*
    local status=$?
    if [ $status -ne 0 ]
    then
        exit $status
    fi
    cd "$d"
}

compilenasmdbg() {
    local d="$(pwd)"
    cd "${1%/*}"
    local f="${1##*/}"
    shift
    nasm $* -f elf -F dwarf -g -o "$d/obj/${f%.*}.o" "$f"
    local status=$?
    if [ $status -ne 0 ]
    then
        exit $status
    fi
    cd "$d"
}

compilegccdbg() {
    local d="$(pwd)"
    cd "${1%/*}"
    local f="${1##*/}"
    shift
    local inc="$(getstdinc)"
    if [ "$inc" != "" ]
    then
        inc="-include $inc"
    fi
    gcc -Wall -c -ggdb3 -gno-strict-dwarf -m32 -Og -o "$d/obj/${f%.*}.o" "$f" $inc -nostdlib -fno-stack-protector -fno-asynchronous-unwind-tables $*
    local status=$?
    if [ $status -ne 0 ]
    then
        exit $status
    fi
    cd "$d"
}
