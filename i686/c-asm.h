#pragma once
#include <xv6-asm.h>

#define START_INTERRUPT(X) \
    __asm__ __volatile__ ("cli"); \
    __asm__ __volatile__ ("sub $4, %ebp")

#define END_INTERRUPT(X) \
    __asm__ __volatile__ ("iret")
