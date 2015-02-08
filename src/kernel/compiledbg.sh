. ../compilefuncs.sh

rm -R -f obj
mkdir obj

compilenasmdbg start/start16.asm
compilegccdbg start/start32.c
compilegccdbg interrupts/interrupts.c
compilenasmdbg interrupts/interrupt_service_routines.asm
compilegccdbg interrupts/pic.c
compilegccdbg memory/manager/memory_manager.c
compilegccdbg memory/manager/physical_memory_manager.c
compilegccdbg memory/manager/virtual_memory_manager.c
