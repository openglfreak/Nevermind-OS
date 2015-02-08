. ../compilefuncs.sh

rm -R -f obj
mkdir obj

compilenasm start/start16.asm
compilegcc start/start32.c
compilegcc interrupts/interrupts.c
compilenasm interrupts/interrupt_service_routines.asm
compilegcc interrupts/pic.c
compilegcc memory/manager/memory_manager.c
compilegcc memory/manager/physical_memory_manager.c
compilegcc memory/manager/virtual_memory_manager.c
