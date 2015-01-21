d=$(pwd)

if [ -e bin ]
then
    rm -R bin
fi
mkdir bin

for f in $(find src -name compile.sh)
do
    cd $d/${f%/*}
    outp=$(sh compile.sh 2>&1)
    status=$?
    if [ $status -ne 0 ]
    then
        echo "$f: $outp"
        exit $status
    fi
    cp -f -R bin/* $d/bin/
done

cd $d
sh generatedisk.sh
