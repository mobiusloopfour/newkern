#include "gdt.h"
#include <nk/nk32.h>
#include <string.h>

#ifndef NKRELEASE
#include <stdio.h>
#endif

static struct i686__HLGDTDescriptor gdt[MAX_DESCRIPTORS];
static struct i686__HLGDTR gdtr;

#pragma GCC push_options
#pragma GCC optimize("O0")
static VOID
HLGDTInstall ()
{
    __asm__ volatile("lgdt [_gdtr]");
}
#pragma GCC pop_options

static VOID
HLGDTSetDescriptor (
    DWORD i, 
    QWORD base, 
    QWORD limit, 
    BYTE access, 
    BYTE grand)
{
    if (i > MAX_DESCRIPTORS)
        {
#ifndef NKRELEASE
            printf ("Error: HLGDTSetDescriptor: i > MAX_DESCRIPTORS");
#endif
            return;
        }
    memset ((LPARAM)&gdt[i], 0, sizeof (struct i686__HLGDTDescriptor));

    gdt[i].m_BaseLow = base & 0xffff;
    gdt[i].m_BaseMid = (base >> 16) & 0xff;
    gdt[i].m_BaseHigh = (base >> 24) & 0xff;
    gdt[i].m_Limit = limit & 0xffff;
    gdt[i].m_Flags = access;
    gdt[i].m_Grand = (limit >> 16) & 0x0f;
    gdt[i].m_Grand |= grand & 0xf0;
}

DWORD
HLGDTInit ()
{

    gdtr.m_Limit
        = (sizeof (struct i686__HLGDTDescriptor) * MAX_DESCRIPTORS) - 1;
    gdtr.m_Base = (DWORD)&gdt[0];

    /* set null descriptor */
    HLGDTSetDescriptor (0, 0, 0, 0, 0);

    /* set default code descriptor */
    HLGDTSetDescriptor (1, 0, 0xffffffff,
                        I686_GDT_DESC_READWRITE | I686_GDT_DESC_EXEC_CODE
                            | I686_GDT_DESC_CODEDATA | I686_GDT_DESC_MEMORY,
                        I686_GDT_GRAND_4K | I686_GDT_GRAND_32BIT
                            | I686_GDT_GRAND_LIMITHI_MASK);

    /* set default data descriptor */
    HLGDTSetDescriptor (2, 0, 0xffffffff,
                        I686_GDT_DESC_READWRITE | I686_GDT_DESC_CODEDATA
                            | I686_GDT_DESC_MEMORY,
                        I686_GDT_GRAND_4K | I686_GDT_GRAND_32BIT
                            | I686_GDT_GRAND_LIMITHI_MASK);

    /* install gdtr */
    HLGDTInstall ();

    return 0;
}