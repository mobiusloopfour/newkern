#include "serial.h"
#include <sys/stdio.h>

extern void picsc (int, int);

void
idone (intno)
{
	if (intno > 16)
        {
            printf("Invalid!\n");
            return;
        }

	/* test if we need to send end-of-interrupt to second pic */
	if (intno >= 8)
		picsc (PIC_OCW2_MASK_EOI, 1);

	/* always send end-of-interrupt to primary pic */
	picsc (PIC_OCW2_MASK_EOI, 0);
}