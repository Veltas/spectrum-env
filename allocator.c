#ifndef NAUDIT
#define NAUDIT
#endif

#include <stddef.h>
#include <string.h>
#include "defs.h"

#include "allocator.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) <= (b) ? (a) : (b))
#define LEN(arr) ((sizeof (arr)) / sizeof *(arr))

size_t g_totalAllocated;

__at(23296) static Byte space[9472];

typedef struct {
	unsigned len:15,
	         isFree:1;
} Border;

typedef struct FreeHeader_tag {
	Border border;
	struct FreeHeader_tag *prev, *next;
} FreeHeader;

typedef struct {
	FreeHeader *first, *last;
} FreeList;

#define IS_TINY_BLOCK(n) (n <= 8)
#define IS_SMALL_BLOCK(n) (n <= 256)
// IS_LARGE_BLOCK(n) implicit for larger n

static FreeList tinyFrees, smallFrees;
static FreeList largeFrees = {(void *)space, (void *)space};

#define BLOCK_OVERHEAD (2 * sizeof (Border))
#define MIN_BLOCK_SIZE (sizeof (FreeHeader) + sizeof (Border))

#ifndef NAUDIT
//#define AssertFail(s,f,l,m) return 0
// Called by HeapAudit()
static Byte HeapAuditX(FreeList *frees, size_t *freeCount)
{
	FreeHeader *free, *next;

	if (!!frees->first != !!frees->last) {
		AssertFail(
			"Free list first/last exists without last/first",
			__FILE__, __LINE__, AssertType_audit
		);
	}
	for (free = frees->first; free; free = free->next) {
		if (free == frees->first && free->prev) {
			AssertFail(
				"First free in free list has non-null prev",
				__FILE__, __LINE__, AssertType_audit
			);
		}
		if (free == frees->last && free->next) {
			AssertFail(
				"Last free in free list has non-null next",
				__FILE__, __LINE__, AssertType_audit
			);
		}
		next = free->next;
		if (next && ((Byte *)next < space || (Byte *)next > space + LEN(space))) {
			AssertFail(
				"Free block next pointer leads out of heap space",
				__FILE__, __LINE__, AssertType_audit
			);
		}
		if (next && free != next->prev) {
			AssertFail(
				"Free in free list with incorrect prev",
				__FILE__, __LINE__, AssertType_audit
			);
		}
		*freeCount += free->border.len;
	}
	return 1;
}
// Checks the integrity of the heap and all associated data structures
static Byte HeapAudit(void)
{
	Border *block, *endBorder, *next, *end;
	size_t total = 0;
	Byte prevFree = 0;

	end = (void *)(space + LEN(space));
	for (block = (void *)space; (Byte *)block < (Byte *)end; block = next) {
		if (prevFree && block->isFree) {
			AssertFail(
				"Contiguous free blocks found in heap space",
				__FILE__, __LINE__, AssertType_audit
			);
		}
		prevFree = block->isFree;
		if (block->len < MIN_BLOCK_SIZE || block->len > LEN(space)) {
			AssertFail(
				"Heap block primary border length entry corrupted",
				__FILE__, __LINE__, AssertType_audit
			);
		}
		next = (void *)((Byte *)block + block->len);
		if ((Byte *)next > (Byte *)end) {
			AssertFail(
				"Heap block primary border length entry too large",
				__FILE__, __LINE__, AssertType_audit
			);
		}
		endBorder = next - 1;
		if (memcmp(block, endBorder, sizeof *block)) {
			AssertFail(
				"Corrupted heap block borders",
				__FILE__, __LINE__, AssertType_audit
			);
		}
		if (!block->isFree) {
			total += block->len;
		}
	}
	if (total != g_totalAllocated) {
		AssertFail(
			"Total allocation count corrupted",
			__FILE__, __LINE__, AssertType_audit
		);
	}
	total = 0;
	if (!HeapAuditX(&tinyFrees, &total)) return 0;
	if (!HeapAuditX(&smallFrees, &total)) return 0;
	if (!HeapAuditX(&largeFrees, &total)) return 0;
	if (LEN(space) - total != g_totalAllocated) {
		AssertFail(
			"Traversable free blocks do not account for all free space",
			__FILE__, __LINE__, AssertType_audit
		);
	}
	return 1;
}
//#undef AssertFail
#endif // ifndef NAUDIT

// Sets borders on a region starting at $block, of size $len
static void SetBorders(void *block, Byte isFree, size_t len)
{
	Border *start, *end;

	start = block;
	end = (Border *)((Byte *)block + len) - 1;
	start->isFree = !!isFree;
	end->isFree = !!isFree;
	start->len = len;
	end->len = len;
}

// Returns 0, 1 or 2 for tiny, small or large sizes respectively
static Byte GetFreesIndex(size_t n)
{
	Byte result = 2;

	if (IS_TINY_BLOCK(n)) {
		result = 0;
	} else if (IS_SMALL_BLOCK(n)) {
		result = 1;
	}
	return result;
}

// Called by AddFree
static void AddFreeX(FreeList *list, FreeHeader *newFree)
{
	g_totalAllocated -= newFree->border.len;

	newFree->next = NULL;
	newFree->prev = list->last;
	if (!list->last) {
		list->first = newFree;
		list->last = newFree;
	} else {
		list->last->next = newFree;
		list->last = newFree;
	}
}

// Adds free block to the appropriate free-list
static void AddFree(void *newFree)
{
	switch (GetFreesIndex(((Border *)newFree)->len)) {
	case 0:
		AddFreeX(&tinyFrees, newFree);
		break;
	case 1:
		AddFreeX(&smallFrees, newFree);
		break;
	case 2:
		AddFreeX(&largeFrees, newFree);
		break;
	}
}

// Called by RemoveFree
static void RemoveFreeX(FreeList *list, FreeHeader *free)
{
	g_totalAllocated += free->border.len;

	if (list->first == free) {
		list->first = free->next;
	} else {
		free->prev->next = free->next;
	}
	if (list->last == free) {
		list->last = free->prev;
	} else {
		free->next->prev = free->prev;
	}
}

// Removes free block from its free-list
static void RemoveFree(void *free)
{
	switch (GetFreesIndex(((Border *)free)->len)) {
	case 0:
		RemoveFreeX(&tinyFrees, free);
		break;
	case 1:
		RemoveFreeX(&smallFrees, free);
		break;
	case 2:
		RemoveFreeX(&largeFrees, free);
		break;
	}
}

// Called by BlockAlloc
static void *BlockAllocX(FreeList *frees, size_t n)
{
	FreeHeader *free, *newFree;
	size_t freeLen;
	void *result = NULL;

	for (free = frees->first; free; free = free->next) {
		freeLen = free->border.len;
		if (freeLen >= n) {
			result = free;
			RemoveFree(free);
			if (freeLen >= n + MIN_BLOCK_SIZE) {
				newFree = (void *)((Byte *)free + n);
				SetBorders(free, 0, n);
				SetBorders(newFree, 1, freeLen - n);
				AddFree(newFree);
			} else {
				SetBorders(free, 0, freeLen);
			}
			break;
		}
	}
	return result;
}

// Allocates a block from the heap to use, if possible
static void *BlockAlloc(size_t n)
{
	void *result = NULL;

	switch (GetFreesIndex(n)) {
	case 0:
		result = BlockAllocX(&tinyFrees, n);
	case 1: // FALLTHRU
		if (!result) {
			result = BlockAllocX(&smallFrees, n);
		}
	case 2: // FALLTHRU
		if (!result) {
			result = BlockAllocX(&largeFrees, n);
		}
	}
	return result;
}

void AllocInit(void)
{
	FreeHeader *newFree;

	SetBorders(space, 1, LEN(space));
	newFree = (void *)space;
	newFree->prev = NULL;
	newFree->next = NULL;

	AuditAssert(HeapAudit());
}

void *Allocate(size_t n)
{
	Border *block;
	void *result = NULL;

	AuditAssert(HeapAudit());

	if (n != 0) {
		block = BlockAlloc(MAX(MIN_BLOCK_SIZE, n + BLOCK_OVERHEAD));
		if (block) {
			result = block + 1;
		}
	}

	AuditAssert(HeapAudit());

	return result;
}

size_t AllocCap(void *p)
{
	Border *block;

	block = ((Border *)p) - 1;
	return block->len - BLOCK_OVERHEAD;
}

Byte AllocUsage(void)
{
	unsigned calc;
	Byte result = 255;

	calc = g_totalAllocated >> 5;
	if (!(calc >> 8)) {
		result = calc;
	}
	return result;
}

// TODO currently just wraps the other functions
void *Reallocate(void *p, size_t n)
{
	size_t currentCapacity;
	void *result = NULL;

	if (!p) {
		result = Allocate(n);
	} else if (n == 0) {
		Free(p);
	} else {
		currentCapacity = AllocCap(p);
		if (currentCapacity == n) {
			result = p;
		} else {
			result = Allocate(n);
			if (!result && currentCapacity > n) {
				result = p;
			} else if (result) {
				memcpy(result, p, MIN(n, currentCapacity));
				Free(p);
			}
		}
	}

	return result;
}

void Free(void *p)
{
	Border *block, *prev = NULL, *next = NULL;
	size_t blockLen, prevContrib = 0, nextContrib = 0;
	FreeHeader *newFree;

	AuditAssert(HeapAudit());

	if (p) {
		block = (Border *)p - 1;
		blockLen = block->len;
		if ((Byte *)block != space) {
			prev = (void *)((Byte *)block - (block - 1)->len);
		}
		if ((Byte *)block + blockLen != space + LEN(space)) {
			next = (void *)((Byte *)block + blockLen);
		}
		if (prev && prev->isFree) {
			prevContrib = prev->len;
			RemoveFree(prev);
		}
		if (next && next->isFree) {
			nextContrib = next->len;
			RemoveFree(next);
		}
		newFree = prevContrib ? (void *)prev : (void *)block;
		SetBorders(newFree, 1, prevContrib + blockLen + nextContrib);
		AddFree(newFree);
	}

	AuditAssert(HeapAudit());
}
