sh compile.sh
status=$?
if [ $status -ne 0 ]
then
    exit $status
fi
sh link.sh
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

bochs -q 'plugin_ctrl: speaker=0'
