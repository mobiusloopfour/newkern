#include "gdt.h"

DWORD 
HLCPUInit ()
{
    HLGDTInit ();
    return 0;
}