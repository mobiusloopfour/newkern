/ Declare constants for the multiboot header.
.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

/ Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/ Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 /* 16 KiB */
stack_top:

#include "asm.h"

/ The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp

    / Call initializers
    call EXT_C(kinit)
	/ Transfer control to the main kernel.
	call EXT_C(kmain)

	/ Hang if kmain unexpectedly returns.
	cli
1:	hlt
	jmp 1b
.size _start, . - _start
