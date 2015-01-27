%define stack_start 0x7B00
%define stack_end 0x7BF0

%define bootcylinders 0x7BFB
%define bootheads 0x7BFD
%define bootsectors 0x7BFE
%define bootdrive 0x7BFF

%define memmap_start 0x7E00
%define memmap_end 0x8000

%define gdt_start 0x8000
%define gdt_end 0xA000

%define idt_start 0xA000
%define idt_end 0xA800

%define infoarea_start 0xA800
%define infoarea_end 0xB000

%define usable_start 0xB000
%define usable_end 0xD000

%define pdir_start 0xD000
%define pdir_end 0xE000
%define ptable0_start 0xE000
%define ptable0_end 0xF000

%define start_file_start 0xF000
%define start_file_end 0x10000
