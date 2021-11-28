#include <hal/hal.h>
#include "cpu.h"

NKAPI uint16_t 
halini ()
{
    cpuini ();
    return 0;
}