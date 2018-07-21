#ifndef XARRAY_H_INCLUDED
#define XARRAY_H_INCLUDED

#include <stddef.h>

#define XArray_Alloc(size, elementType) XArray_AllocRaw(size, sizeof (elementType))
void *XArray_AllocRaw(size_t initialSize, size_t elementSize);

#define XArray_Resize(arr, newSize) XArray_ResizeRaw(arr, sizeof *(arr), newSize)
void *XArray_ResizeRaw(void *arr, size_t elementSize, size_t newSize);

#define XArray_Insert(arr, i) XArray_InsertRaw(arr, sizeof *(arr), i)
void *XArray_InsertRaw(void *arr, size_t elementSize, size_t i);

#define XArray_Remove(arr, i) XArray_RemoveRaw(arr, sizeof *(arr), i)
void *XArray_RemoveRaw(void *arr, size_t elementSize, size_t i);

size_t XArray_Len(void *arr);

void XArray_Free(void *arr);

#endif // XARRAY_H_INCLUDED
