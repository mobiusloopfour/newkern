#pragma once
#pragma GCC system_header /* warnings about inline variables */

/* The following devices use PIC 1 to generate interrupts */
static inline const PIC_IRQ_TIMER = 0;
static inline const PIC_IRQ_KEYBOARD = 1;
static inline const PIC_IRQ_SERIAL2 = 3;
static inline const PIC_IRQ_SERIAL1 = 4;
static inline const PIC_IRQ_PARALLEL2 = 5;
static inline const PIC_IRQ_DISKETTE = 6;
static inline const PIC_IRQ_PARALLEL1 = 7;

/* The following devices use PIC 2 to generate interrupts */
static inline const PIC_IRQ_CMOSTIMER = 0;
static inline const PIC_IRQ_CGARETRACE = 1;
static inline const PIC_IRQ_AUXILIARY = 4;
static inline const PIC_IRQ_FPU = 5;
static inline const PIC_IRQ_HDC = 6;

static inline const PIC_OCW2_MASK_L1
    = 1; /* 00000001	-> Level 1 interrupt level */
static inline const PIC_OCW2_MASK_L2
    = 2; /* 00000010	-> Level 2 interrupt level */
static inline const PIC_OCW2_MASK_L3
    = 4; /* 00000100	-> Level 3 interrupt level */
static inline const PIC_OCW2_MASK_EOI
    = 0x20; /* 00100000	-> End of Interrupt command */
static inline const PIC_OCW2_MASK_SL = 0x40; /* 01000000	-> Select command
                                              */
static inline const PIC_OCW2_MASK_ROTATE
    = 0x80; /* 10000000	-> Rotation command */

static inline const PIC_OCW3_MASK_RIS = 1;
static inline const PIC_OCW3_MASK_RIR = 2;
static inline const PIC_OCW3_MASK_MODE = 4;
static inline const PIC_OCW3_MASK_SMM = 0x20;
static inline const PIC_OCW3_MASK_ESMM = 0x40;
static inline const PIC_OCW3_MASK_D7 = 0x80;