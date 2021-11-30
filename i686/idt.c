#include "idt.h"
#include <string.h>
#include "c-asm.h"

idtdes_t idt[256];
idtr_t idtr;

/* install idt
 */
static void
idtins ()
{
    asm volatile("lidt [_idtr]");
}

#ifndef NKRELEASE
#include <stdio.h>
#endif

/* default idt handler
 */
void
idtdef (void *a, int b)
{
    cli ();
#ifndef NKRELEASE
    /* Don't use locale for this */
    printf ("");
#endif
    
    for (;;)
        ;
}

/* Install interrupt handler
 */
uint32_t
idtinr (uint32_t i, uint16_t flags, uint16_t sel, irqhan_t irq)
{
    if (i > 256)
        return 0;

    if (!irq)
        return 0;

    uint64_t uinbas = (uint64_t)(&(*irq));

    idt[i].baslow = uinbas & 0xffff;
    idt[i].bashi = (uinbas >> 16) & 0xffff;
    idt[i]._reserved = 0;
    idt[i].flags = flags;
    idt[i].sel = sel;

    return 0;
}

/* initialize idt
 */
int
idtini (uint16_t csel)
{

    idtr.limit = sizeof (idtdes_t) * 256 - 1;
    idtr.base = (uint32_t)&idt[0];

    memset ((void *)&idt[0], 0, sizeof (idtdes_t) * 256 - 1);

    for (int i = 0; i < 256; i++)
        idtinr (i, IDT_DESC_PRESENT | IDT_DESC_BIT32, csel, (irqhan_t)idtdef);

    idtins ();
    return 0;
}