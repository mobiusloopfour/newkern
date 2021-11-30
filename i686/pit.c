#include "pit.h"
#include "c-asm.h"
#include "idt.h"
#include <stdint.h>
#include <sys/stdio.h>

static const PIT_REG_COUNTER0 = 0x40;
static const PIT_REG_COUNTER1 = 0x41;
static const PIT_REG_COUNTER2 = 0x42;
static const PIT_REG_COMMAND = 0x43;

static uint16_t pittck = 0;
static uint8_t isinit = 0;

extern void idone(int);

#pragma GCC push_options
#pragma GCC optimize ("O0")
void
pitirq ()
{
    asm volatile (
        "add $12, %esp\n"
        "pusha\n"
    );

    pittck++;
    idone (0);

    asm volatile (
        "popa\n"
        "iret\n"
    );
}
#pragma GCC pop_options

void
pitsen (cmd)
{
    outb (PIT_REG_COMMAND, cmd);
}

/* send data
 */
void
pitsed (uint16_t data, uint8_t count)
{

    uint8_t port
        = (count == PIT_OCW_COUNTER_0)
              ? PIT_REG_COUNTER0
              : ((count == PIT_OCW_COUNTER_1) ? PIT_REG_COUNTER1
                                                    : PIT_REG_COUNTER2);

    outb (port, data);
}

/* start counting
 */
void
pitstc (uint32_t freq, uint8_t count, uint8_t mode)
{

    if (freq == 0)
        return;

    uint16_t div = 1193180 / freq;

    uint8_t ocw = 0;
    ocw = (ocw & ~PIT_OCW_MASK_MODE) | mode;
    ocw = (ocw & ~PIT_OCW_MASK_RL) | PIT_OCW_RL_DATA;
    ocw = (ocw & ~PIT_OCW_MASK_COUNTER) | count;
    pitsen (ocw);

    //! set frequency rate
    pitsed (div & 0xff, 0);
    pitsed ((div >> 8) & 0xff, 0);

    //! reset tick count
    pittck = 0;
}

extern void setvec (int intno, irqhan_t vect);

/* init pit
 */
void
pitini ()
{
    if (isinit)
        {
            return;
        }
    setvec (32, pitirq);
    isinit = 1;
}