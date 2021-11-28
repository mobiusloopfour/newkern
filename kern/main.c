#include <stdio.h>
#include <nk/nk32.h>
#include <hal/hal.h>

static char str[] = "Yes!";

int
NKMain ()
{
    HLInit ();
    printf (str);
    while (1)
        ;
}