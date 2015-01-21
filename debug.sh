sh compiledbg.sh
status=$?
if [ $status -ne 0 ]
then
    exit $status
fi

nohup bochs -q > /dev/null 2>&1 &
gdb --quiet -x debug.gdb
