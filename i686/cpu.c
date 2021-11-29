#include "gdt.h"
#include "idt.h"
#include <hal/cpuid.h>

uint32_t 
cpuini ()
{
    gdtini ();
    idtini (0x8);
    return 0;
}