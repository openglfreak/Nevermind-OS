; DONT WRITE TO SUPERBLOCK!!!
[global loader]

[section .text]
[bits 16]
ext2loader:
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

read_root_inode:
mov eax,0x02
call read_inode_to_usable

find_start_file:
mov esi,start_file_name
mov edi,edx
add edi,usable_start
call find_file_in_inode
test eax,eax
jz error

read_start_file_inode:
call read_inode_to_usable

read_start_file:
mov bx,(start_file_start>>0x04)
mov es,bx
mov bx,(start_file_start&0x0F)
mov eax,0x01
call block2device
mov cl,al
read_start_file_loop:
mov dword eax,[usable_start+edx+0x28]
test eax,eax
jz jump
push cx
call block2device
pop cx
pusha
call read_sectors_lba
popa
push cx
call get_block_size
add bl,al
and bl,0x0F
shr eax,0x04
mov cx,es
add cx,ax
mov es,cx
pop cx
add edx,0x04
jmp read_start_file_loop
; TODO: support files larger than 12 blocks

jump:
mov byte dl,[bootdrive]
push end
push start_file_start
ret

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

%include "../startfile.part"

;constants

%include "../../memconsts/memconsts.asm"

;functions

return:
ret

popa_return:
popa
ret

%include "../read_sectors.part"

%include "../conversions.part"

;split
%include "../split.part"
;part 2

%include "superblock.part"

%include "blockgroups.part"

%include "find_file.part"

;size check
times 0x03FF-($-$$) db 0x00
