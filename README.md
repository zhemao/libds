# libds - Data Structures in C

This is a collection of C implementations of common data structures.
I implemented these as an exercise when I was first learning C.
I have no interest in maintaining this library. **Use this code at your own peril.**

The library includes implementations of the following data structures.

 * Hashmap
 * Vector (auto-expanding array)
 * Linked List
 * String Buffer (auto-expanding, length-recording string)

## Installation Instructions:

Running make with no arguments will generate a shared library named libds.a.
You can then copy that library, as well as all header files, into your 
project directory. If you do not wish to use separate header files, you may 
generate a single header file called ds.h by running make ds.h.

You can link your applications to the static library like so. 

    gcc -static main.c -L. -lds -o main

Assuming that main.c is your program and libds.a has been copied into the 
same directory.

Documentation on how to use the various functions and datastructures can be 
found in the header files.

License:

libds is distributed under the MIT License, the full text of which is 
reproduced in LICENSE.
