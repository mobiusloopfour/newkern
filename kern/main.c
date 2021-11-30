#include <stdio.h>
#include <hal/hal.h>

#include <locale.h>

extern void idtint ();

int
kmain ()
{
    halini ();
    printf ("\n%s", strtab[KERNEL_LOADED]);
    while (1)
        ;
}