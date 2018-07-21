#ifndef ALLOCATOR_H_INCLUDED
#define ALLOCATOR_H_INCLUDED

#include <stddef.h>
#include "defs.h"

// This is the total size of blocks allocated in heap space, it can give an
// indication of how 'used' the heap is. GetAllocatorUsage will give a number
// between 0 and 255, but is slower than checking this value.
extern size_t g_totalAllocated;

// Must be called in startup before any heap usage
void AllocInit(void);

// Like malloc
void *Allocate(size_t n);

// Returns capacity of an allocated space (or 0 if p is null pointer)
size_t AllocCap(void *p);

// Returns conservative usage estimate from 0-255
Byte AllocUsage(void);

// Like realloc
void *Reallocate(void *p, size_t n);

// Like free
void Free(void *p);

#endif // XALLOC_H_INCLUDED
