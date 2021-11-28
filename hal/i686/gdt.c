#include "gdt.h"
#include <string.h>
#include <stdint.h>
#include <locale.h>
#ifndef NKRELEASE
#include <stdio.h>
#endif

gdtd_t gdt[MAX_DESCRIPTORS];
gdtr_t gdtr;

/* install descriptor
 */
#pragma GCC push_options
#pragma GCC optimize("O0")
static void
gdtins ()
{
    asm volatile("lgdt [_gdtr]");
}
#pragma GCC pop_options

/* set descriptor
 */
static void
gdtsed (
    uint32_t i, 
    uint64_t base, 
    uint64_t limit, 
    uint8_t access, 
    uint8_t grand)
{
    if (i > MAX_DESCRIPTORS)
        {
#ifndef NKRELEASE
            printf (strtab[GDTSED_I_MAX_DESCRIPTORS]);
#endif
            return;
        }
    memset ((void*)&gdt[i], 0, sizeof (gdtd_t));

    gdt[i].baslow = base & 0xffff;
    gdt[i].basmid = (base >> 16) & 0xff;
    gdt[i].bashi = (base >> 24) & 0xff;
    gdt[i].limit = limit & 0xffff;
    gdt[i].flags = access;
    gdt[i].gran = (limit >> 16) & 0x0f;
    gdt[i].gran |= grand & 0xf0;
}

uint32_t
gdtini ()
{

    gdtr.limit
        = (sizeof (gdtd_t) * MAX_DESCRIPTORS) - 1;
    gdtr.base = (uint32_t)&gdt[0];

    /* set null descriptor */
    gdtsed (0, 0, 0, 0, 0);

    /* set default code descriptor */
    gdtsed (1, 0, 0xffffffff,
                        I686_GDT_DESC_READWRITE | I686_GDT_DESC_EXEC_CODE
                            | I686_GDT_DESC_CODEDATA | I686_GDT_DESC_MEMORY,
                        I686_GDT_GRAND_4K | I686_GDT_GRAND_32BIT
                            | I686_GDT_GRAND_LIMITHI_MASK);

    /* set default data descriptor */
    gdtsed (2, 0, 0xffffffff,
                        I686_GDT_DESC_READWRITE | I686_GDT_DESC_CODEDATA
                            | I686_GDT_DESC_MEMORY,
                        I686_GDT_GRAND_4K | I686_GDT_GRAND_32BIT
                            | I686_GDT_GRAND_LIMITHI_MASK);

    /* install gdtr */
    gdtins ();

    return 0;
}