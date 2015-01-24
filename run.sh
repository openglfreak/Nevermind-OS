sh compile.sh
status=$?
if [ $status -ne 0 ]
then
    exit $status
fi

bochs -q
