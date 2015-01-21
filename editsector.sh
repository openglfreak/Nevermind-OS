if [ "$1" = "" ]
then
    if [ -f sector.hex ]
    then
        vim -c ":call feedkeys('R')" sector.hex
    else
        echo "No sector specified"
        exit 1
    fi
else
    xxd -s $((512*$1)) -l 512 -u disk.img sector.hex
    cp sector.hex sector.hex.old
    vim -c ":call feedkeys('R')" sector.hex
fi
if [ "$(diff --brief sector.hex sector.hex.old)" != "" ]
then
    xxd -u -r sector.hex disk.img
fi
