#pragma once
#include <stdint.h>
#include <xv6-asm.h>

extern uint16_t halini ();
extern uint16_t haloff ();
extern uint8_t halinb ();
extern void haloub ();
extern void idone (int);