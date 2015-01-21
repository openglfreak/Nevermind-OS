d=$(pwd)

if [ -e bin ]
then
    rm -R bin
fi
mkdir bin
if [ -e obj ]
then
    rm -R obj
fi
mkdir obj

for f in $(find src -name compiledbg.sh)
do
    cd $d/${f%/*}
    dirs="$dirs:$d/${f%/*}"
    outp=$(sh compiledbg.sh 2>&1)
    status=$?
    if [ $status -ne 0 ]
    then
        echo "$f: $outp"
        exit $status
    fi
    cp -f -R bin/* $d/bin/
    cp -f -R obj/* $d/obj/
done

cd $d

sh generatedisk.sh

echo "directory $dirs" > source_dirs.gdb
