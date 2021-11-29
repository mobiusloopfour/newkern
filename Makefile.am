AUTOMAKE_OPTIONS = gnu subdir-objects

AM_CFLAGS = $(CFLAGS)
AM_CFLAGS += \
    -I. \
    -I./i686/ \
    -I./sys/ \
    -I./EXTERNAL_HEADERS

AM_LDFLAGS = \
    -Ti686/link.ld \
    -z max-page-size=4096

bin_PROGRAMS = sys_kern
sys_kern_SOURCES = \
    kern/main.c \
    kern/init.c \
    kern/tty.c \
    kern/strtab.c \
    i686/asm.c \
    i686/cpu.c \
    i686/entry.S \
    i686/gdt.c \
    i686/hal-init.c \
    i686/hal-off.c \
    i686/idt.c \
    libc/printf.c \
    libc/string.c


qemu: sys_kern
	qemu-system-x86_64 -monitor stdio -smp 2 -net nic,model=rtl8139 -net user,hostfwd=tcp::12345-:7  -kernel sys_kern