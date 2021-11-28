#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H
 
#include <stddef.h>
 
void ttyini(void);
void ttyputc(char c);
void ttyw(const char* data, size_t size);
void ttystr(const char* data);
 
#endif