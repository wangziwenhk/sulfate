mkdir -p build

nasm boot/boot.asm -o build/boot.bin
nasm boot/loader.asm -o build/loader.bin

printf "1\nfd\n\nbuild/boot.img\nyes\n" | bximage
dd if=build/boot.bin of=build/boot.img bs=512 count=1 conv=notrunc

mount build/boot.img /media/ -t vfat -o loop
cp build/loader.bin /media/
sync
umount /media/