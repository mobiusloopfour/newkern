AUTOMAKE_OPTIONS = gnu subdir-objects

AM_CFLAGS = $(CFLAGS) -Wno-pointer-to-int-cast -Wno-implicit-int -pipe -O3
AM_CFLAGS += \
    -I. \
    -I./i686/ \
    -I./sys/ \
    -I./EXTERNAL_HEADERS

AM_LDFLAGS = \
    -Ti686/link.ld \
    -z max-page-size=4096

K=kern
A=i686
L=libc

bin_PROGRAMS = sys_kern
sys_kern_SOURCES = \
    $K/main.c \
    $K/init.c \
    $K/tty.c \
    $K/strtab.c \
    $A/asm.c \
    $A/cpu.c \
    $A/entry.S \
    $A/gdt.c \
    $A/hal-init.c \
    $A/hal-off.c \
    $A/idone.c \
    $A/idt.c \
    $A/pic.c \
    $A/pit.c \
    $A/setvec.c \
    $A/serial.c \
    $L/printf.c \
    $L/string.c


qemu: sys_kern
	qemu-system-x86_64 -monitor stdio -smp 2 -net nic,model=rtl8139 -net user,hostfwd=tcp::12345-:7  -kernel sys_kern