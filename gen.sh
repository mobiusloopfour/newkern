#!/usr/bin/env sh
autoreconf -fi
automake --add-missing
autoreconf -fi
./configure --host="i686-elf"