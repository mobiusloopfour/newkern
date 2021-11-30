/*
    The xv6 software is:

Copyright (c) 2006-2018 Frans Kaashoek, Robert Morris, Russ Cox,
                        Massachusetts Institute of Technology

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 */


#pragma once
// Routines to let C code use special x86 instructions.

#include <stdint.h>

static inline uint8_t
inb (uint16_t port)
{
    uint8_t data;

    asm volatile("in %1,%0" : "=a"(data) : "d"(port));
    return data;
}

static inline void
insl (int port, void *addr, int cnt)
{
    asm volatile("cld; rep insl"
                 : "=D"(addr), "=c"(cnt)
                 : "d"(port), "0"(addr), "1"(cnt)
                 : "memory", "cc");
}

static inline void
outb (uint16_t port, uint8_t data)
{
    asm volatile("out %0,%1" : : "a"(data), "d"(port));
}

static inline void
outw (uint16_t port, uint16_t data)
{
    asm volatile("out %0,%1" : : "a"(data), "d"(port));
}

static inline void
outsl (int port, const void *addr, int cnt)
{
    asm volatile("cld; rep outsl"
                 : "=S"(addr), "=c"(cnt)
                 : "d"(port), "0"(addr), "1"(cnt)
                 : "cc");
}

static inline void
stosb (void *addr, int data, int cnt)
{
    asm volatile("cld; rep stosb"
                 : "=D"(addr), "=c"(cnt)
                 : "0"(addr), "1"(cnt), "a"(data)
                 : "memory", "cc");
}

static inline void
stosl (void *addr, int data, int cnt)
{
    asm volatile("cld; rep stosl"
                 : "=D"(addr), "=c"(cnt)
                 : "0"(addr), "1"(cnt), "a"(data)
                 : "memory", "cc");
}

struct segdesc;

static inline void
lgdt (struct segdesc *p, int size)
{
    volatile uint16_t pd[3];

    pd[0] = size - 1;
    pd[1] = (uint32_t)p;
    pd[2] = (uint32_t)p >> 16;

    asm volatile("lgdt (%0)" : : "r"(pd));
}

struct gatedesc;

static inline void
lidt (struct gatedesc *p, int size)
{
    volatile uint16_t pd[3];

    pd[0] = size - 1;
    pd[1] = (uint32_t)p;
    pd[2] = (uint32_t)p >> 16;

    asm volatile("lidt (%0)" : : "r"(pd));
}

static inline void
ltr (uint16_t sel)
{
    asm volatile("ltr %0" : : "r"(sel));
}

static inline uint32_t
readeflags (void)
{
    uint32_t eflags;
    asm volatile("pushfl; popl %0" : "=r"(eflags));
    return eflags;
}

static inline void
loadgs (uint16_t v)
{
    asm volatile("movw %0, %%gs" : : "r"(v));
}

static inline void
cli (void)
{
    asm volatile("cli");
}

static inline void
sti (void)
{
    asm volatile("sti");
}

static inline uint32_t
xchg (volatile uint32_t *addr, uint32_t newval)
{
    uint32_t result;

    // The + in "+m" denotes a read-modify-write operand.
    asm volatile("lock; xchgl %0, %1"
                 : "+m"(*addr), "=a"(result)
                 : "1"(newval)
                 : "cc");
    return result;
}

static inline uint32_t
rcr2 (void)
{
    uint32_t val;
    asm volatile("movl %%cr2,%0" : "=r"(val));
    return val;
}

static inline void
lcr3 (uint32_t val)
{
    asm volatile("movl %0,%%cr3" : : "r"(val));
}

// PAGEBREAK: 36
//  Layout of the trap frame built on the stack by the
//  hardware and by trapasm.S, and passed to trap().
typedef struct trapframe
{
    // registers as pushed by pusha
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t oesp; // useless & ignored
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;

    // rest of trap frame
    uint16_t gs;
    uint16_t padding1;
    uint16_t fs;
    uint16_t padding2;
    uint16_t es;
    uint16_t padding3;
    uint16_t ds;
    uint16_t padding4;
    uint32_t trapno;

    // below here defined by x86 hardware
    uint32_t err;
    uint32_t eip;
    uint16_t cs;
    uint16_t padding5;
    uint32_t eflags;

    // below here only when crossing rings, such as from user to kernel
    uint32_t esp;
    uint16_t ss;
    uint16_t padding6;
} trapframe_t;