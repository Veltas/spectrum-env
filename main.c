#include <stddef.h>
#include <string.h>
#include "halt.h"
#include "allocator.h"
#include "defs.h"
#include "text.h"
#include "env.h"
#include "graphics.h"
#include "keyboard.h"
#include "util.h"
#include "editor.h"

static void PaintSeparator(void)
{
	int i = 0;
	for (; i < 4; ++i) {
		Byte *line = g_displayFile + 4096 + 6*32 + 2*256 + i*256;
		if (i >= 1 && i <= 2) {
			__builtin_memset(line, 0xFF, 23);
			line[24] = 0x80;
			line[29] = 0x01;
		} else {
			memset(line, 0xFF, 32);
		}
		line[23] = 0xFC;
		line[30] = 0x3F;
		line[31] = 0xFF;
	}
}

// val in [0, 46]
static void PaintSeparatorBar(Byte val)
{
	Byte *line = g_displayFile + 4096 + 6*32 + 3*256,
	     solid = (val+1)/8;
	line[24] = 0x80;
	__builtin_memset(line+25, 0x00, 4);
	__builtin_memset(g_displayAttr + 22*32 + 24,
	                 (val > 30 ? ink_red : ink_blue) | paper_white,
	                 6);
	line[29] = 0x01;
	memset(line+24, 0xFF, solid);
	if ((val+1)%8 != 0) {
		line[24+solid] |= 0xFF << (8 - (val+1)%8);
	}
	__builtin_memcpy(line+256+24, line+24, 6);
}

void main(void)
{
	void *frame;
	Byte allocUse = (Byte)-1, newUse;
	size_t allocUseFull = (size_t)-1;
	//volatile Byte waitI;
	Pen mainPen = {0, 23, {0, 0, 255, 23}};

	frame = GetStackF();

	PaintSeparator();
	PaintSeparatorBar(0);
	DrawTextLine(&mainPen, "BREAK: leave edit mode");

	mainPen.x = 0; mainPen.y = 0;
	for (;; Halt()) {
		// wait a bit to sync line
		/*
		for (waitI = 0; waitI < 120; ++waitI);
		g_ioPort = ink_black;
		*/

		AuditAssert(frame == GetStackF());

		//g_ioPort = ink_magenta;
		// Perform keyboard driver scan
		Key_Scan();

		//g_ioPort = ink_yellow;

		// Update alloc bar on demand
		if (allocUseFull != g_totalAllocated) {
			allocUseFull = g_totalAllocated;
			newUse = AllocUsage();
			if (newUse != allocUse) {
				allocUse = newUse;
				PaintSeparatorBar((47*allocUse)>>8);
			}
		}

		//g_ioPort = ink_blue;
		// Update editor state
		Editor_Step();

		// End border timing
		//g_ioPort = Graphics_borderColor % 010;
	}
}
