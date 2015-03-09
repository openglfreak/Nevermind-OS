target remote localhost:1234
break *0x7C00
continue
set architecture i8086
set disassembly-flavor intel
add-symbol-file obj/ext2loader.o 0x7C00

define stepid
    stepi
    disassemble
end

define stepidl
    stepi
    disassemble $eip,+0x01
end
