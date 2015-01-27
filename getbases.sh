for f in $(find obj -type f -name *.o)
do
    base=$(objdump -f $f | tail -n 2 | head -n 1)
    base=${base##* }
    if [ $? = 0 ]
    then
        if [ "$((base))" -ne 0 ]
        then
            bases="$bases
add-symbol-file \"$f\" $base"
        fi
    fi
done

echo "$bases" > symbol_files.gdb
