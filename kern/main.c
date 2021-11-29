#include <stdio.h>
#include <hal/hal.h>

#include <locale.h>

extern void idtint ();

int
kmain ()
{
    halini ();
    printf (strtab[GDT_LOADED]);
    asm volatile ("int $10");
    asm volatile ("int $0");
    while (1)
        ;
}