#include <hal/hal.h>
#include "cpu.h"

NKAPI WORD 
HLInit ()
{
    HLCPUInit ();
    return 0;
}