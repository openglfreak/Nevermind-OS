if [ -e obj ]
then
    rm -R obj
fi
mkdir obj

d="$(pwd)"

for f in $(find src -name compile.sh)
do
    cd $d/${f%/*}
    outp="$(sh compile.sh 2>&1)"
    status=$?
    if [ $status -ne 0 ]
    then
        echo "$f: $outp"
        exit $status
    fi
done

cd $d
