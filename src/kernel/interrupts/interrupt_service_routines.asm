[extern isr_handler_wrapper]
[global isr_table]
[global isr_table_end]
[global isr_attribute_table]
[global isr_attribute_table_end]

[bits 32]
[section .text]

isr_table:
%assign n 0
%rep 256
    align 0x08
    .isr%[n]:
    call isr_wrapper
    %assign n n+1
%endrep
isr_table_end:

isr_attribute_table:
times 48 db 0x8E
times (256-48) db 0xEE
isr_attribute_table_end:

isr_wrapper:
push dword esp
pushfd
pop dword [ss:.old_flags]
mov dword [ss:.old_eax],eax
push dword .old_eax
push dword .old_flags
call isr_handler_wrapper
add esp,eax
add esp,0x10
mov dword eax,[ss:.old_eax]
push dword [ss:.old_flags]
popfd
iret
.old_eax:
dd 0x00000000
.old_flags:
dd 0x00000000
