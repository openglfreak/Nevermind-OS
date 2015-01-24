ENTRY(start16)
TARGET(elf32-i386)
OUTPUT_FORMAT(binary)
OUTPUT_ARCH(i386)

INPUT(obj/start16.o)
INPUT(obj/start32.o)
OUTPUT(bin/kernel.bin)

SECTIONS
{
  . = 0xF000;
  .text . :
    {
      obj/start16.o(.text)
      obj/start32.o(.text)
    }
  .data . :
    {
      obj/start16.o(.data)
      obj/start32.o(.data)
    }
}
