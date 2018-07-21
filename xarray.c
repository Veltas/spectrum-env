#include <stddef.h>
#include <string.h>
#include "allocator.h"

#include "xarray.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
	size_t len;
	char data[1];
} Internals;

void *XArray_AllocRaw(size_t initialSize, size_t elementSize)
{
	size_t bCap;
	Internals *internals;
	void *result = NULL;

	bCap = elementSize * MAX(1, initialSize);
	internals = Allocate(offsetof(Internals, data) + bCap);
	if (internals) {
		internals->len = initialSize;
		result = internals->data;
	}

	return result;
}

void *XArray_ResizeRaw(void *arr, size_t elementSize, size_t newSize)
{
	size_t bCap;
	Internals *internals;
	void *result = NULL;

	bCap = elementSize * MAX(1, newSize);
	internals = (void *)((Byte *)arr - offsetof(Internals, data));
	internals = Reallocate(internals, offsetof(Internals, data) + bCap);
	if (internals) {
		internals->len = newSize;
		result = internals->data;
	}

	return result;
}

void *XArray_InsertRaw(void *arr, size_t elementSize, size_t i)
{
	size_t bCap;
	Internals *internals;
	Byte *movePtr;
	void *result = NULL;

	internals = (void *)((Byte *)arr - offsetof(Internals, data));
	bCap = AllocCap(internals) - offsetof(Internals, data);
	if (bCap == elementSize * internals->len) {
		bCap *= 2;
		internals = Reallocate(internals, offsetof(Internals, data) + bCap);
	}
	if (internals) {
		result = internals->data;
		movePtr = (Byte *)result + i*elementSize;
		memmove(movePtr + elementSize, movePtr, elementSize * (internals->len - i));
		++internals->len;
	}

	return result;
}

void *XArray_RemoveRaw(void *arr, size_t elementSize, size_t i)
{
	size_t bCap;
	Byte *movePtr;
	Internals *internals;

	internals = (void *)((Byte *)arr - offsetof(Internals, data));
	movePtr = (Byte *)arr + i*elementSize;
	memmove(movePtr, movePtr + elementSize, elementSize * (internals->len-i-1));
	--internals->len;
	bCap = AllocCap(internals) - offsetof(Internals, data);
	if (bCap >= 14 && bCap == 2*elementSize*internals->len) {
		bCap = elementSize*internals->len;
		internals = Reallocate(internals, offsetof(Internals, data) + bCap);
		if (!internals) {
			internals = (void *)((Byte *)arr - offsetof(Internals, data));
		}
	}

	return internals->data;
}

size_t XArray_Len(void *arr)
{
	Internals *internals;

	internals = (void *)((Byte *)arr - offsetof(Internals, data));

	return internals->len;
}

void XArray_Free(void *arr)
{
	Internals *internals;

	internals = (void *)((Byte *)arr - offsetof(Internals, data));
	Free(internals);
}
