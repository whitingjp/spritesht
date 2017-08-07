spritesht
=========

A tiny C application and library for producing packed spritesheets.

![Output Example](http://jonathanwhiting.com/images/spritesht_sizzle.png)

Why?
----

Packed spritesheets can be very useful in game development, but there aren't
many ways of making them that are:

* Free
* Lightweight
* Cross platform
* Easy to incorporate into builds
* Reasonably simple to modify/extend

spritesht is hopefully all of those things :)

Limitations
-----------

* Only handles png input/output images
* Only supports csv and a custom binary data file as output
* Lacks many fancy features that other spritesheet packers have

Compilation
-----------

To build spritesht you will need:

* a C compiler
* make
* libpng
* zlib

If you have those things you will hopefully just be able to just run "make". It
will build into the directory build/out

(if you're using Visual Studio, or XCode, and so don't have make, you can
hopefully figure out how to build+link the two source files yourself)

Usage
-----

    ./spritesht --png packed.png --csv data.csv src/a/*.png src/b/*.png

Command line arguments:

* `--png file.png` _[required]_ the packed spritesheet image file
* `--csv file.csv` a csv file for sprite meta data
* `--dat file.dat` a spritesht format data file for sprite meta data
* `--max 4096` the max dimensions (max*max) for the spritesheet, default 4096
* `--margin 2` a pixel margin for every sprite, to avoid graphical glitches, default 2

Exit code is 0 if successful, 1 if failed for any reason (see stdout for reason).

To load sprites, you can either pass the csv file yourself, or if using a C
library is easy enough, use libspritesht's `spritesht_load_meta` to obtain a
`spritesht_spritesheet` data structure containing the same information.
