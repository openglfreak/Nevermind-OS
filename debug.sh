sh compiledbg.sh
status=$?
if [ $status -ne 0 ]
then
    exit $status
fi
sh linkdbg.sh
status=$?
if [ $status -ne 0 ]
then
    exit $status
fi
sh generatedisk.sh
status=$?
if [ $status -ne 0 ]
then
    exit $status
fi

nohup bochs -q 'gdbstub: enabled=1, port=1234, text_base=0, data_base=0, bss_base=0' > /dev/null 2>&1 &
gdb --quiet -x dbg.gdb
