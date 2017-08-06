spritesht
=========

A tiny C application and library for producing packed spritesheets.

Why?
----

Packed spritesheets can be very useful in game development, but there aren't
many ways of making them that are:

* Free
* Lightweight
* Cross platform
* Easy to incorporate into builds
* Reasonably simple to modify/extend

spritesht is hopefully all of those things!

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

???
