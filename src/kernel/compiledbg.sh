. ../compilefuncs.sh

rm -R -f obj
mkdir obj

compilenasmdbg start/start16.asm
status=$?
if [ $status -ne 0 ]
then
    exit $status
fi
compilegccdbg start/start32.c
status=$?
if [ $status -ne 0 ]
then
    exit $status
fi
compilegccdbg memory/manager/memory_manager.c
status=$?
if [ $status -ne 0 ]
then
    exit $status
fi
