#include <string.h>
#include "env.h"
#include "graphics.h"
#include "halt.h"
#include "text.h"
#include "util.h"

#include "defs.h"

void AssertFail(const char *message, const char *filename, unsigned line, Byte type)
{
	Pen        pen       = {0, 0, {0, 0, 255, 195}};

	clear_screen(ink_white | paper_blue, ink_blue);

	DrawText(&pen, "BUILD " __DATE__);
	pen.x = 0;
	++pen.y;
	if (type == AssertType_audit) {
		DrawText(&pen, "AUDIT ");
	}
	DrawText(&pen, "ASSERTION ERROR\n\n");
	DrawText(&pen, filename);
	DrawText(&pen, ":");
	PrintDecimal(&pen, line);
	pen.x = 0;
	pen.y += 2;
	DrawText(&pen, message);

	// TODO allow "press any key to continue"
	// Do not exit
	for (;;) {
		Halt();
	}
}
