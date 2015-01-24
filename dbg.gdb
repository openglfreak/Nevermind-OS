set logging redirect on
set logging file /dev/null
set logging on

set confirm off
target remote localhost:1234

python gdb.events.exited.connect(lambda x : gdb.execute("quit"))

define lasm
layout asm
layout regs
end

define lc
layout src
layout regs
end

define stepid
stepi
disassemble /r
end

define stepidc
stepi
disassemble /r $pc,+0x01
end

define stepii
stepi
info registers
end

define stepiid
stepi
info registers
disassemble /r
end

define stepiidc
stepi
info registers
disassemble /r $pc,+0x01
end

define _16
set architecture i8086
end

define _32
set architecture i386
end

set debug-file-directory $HOME/os/obj
source source_dirs.gdb
source symbol_files.gdb

set architecture i8086
set disassembly-flavor intel
set print asm-demangle

break *0x7C00
continue

set logging off
set logging redirect off
