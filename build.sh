#/usr/bin/bash
set -e
mkdir -p build/obj
mkdir -p build/out
gcc -c -o build/obj/spritesht_lib.o src/spritesht_lib.c
gcc -c -o build/obj/spritesht.o src/spritesht.c
gcc -o build/out/spritesht build/obj/spritesht_lib.o build/obj/spritesht.o
