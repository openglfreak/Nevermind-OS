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
        cd $d
        echo "$f: $outp"
        exit $status
    fi
done

cd $d

mkdir -p debug
echo "directory $(find src -type d -exec echo -n :{} ';')" > debug/source_dirs.gdb
