. ../linkfuncs.sh

rm -R -f bin
mkdir bin

mv obj/ext2loader.o /tmp/ext2loader.o
merge obj/ext2loader.o /tmp/ext2loader.o $(find obj -type f -name \*.o | grep -v ext2loader.o | grep -v loader.o)
linkbinary 0x7C00 bin/ext2loader.bin obj/ext2loader.o
