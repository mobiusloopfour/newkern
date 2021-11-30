#include <hal/hal.h>
#include "cpu.h"
#include "c-asm.h"
#include "pit.h"

extern void picini (unsigned, unsigned);

uint16_t 
halini ()
{
    cli ();
    cpuini ();
    
    picini (0x20, 0x28);
    pitini ();
    // pitstc (100, PIT_OCW_COUNTER_0, PIT_OCW_MODE_SQUAREWAVEGEN); // does not work yet!

    sti ();
    return 0;
}