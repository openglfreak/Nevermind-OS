if [ -e obj ]
then
    rm -R obj
fi
mkdir obj

d="$(pwd)"

for f in $(find src -name compiledbg.sh)
do
    cd $d/${f%/*}
    outp="$(sh compiledbg.sh 2>&1)"
    status=$?
    if [ $status -ne 0 ]
    then
        echo "$f: $outp"
        exit $status
    fi
    cp -f -R obj/* $d/obj/
done

cd $d

echo "directory $(find src -type d -exec echo -n :{} ';')" > source_dirs.gdb
