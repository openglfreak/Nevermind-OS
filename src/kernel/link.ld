ENTRY(start16)
TARGET(elf32-i386)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386)

INPUT(obj/start16.o)
INPUT(obj/start32.o)
INPUT(obj/interrupts.o)
INPUT(obj/interrupt_service_routines.o)
INPUT(obj/pic.o)
INPUT(obj/memory_manager.o)
INPUT(obj/physical_memory_manager.o)
INPUT(obj/virtual_memory_manager.o)
OUTPUT(obj/kernel.o)

SECTIONS
{
  . = 0xF000;
  .text . :
    {
      obj/start16.o(.text)
      *(EXCLUDE_FILE(*obj/start16.o) .text)
    }
  .data . :
    {
      *(.data)
    }
}
