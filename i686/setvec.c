#include "idt.h"

void
setvec (int intno, irqhan_t vect)
{
    idtinr (intno, IDT_DESC_PRESENT | IDT_DESC_BIT32, 0x8, vect);
}