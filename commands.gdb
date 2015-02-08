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

define stepl
    tbreak +1
    continue
end

define stepld
    tbreak +1
    continue
    disassemble /r
end

define stepldc
    tbreak +1
    continue
    disassemble /r $pc,+0x01
end

define stepli
    tbreak +1
    continue
    info registers
end

define steplid
    tbreak +1
    continue
    info registers
    disassemble /r
end

define steplidc
    tbreak +1
    continue
    info registers
    disassemble /r $pc,+0x01
end

define _16
    set architecture i8086
end

define _32
    set architecture i386
end
