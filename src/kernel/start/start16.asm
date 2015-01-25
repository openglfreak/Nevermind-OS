[global start16]

[extern start32]

[section .text]
[bits 16]
start16:
.init_stack:
mov ax,(stack_end>>0x04)
mov ss,ax
mov esp,(stack_end&0x0F)
.enable_a20:
call enable_a20
.get_biosinfos:
call fill_info_area
.get_memorymap:
call detect_memory
.copy_gdt:
push dword (gdt_template_end-gdt_template)
push dword gdt_start
push dword gdt_template
call copy_memory
sub esp,0x0C
push dword (gdt_end-gdt_start-(gdt_template_end-gdt_template))
push dword (gdt_start+(gdt_template_end-gdt_template))
call zero_memory
sub esp,0x08
mov word [gdtr],(gdt_template_end-gdt_template)
lgdt [gdtr]
.zero_idt:
push dword (idt_end-idt_start)
push dword idt_start
call zero_memory
sub esp,0x08
.init_idt:
mov word [idtr],0x00
lidt [idtr]
.disable_nmi:
in al,0x70
or al,0x80
out 0x70,al
.switch_protected_mode:
mov eax,cr0
or al,0x01
mov cr0,eax
.enable_nmi:
in al,0x70
and al,0x7F
out 0x70,al
.jump:
jmp codesegment:protected_mode
.end:
jmp $

[bits 32]
protected_mode:
.init_stack:
mov ax,datasegment
mov ds,ax
mov es,ax
mov fs,ax
mov gs,ax
mov ss,ax
mov esp,stack_end
.switch_pse:
mov eax,cr4
or al,0x10
mov cr4,eax
.jump:
call start32
jmp $

;variables

gdtr:
dw (gdt_end-gdt_start)
dd gdt_start

idtr:
dw (idt_end-idt_start)
dd idt_start

;constants

%include "../../memconsts/memconsts.asm"

;functions:

[bits 16]

enable_a20:
.save_registers:
push ax
push bx
.bios:
mov ax,0x2401
int 0x15
jnc .restore_registers
.keyb:
call .wait1
mov al,0xD0
out 0x64,al
call .wait2
in al,0x60
or al,0x02
mov bl,al
call .wait1
mov al,0xD1
out 0x64,al
call .wait1
mov al,bl
out 0x60,al
call .wait2
mov al,0xD0
out 0x64,al
call .wait1
in al,0x60
and al,0x02
jnz .restore_registers
.syscporta:
in al,0x92
or al,0x02
out 0x92,al
.restore_registers:
pop bx
pop ax
ret
.wait1:
in al,0x64
test al,0x02
jnz .wait1
ret
.wait2:
in al,0x64
test al,0x01
jz .wait2
ret

fill_info_area:
.save_registers:
push eax
.copycombases:
mov word ax,[0x0400]
mov word [infoarea_start],ax
mov word ax,[0x0402]
mov word [infoarea_start+0x02],ax
mov word ax,[0x0404]
mov word [infoarea_start+0x04],ax
mov word ax,[0x0406]
mov word [infoarea_start+0x06],ax
.fillebdastart:
mov word ax,[0x040E]
mov word [infoarea_start+0x08],ax
.restore_registers:
pop eax
ret

detect_memory:
.save_registers:
push eax
push ebx
push ecx
push edx
push si
push di
.clear_memmap:
mov ecx,(memmap_end-memmap_start)
.clear_memmap_loop:
sub ecx,0x04
mov dword [memmap_start+ecx],0x00
jnz .clear_memmap_loop
.init_loop:
mov si,memmap_start
xor di,di
mov es,di
mov di,infoarea_start+0x10
mov edx,0x534D4150
xor ebx,ebx
.int_15_E820_loop:
mov dword [infoarea_start+0x24],0x01
mov eax,0xE820
mov ecx,0x18
int 0x15
.check_validity:
jc .restore_registers
cmp eax,0x534D4150
jne .restore_registers
jcxz .testebx
mov dword ecx,[infoarea_start+0x1C]
test ecx,ecx
jnz .check_acpi30attrs
mov dword ecx,[infoarea_start+0x18]
jecxz .testebx
.check_acpi30attrs:
mov dword ecx,[infoarea_start+0x24]
and ecx,0x01
jcxz .testebx

.copy_entry_data:
mov dword ecx,[infoarea_start+0x10]
mov dword [si],ecx
mov dword ecx,[infoarea_start+0x14]
mov dword [si+0x04],ecx

mov dword ecx,[infoarea_start+0x18]
mov dword [si+0x08],ecx
mov dword ecx,[infoarea_start+0x1C]
mov dword [si+0x0C],ecx

mov dword ecx,[infoarea_start+0x20]
mov dword [si+0x10],ecx

mov dword [si+0x14],0x00

add si,0x18
.testebx:
test ebx,ebx
jnz .int_15_E820_loop
.restore_registers:
pop eax
pop ebx
pop ecx
pop edx
pop si
pop di
ret

zero_memory:
push ebp
mov ebp,esp
.save_registers:
push ecx
push edi
.get_params:
mov dword edi,[ebp+0x06]
mov dword ecx,[ebp+0x0A]
.check_size:
jecxz .restore_registers
.zero_loop:
mov byte [edi],0x00
inc edi
loop .zero_loop
.restore_registers:
pop edi
pop ecx
pop ebp
ret

copy_memory:
push ebp
mov ebp,esp
.save_registers:
push bx
push ecx
push esi
push edi
.get_params:
mov dword esi,[ebp+0x06]
mov dword edi,[ebp+0x0A]
mov dword ecx,[ebp+0x0E]
.check_size:
jecxz .restore_registers
.copy_loop:
mov byte bl,[esi]
mov byte [edi],bl
inc esi
inc edi
loop .copy_loop
.restore_registers:
pop edi
pop esi
pop ecx
pop bx
pop ebp
ret

replicate_memory:
push ebp
mov ebp,esp
.save_registers:
push bx
push ecx
push edx
push esi
push edi
.get_params:
mov dword edi,[ebp+0x0A]
mov dword ecx,[ebp+0x0E]
mov dword edx,[ebp+0x12]
.check_size_and_count:
jecxz .restore_registers
test edx,edx
jz .restore_registers
.replicate_loop:
mov dword esi,[ebp+0x06]
.copy_loop:
mov byte bl,[esi]
mov byte [edi],bl
inc esi
inc edi
loop .copy_loop
dec edx
jnz .replicate_loop
.restore_registers:
pop edi
pop esi
pop ecx
pop bx
pop ebp
ret

;datas

gdt_template:
nullsegment equ 0x00
dq 0x0000000000000000

codesegment equ ($-gdt_template)
dw 0xFFFF
dw 0x0000
db 0x00
db 0x9A
db 0xCF
db 0x00

datasegment equ ($-gdt_template)
dw 0xFFFF
dw 0x0000
db 0x00
db 0x92
db 0xCF
db 0x00
gdt_template_end:
