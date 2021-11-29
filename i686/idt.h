#pragma once

#include <stdint.h>

#pragma pack(push, 1)

typedef struct 
{
    uint16_t baslow;
    uint16_t sel;
    uint8_t _reserved;
    uint8_t flags;
    uint16_t bashi;
} idtdes_t;

typedef struct 
{
    uint16_t limit;
    uint32_t base;
} idtr_t;

#pragma pack(pop)

#define I86_MAX_INTERRUPTS      256
#define I86_IDT_DESC_BIT16		0x06
#define I86_IDT_DESC_BIT32		0x0E
#define I86_IDT_DESC_RING1		0x40
#define I86_IDT_DESC_RING2		0x20
#define I86_IDT_DESC_RING3		0x60
#define I86_IDT_DESC_PRESENT	0x80

typedef __attribute__((interrupt)) void (*irqhan_t)(void*,int);

extern int idtini (uint16_t csel);