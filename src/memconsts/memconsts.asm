%define stack_start 0x7B00
%define stack_end 0x7BF0

%define bootcylinders 0x7BFB
%define bootheads 0x7BFD
%define bootsectors 0x7BFE
%define bootdrive 0x7BFF

%define hmemmap_start 0x7E00
%define hmemmap_end 0x8000

%define gdt_start 0x8000
%define gdt_end 0xA000

%define idt_start 0xA000
%define idt_end 0xA800

%define infoarea_start 0xA800
%define infoarea_end 0xB000

%define usable_start 0xB000
%define usable_end 0xF000

%define start_file_start 0xF000
%define start_file_end 0x12000

%define cpuid_signature 0x1F000
%define cpuid_features0 0x1F004
%define cpuid_features1 0x1F008
%define cpuid_features 0x1F004
%define cpuid_additional_features 0x1F00C

%define pdir_start 0x20000
%define pdir_end 0x21000
%define ptable0_start 0x21000
%define ptable0_end 0x22000

%define physical_memory_usage_map_start 0x22000
%define physical_memory_usage_map_end 0x23000
%define physical_memory_usage_page0_start 0x23000
%define physical_memory_usage_page0_end 0x24000

%define video_buffer_start 0xB8000
