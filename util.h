#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "defs.h"
#include "text.h"

// Perform 16-bit add and return carry state
Byte add_with_carry(unsigned *res, unsigned n, unsigned m);

// Get input byte from 16-bit I/O address
Byte Input16(unsigned addr);

// Keyboard feedback click
void Click(void);

// Warning/error beep for user
void Beep(void);

void PrintDecimal(Pen *pen, unsigned num);

// Gets current stack frame
void *GetStackF(void);

#endif // UTIL_H_INCLUDED
