#pragma once
#include <stdint.h>

static const PIT_OCW_MASK_BINCOUNT = 1;
static const PIT_OCW_MASK_MODE = 0xE;
static const PIT_OCW_MASK_RL = 0x30;
static const PIT_OCW_MASK_COUNTER = 0xC0;

static const PIT_OCW_BINCOUNT_BINARY
    = 0; /* 0		 Use when setting PIT_OCW_MASK_BINCOUNT */
static const PIT_OCW_BINCOUNT_BCD = 1; /* 1 */
static const PIT_OCW_MODE_TERMINALCOUNT
    = 0; /* 0000		 Use when setting PIT_OCW_MASK_MODE */
static const PIT_OCW_MODE_ONESHOT = 0x2;       /* 0010 */
static const PIT_OCW_MODE_RATEGEN = 0x4;       /* 0100 */
static const PIT_OCW_MODE_SQUAREWAVEGEN = 0x6; /* 0110 */
static const PIT_OCW_MODE_SOFTWARETRIG = 0x8;  /* 1000 */
static const PIT_OCW_MODE_HARDWARETRIG = 0xA;  /* 1010 */
static const PIT_OCW_RL_LATCH
    = 0; /* 000000	 Use when setting PIT_OCW_MASK_RL */
static const PIT_OCW_RL_LSBONLY = 0x10; /* 010000 */
static const PIT_OCW_RL_MSBONLY = 0x20; /* 100000 */
static const PIT_OCW_RL_DATA = 0x30;    /* 110000 */
static const PIT_OCW_COUNTER_0
    = 0; /* 00000000	 Use when setting PIT_OCW_MASK_COUNTER */
static const PIT_OCW_COUNTER_1 = 0x40; /* 01000000 */
static const PIT_OCW_COUNTER_2 = 0x80; /* 10000000 */

extern void pitstc (uint32_t freq, uint8_t count, uint8_t mode);
extern void pitini ();