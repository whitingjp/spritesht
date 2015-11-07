#/usr/bin/bash
set -e
mkdir -p build/obj
mkdir -p build/out
gcc -g -c -Iinput/libpng -Iinc -o build/obj/spritesht_lib.o src/spritesht_lib.c
gcc -g -c -Iinc -o build/obj/spritesht.o src/spritesht.c
gcc -g -c -Iinc -o build/obj/fakesht.o src/fakesht.c
gcc -g -Linput/libpng -Linput/zlib -lpng -lz -o build/out/spritesht build/obj/spritesht_lib.o build/obj/spritesht.o
gcc -g -Linput/libpng -Linput/zlib -lpng -lz -o build/out/fakesht build/obj/spritesht_lib.o build/obj/fakesht.o
