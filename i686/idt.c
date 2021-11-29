#include "idt.h"
#include <string.h>

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
idtdef (void* a, int b)
{
#ifndef NKRELEASE
    /* Don't use locale for this */
    printf ("Unhandled interrupt\n");
#endif
    return;
    while (1)
        ;
}

void
idtin0 ()
{
    asm volatile("int $0\n");
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

    uint64_t uinbas = (uint64_t) & (*irq);

    idt[i].baslow = uinbas & 0xffff;
    idt[i].bashi = (uinbas >> 16) & 0xffff;
    idt[i]._reserved = 0;
    idt[i].flags = flags;
    idt[i].sel = sel;

    return 0;
}

/* initialize idt
 */
int idtini (uint16_t csel) {
 
	/* set up idtr for processor */
	idtr.limit = sizeof (idtdes_t) * 256 -1;
	idtr.base	= (uint32_t)&idt[0];
 
	/* null out the idt */
	memset ((void*)&idt[0], 0, sizeof (idtdes_t) * 256 - 1);
 
	/* register default handlers */
	for (int i=0; i<256; i++)
		idtinr (i, I86_IDT_DESC_PRESENT | I86_IDT_DESC_BIT32,
			csel, (irqhan_t)idtdef);
 
	/* install our idt */
	idtins ();
 
	return 0;
}