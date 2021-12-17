# NewKern

A 64-bit, higher half kernel I'm making to learn OS dev.

## Features

Right now not so many:

- runtime undefined behavior checking
- higher half (-2GB) 64 bit kernel
- multiboot 1 compliant
- stivale 2 compliant

Tbd:

- memory management
- multiprocessor stuff
- processes/user mode
- disk driver

## Building

Install the following:

- x86_64-elf-gcc
- xorriso
- ninja (the build system)

run:

- `ninja -C build iso`

This will generate a new `disk.iso` in the root source directory.
Use qemu to run it.
Note that to generate a new disk.iso, you will need to
remove it, because of CMake's finicky dependency tracking.