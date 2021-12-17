#include <nkdef.h>

void
hal_outb(uint16_t port, uint8_t data)
{
    __asm__ volatile("out %0,%1"
                     :
                     : "a"(data), "d"(port));
}

void
hal_outw(uint16_t port, uint16_t data)
{
    __asm__ volatile("out %0,%1"
                     :
                     : "a"(data), "d"(port));
}

uint8_t
hal_inb(uint16_t port)
{
    uint8_t data;

    __asm__ volatile("in %1,%0"
                     : "=a"(data)
                     : "d"(port));
    return data;
}
