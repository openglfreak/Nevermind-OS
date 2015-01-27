ENTRY(start16)
TARGET(elf32-i386)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386)

INPUT(obj/start16.o)
INPUT(obj/start32.o)
INPUT(obj/memory_manager.o)
OUTPUT(obj/kernel.o)

SECTIONS
{
  . = 0xF000;
  .text . :
    {
      obj/start16.o(.text)
      obj/start32.o(.text)
      obj/memory_manager.o(.text)
    }
  .data . :
    {
      *(.data)
    }
}
