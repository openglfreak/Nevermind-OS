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

bochs -q 'gdbstub: enabled=1, port=1234, text_base=0, data_base=0, bss_base=0' 'plugin_ctrl: speaker=0' 'debug: action=ignore' 'info: action=ignore' 'error: action=fatal' 'panic: action=fatal' &
bochs_pid=$!
gdb --quiet -x debug/dbg.gdb
kill $bochs_pid > /dev/null 2>&1
