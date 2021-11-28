#pragma once
#pragma pack(push, 1)

#include <nk/nk32.h>

#define MAX_DESCRIPTORS 3

struct i686__HLGDTDescriptor {
    WORD m_Limit;
    WORD m_BaseLow;
    BYTE m_BaseMid;
    BYTE m_Flags;
    BYTE m_Grand;
    BYTE m_BaseHigh;
};

struct i686__HLGDTR {
    WORD m_Limit;
    DWORD m_Base;
};

#pragma pack(pop)


#define I686_GDT_DESC_ACCESS			0x0001
#define I686_GDT_DESC_READWRITE			0x0002
#define I686_GDT_DESC_EXPANSION			0x0004
#define I686_GDT_DESC_EXEC_CODE			0x0008
#define I686_GDT_DESC_CODEDATA			0x0010
#define I686_GDT_DESC_DPL			    0x0060
#define I686_GDT_DESC_MEMORY			0x0080

/* grandularity bit flags */

#define I686_GDT_GRAND_LIMITHI_MASK		0x0f
#define I686_GDT_GRAND_OS			    0x10
#define I686_GDT_GRAND_32BIT			0x40

/* 4k grandularity. default: none */
#define I686_GDT_GRAND_4K			    0x80

DWORD HLGDTInit ();