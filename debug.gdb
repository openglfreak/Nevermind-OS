set confirm off
target remote localhost:1234

python gdb.events.exited.connect(lambda x : gdb.execute("quit"))

define stepid
stepi
disassemble /r
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

define _16
set architecture i8086
end

define _32
set architecture i386
end

set debug-file-directory $HOME/os/obj
source source_dirs.gdb
add-symbol-file obj/loader.o 0x7C00

set architecture i8086
set disassembly-flavor intel

break loader
continue
#continue
