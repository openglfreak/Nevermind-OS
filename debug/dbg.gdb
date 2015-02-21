set logging redirect on
set logging file /dev/null
set logging on

set confirm off
target remote localhost:1234

python gdb.events.exited.connect(lambda x : gdb.execute("quit"))

source debug/commands.gdb

set debug-file-directory obj
source debug/source_dirs.gdb
source debug/symbol_files.gdb

set disassembly-flavor intel
set print asm-demangle

break *0x7C00
commands
    silent
    _16
end
continue

break protected_mode
commands
    silent
    _32
    continue
end

set logging off
set logging redirect off
