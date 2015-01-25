stack_start equ 0x7B00
stack_end equ 0x7BF0

bootcylinders equ 0x7BFB
bootheads equ 0x7BFD
bootsectors equ 0x7BFE
bootdrive equ 0x7BFF

gdt_start equ 0x8000
gdt_end equ 0xA000

idt_start equ 0xA000
idt_end equ 0xA800

infoarea_start equ 0xA800
infoarea_end equ 0xB000

pdir_start equ 0xB000
pdir_end equ 0xC000
ptable0_start equ 0xC000
ptable0_end equ 0xD000

memmap_start equ 0xD000
memmap_end equ 0xE000

superblock_start equ 0xE000
superblock_end equ 0xE400

root_bgd_start equ 0xE400
root_bgd_end equ 0xE600

usable_start equ 0xE600
usable_end equ 0xF000

start_file_start equ 0xF000
start_file_end equ 0x10000
