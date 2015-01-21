truncate --size $((1024*1024*2)) bin/disk.img
mkfs -t ext2 -F bin/disk.img -q

dd if=bin/loader.bin of=bin/disk.img conv=notrunc > /dev/null 2>&1

rm -R -f tempmount
mkdir tempmount

sudo mount -t ext2 -o loop bin/disk.img tempmount
sudo cp -f -R bin/* tempmount/
sync
sudo umount tempmount

rm -R tempmount

cp -f bin/disk.img disk.img
