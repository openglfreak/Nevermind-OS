rm -f dbgfs
cd bin

for d in $(find . -type d | cut -c3-)
do
    if [ "$d" != "" ]
    then
        dbgfs="$dbgfs
mkdir \"$d\""
    fi
done

for f in $(find . -type f | cut -c3-)
do
    dbgfs="$dbgfs
write \"bin/$f\" \"$f\""
done

dbgfs="$dbgfs
close"

cd ..

truncate --size $((1024*1024*2)) bin/disk.img
mkfs -t ext2 -F bin/disk.img -q

dd if=bin/ext2loader.bin of=bin/disk.img conv=notrunc > /dev/null 2>&1
echo "$dbgfs" | debugfs -w bin/disk.img > /dev/null 2>&1

cp -f bin/disk.img disk.img
