#include "c-asm.h"
#include "serial.h"

static const PIC_ICW4_MASK_UPM = 0x1;
static const PIC_ICW4_UPM_86MODE = 1;

static const PIC1_REG_COMMAND = 0x20;
static const PIC1_REG_STATUS = 0x20;
static const PIC1_REG_DATA = 0x21;
static const PIC1_REG_IMR = 0x21;
static const PIC2_REG_COMMAND = 0xA0;
static const PIC2_REG_STATUS = 0xA0;
static const PIC2_REG_DATA = 0xA1;
static const PIC2_REG_IMR = 0xA1;

static const PIC_ICW1_MASK_IC4 = 0x1;  /* 00000001	 Expect ICW 4 bit */
static const PIC_ICW1_MASK_SNGL = 0x2; /* 00000010  Single or Cascaded */
static const PIC_ICW1_MASK_ADI = 0x4;  /* 00000100	 Call Address Interval
                                        */
static const PIC_ICW1_MASK_LTIM = 0x8; /* 00001000	 Operation Mode */
static const PIC_ICW1_MASK_INIT = 0x10;

extern void irqpit (void*,int);

/* send a command to the pic
 */
void
picsc (cmd, pnum)
{
    if (pnum > 1)
        {
            return;
        }
    uint8_t r = (pnum == 1) ? PIC2_REG_COMMAND : PIC1_REG_COMMAND;
    outb (r, (uint8_t)cmd);
}

/* send and read data
 */
void
picsd (data, pnum)
{
    if (pnum > 1)
        {
            return;
        }
    uint8_t r = (pnum == 1) ? PIC2_REG_DATA : PIC1_REG_DATA;
    outb (r, data);
}

uint8_t
picrd(data, pnum)
{
    if (pnum > 1)
        {
            return 0;
        }
    uint8_t r = (pnum == 1) ? PIC2_REG_DATA : PIC1_REG_DATA;
    return inb (r);
}

void 
picini (b0, b1)
{
    uint8_t icw;
    icw ^= icw;

    icw = (icw & PIC_ICW1_MASK_INIT) | 16;
    icw = (icw & ~PIC_ICW1_MASK_IC4) | 1;

    picsc (icw, 0);
    picsc (icw, 1);

    picsd (b0, 0);
    picsd (b1, 1);

    picsd (0x04, 0);
    picsd (0x02, 1);

    icw = (icw & ~PIC_ICW4_MASK_UPM) | PIC_ICW4_UPM_86MODE;

    picsd (icw, 0);
    picsd (icw, 1);
}