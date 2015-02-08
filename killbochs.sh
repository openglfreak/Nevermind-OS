for pid in $(pidof bochs)
do
    kill $pid
    if [ "$?" -eq "0" ]
    then
        echo "killed $pid"
    fi
done
