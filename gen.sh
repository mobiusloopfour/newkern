#!/usr/bin/env sh
automake --add-missing
autoreconf -fi
./configure --host="i686-elf"