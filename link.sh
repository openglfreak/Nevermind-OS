if [ -e bin ]
then
    rm -R bin
fi
mkdir bin

d="$(pwd)"

for f in $(find src -name link.sh)
do
    cd $d/${f%/*}
    outp="$(sh link.sh 2>&1)"
    status=$?
    if [ $status -ne 0 ]
    then
        echo "$f: $outp"
        exit $status
    fi
    cp -f -R obj/* $d/obj/
    cp -f -R bin/* $d/bin/
done

cd $d
