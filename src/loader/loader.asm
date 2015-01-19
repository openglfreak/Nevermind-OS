[global loader]

[section .text]
[bits 16]
loader:
cli
mov byte [bootdrive],dl

init_segments:
xor ax,ax
mov ds,ax
mov ss,ax
mov esp,stack_end

init_disk:
xor ah,ah
int 0x13
jc error

get_drive_params:
mov ah,0x08
int 0x13
jc error
mov bl,cl
and bl,0x3F
mov byte [bootsectors],bl
inc dh
mov byte [bootheads],dh
mov bl,ch
mov bh,cl
shr bh,0x06
inc bx
mov word [bootcylinders],bx

read_second_half:
mov ah,0x02
mov al,0x01
xor ch,ch
mov cl,0x02
xor dh,dh
mov byte dl,[bootdrive]
mov bx,0x7E0
mov es,bx
xor bx,bx
int 0x13
jc error

read_superblock:
mov al,0x02
xor ch,ch
mov cl,0x03
xor dh,dh
mov bx,(superblock_start>>0x04)
mov es,bx
mov bx,(superblock_start&0x0F)
call read_sectors

check_ext2_existence:
mov word ax,[superblock_start+0x38]
cmp ax,0xEF53
jnz error
check_ext2_errors:
mov word ax,[superblock_start+0x3A]
cmp ax,0x01
jz no_ext2_errors
mov word ax,[superblock_start+0x3C]
cmp ax,0x03
jz error
no_ext2_errors:

calc_blockgroup_descriptor_device_block:
mov dword ecx,[superblock_start+0x18]
test cl,cl
jnz calc_blockgroup_descriptor_device_block2
inc cl

calc_blockgroup_descriptor_device_block2:
mov eax,0x02
shl eax,cl

read_blockgroup_descriptor:
mov cl,0x01
call read_sectors_to_usable_lba

calc_inode_table_device_block:
mov dword ecx,[superblock_start+0x18]
mov dword eax,[usable_start+0x08]
inc cl
shl eax,cl
push eax

calc_block_offset:
call get_inode_size
push eax
mov dword ecx,[superblock_start+0x18]
add cl,0x0A
mov ebx,0x0400
shl ebx,cl
xor edx,edx
div ebx

calc_inode_table_device_block2:
pop ecx
shr ecx,0x09
inc cl
mov ebx,eax
pop eax
add eax,ebx
push edx

read_inode_table_block:
call read_sectors_to_usable_lba

find_start_file:
mov esi,start_file_name
pop edi
add edi,usable_start
call find_file_in_inode

end:
jmp halt

error:
mov si,error_str
mov ecx,0xB8000
print_errmessage_loop:
mov byte bl,[si]
test bl,bl
jz halt
mov byte [ecx],bl
mov byte [ecx+0x01],0x07
add ecx,0x02
inc si
jmp print_errmessage_loop

halt:
cli
hlt
jmp $

;variables

error_str: db "ERROR",0x00
;start_file_name: db "start16.bin",0x00
start_file_name: db "loader.bin",0x00

;constants

%include "../memory/memconsts/memconsts.asm"

;split

jmp second_half
times 0x1FE-($-$$) db 0
db 0x55
db 0xAA
second_half:

;functions:

return:
ret

popa_return:
ret

read_sectors_to_usable_lba:
xor ch,ch
push cx
xor bh,bh
mov byte bl,[bootsectors]
push bx
mov byte bl,[bootheads]
push bx
push eax
call lbs2chs
call chs2int13h
pop ax

read_sectors_to_usable:
mov bx,(usable_start>>0x04)
mov es,bx
mov bx,(usable_start&0x0F)
jmp read_sectors

read_sectors_lba:
push bx
xor ch,ch
push cx
xor bh,bh
mov byte bl,[bootsectors]
push bx
mov byte bl,[bootheads]
push bx
push eax
call lbs2chs
call chs2int13h
pop ax
pop bx

read_sectors:
mov ah,0x02
mov byte dl,[bootdrive]
int 0x13
jc error
ret

get_inode_size:
mov eax,0x80
mov word cx,[superblock_start+0x4C]
test cx,cx
jz return
mov word ax,[superblock_start+0x58]
ret

getchscount:
mov ah,0x08
int 0x13
jc return
mov bl,cl
and bl,0x3F
mov al,ch
mov ah,cl
shr ah,0x06
inc ax
inc dh
ret

lbs2chs:
mov ebp,esp
add ebp,0x02
mov word cx,[ebp+0x06]
mov word ax,[ebp+0x04]
mul cl
xor ecx,ecx
mov cx,ax
xor edx,edx
mov dword eax,[ebp]
div ecx
push eax
xor edx,edx
mov dword eax,[ebp]
xor ecx,ecx
mov word cx,[ebp+0x06]
div ecx
inc edx
push edx
xor ecx,ecx
mov word cx,[ebp+0x04]
xor edx,edx
div ecx
pop eax
pop ecx
ret 0x08

chs2int13h:
mov dh,cl
shr cx,0x02
and cl,0xC0
or cl,al
mov ch,dh
mov dh,dl
ret

%include "find_file.part"
