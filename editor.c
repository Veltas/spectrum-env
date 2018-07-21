#include <stddef.h>
#include <string.h>
#include "defs.h"
#include "graphics.h"
#include "allocator.h"
#include "text.h"
#include "keyboard.h"
#include "env.h"
#include "util.h"
#include "halt.h"
#include "xarray.h"

#include "editor.h"

#define LEN(arr) ((sizeof (arr)) / (sizeof *(arr)))

Byte Editor_mode    = Editor_insertMode,
     Editor_running = 1;

#define cursorPeriod 25
#define maxLineData 120
#define horViewScroll 20

static Editor s = {
	NULL, // lines
	0, // cursorCol
	0, // displayCol
	1, // cursorDrawn
	cursorPeriod, // cursorTimeout
	0, // cursorLine
	0, // displayLine
	{1, 0, {1, 0, 255, 21}} // pen
};

Editor *g_editorState = &s;

void Editor_Init(void)
{
	s.lines = XArray_Alloc(1, char *);
	AuditAssert(s.lines);

	s.lines[0] = XArray_Alloc(1, char);
	AuditAssert(s.lines[0]);
	strcpy(s.lines[0], "");
}

static void ClearEditorDisplay(void)
{
	Byte *display, *end;

	memset(g_displayFile, 0, LEN(g_displayFile)*2/3);
	memset(g_displayAttr, paper_white | ink_black, 22*32);

	display = g_displayFile + LEN(g_displayFile)*2/3;
	end = g_displayFile + LEN(g_displayFile);
	for (; display != end; display += 256) {
		memset(display, 0, 6*32);
	}
}

// Returns current horizontal pixel location of cursor (can go off right of
// screen, for measuring when to scroll)
static size_t GetCursorPos(void)
{
	char **line;

	line = s.lines + s.cursorLine;
	return s.pen.drawArea.x1 + MeasureTextLength(*line + s.displayCol, s.cursorCol - s.displayCol);
}

static void XorCursor(void)
{
	unsigned strLength, cursorPos[2], cursorBitmap;
	Byte *display, *end;
	char *displayStr;

	displayStr = s.lines[s.displayLine] + s.displayCol;
	strLength = XArray_Len(s.lines[s.displayLine]) - s.displayCol - 1;
	cursorPos[0] = GetCursorPos();
	cursorPos[1] = s.pen.drawArea.y1 + s.cursorLine - s.displayLine;
	cursorBitmap = GetDisplayMask(cursorPos[0]);
	display = GetDisplay(cursorPos[0], 8*cursorPos[1]);
	end = display + 256*8;
	for (; display != end; display += 256) {
		*display ^= cursorBitmap;
	}
}

void Editor_RedrawAll(void)
{
	size_t i;

	ClearEditorDisplay();
	for (i = s.displayLine; i < XArray_Len(s.lines) && i <= s.displayLine + s.pen.drawArea.y2 - s.pen.drawArea.y1; ++i) {
		s.pen.x = s.pen.drawArea.x1;
		s.pen.y = s.pen.drawArea.y1 + i - s.displayLine;
		if (i == s.cursorLine) {
			DrawTextLine(&s.pen, s.lines[i] + s.displayCol);
		} else {
			DrawTextLine(&s.pen, s.lines[i]);
		}
	}

	if (s.cursorDrawn) {
		XorCursor();
	}
}

// Removes pixels of rest of line starting from current cursor position
static void ScrubFromCursor(void)
{
	Byte *display, *end, vLine, scrubPos, mask;

	vLine = s.cursorLine - s.displayLine;
	scrubPos = GetCursorPos();

	display = GetDisplay(scrubPos, 8*vLine);
	end = display + 256*8;
	mask = ~(2*GetDisplayMask(scrubPos) - 1u);
	for (; display != end; display += 256) {
		*display &= mask;
	}

	display = GetDisplay(scrubPos, 8*vLine) + 1;
	end = display + 256*8;
	for (; display != end; display += 256) {
		memset(display, 0, 31 - scrubPos/8);
	}
}

static void DrawFromCursor(void)
{
	char **line;

	line = s.lines + s.cursorLine;
	s.pen.y = s.pen.drawArea.y1 + s.cursorLine - s.displayLine;
	s.pen.x = GetCursorPos();
	DrawTextLine(&s.pen, *line + s.cursorCol);
}

// Zeros the cursor line and redraws the text in it
static void RedrawActiveLine(void)
{
	Byte *display, *end, vLine;

	vLine = s.cursorLine - s.displayLine;
	display = GetDisplay(0, 8*vLine);
	end = display + 256*8;

	for (; display != end; display += 256) {
		__builtin_memset(display, 0, 32);
	}

	s.pen.x = s.pen.drawArea.x1;
	s.pen.y = vLine;
	DrawTextLine(&s.pen, s.lines[s.cursorLine] + s.displayCol);
}

static void HandleDel(void)
{
	char **line;

	line = s.lines + s.cursorLine;
	if (s.cursorCol > 0) {
		*line = XArray_Remove(*line, s.cursorCol - 1);
		--s.cursorCol;
		if (s.cursorCol < s.displayCol) {
			s.displayCol -= horViewScroll;
			RedrawActiveLine();
		} else {
			ScrubFromCursor();
			DrawFromCursor();
		}
		s.cursorDrawn = 1;
		s.cursorTimeout = cursorPeriod;
		XorCursor();
	} else {
		Beep();
	}
}

static void HandleLeft(void)
{
	if (s.cursorCol > 0) {
		if (s.cursorDrawn) {
			XorCursor();
		}
		--s.cursorCol;
		if (s.cursorCol < s.displayCol) {
			s.displayCol -= horViewScroll;
			RedrawActiveLine();
		}
		s.cursorDrawn = 1;
		XorCursor();
	} else {
		Beep();
	}
}

static void HandleRight(void)
{
	char **line;

	line = s.lines + s.cursorLine;

	if (s.cursorCol < XArray_Len(*line)-1) {
		if (s.cursorDrawn) {
			XorCursor();
		}
		++s.cursorCol;
		if (GetCursorPos() >= s.pen.drawArea.x2) {
			s.displayCol += horViewScroll;
			RedrawActiveLine();
		}
		s.cursorDrawn = 1;
		XorCursor();
	} else {
		Beep();
	}
}

static void ShiftDisplayDown(void)
{
	Byte *display, *line, *lineEnd, *end, i, j;

	display = g_displayFile;
	end = display + sizeof g_displayFile - 2048;
	for (; display != end; display += 2048) {
		memmove(display, display + 32, 2048);
		line = display + 7*32;
		lineEnd = line + 2048;
		for (; line != lineEnd; line += 256) {
			memcpy32(line, line + 2048 - 32*7);
		}
	}

	for (i = 0; i < 5; ++i) {
		display = g_displayFile + 2*2048 + 32*i;
		for (j = 0; j < 8; ++j) {
			memcpy32(display + 256*j, display + 32 + 256*j);
		}
	}

	display = g_displayFile + 2*2048 + 32*5;
	for (j = 0; j < 8; ++j) {
		memset(display + 256*j, 0, 32);
	}
}

static void ShiftDisplayDownFrom(size_t n)
{
	Byte *displayLine, *displayPrev, *endLine, i;

	for (i = s.pen.drawArea.y2; i-1 >= n; --i) {
		displayLine = GetDisplay(0, 8*i);
		displayPrev = GetDisplay(0, 8*(i-1));
		endLine = displayLine + 8*256;
		for (; displayLine < endLine; displayLine += 256, displayPrev += 256) {
			memcpy32(displayLine, displayPrev);
		}
	}

	displayLine = GetDisplay(0, 8*n);
	endLine = displayLine + 8*256;
	for (; displayLine < endLine; displayLine += 256) {
		memset(displayLine, 0, 32);
	}
}

static void HandleDown(void)
{
	if (s.cursorLine + 1 < XArray_Len(s.lines)) {
		if (s.cursorDrawn) {
			XorCursor();
		}
		s.cursorCol = 0;
		if (s.displayCol > 0) {
			s.displayCol = 0;
			RedrawActiveLine();
		}

		++s.cursorLine;
		s.cursorTimeout = cursorPeriod;
		if (s.cursorLine > s.displayLine + s.pen.drawArea.y2 - s.pen.drawArea.y1) {
			ShiftDisplayDown();
			++s.displayLine;
			RedrawActiveLine();
		}
		s.cursorDrawn = 1;
		XorCursor();
	} else {
		Beep();
	}
}

static void HandleUp(void)
{
	if (s.cursorLine > 0) {
		if (s.cursorDrawn) {
			XorCursor();
		}
		s.cursorCol = 0;
		if (s.displayCol > 0) {
			s.displayCol = 0;
			RedrawActiveLine();
		}

		--s.cursorLine;
		s.cursorTimeout = cursorPeriod;
		if (s.cursorLine < s.displayLine) {
			--s.displayLine;
			s.cursorDrawn = 0;
			Editor_RedrawAll();
		}
		s.cursorDrawn = 1;
		XorCursor();
	} else {
		Beep();
	}
}

static void HandleChar(KeyEvent *keyEvent)
{
	char **line;
	char c;

	line = s.lines + s.cursorLine;

	c = KeyEvent_ToChar(keyEvent);
	switch (c) {
	case 0: case '\n':
		break;
	default:
		if (XArray_Len(*line)-1 < maxLineData) {
			ScrubFromCursor();
			*line = XArray_Insert(*line, s.cursorCol);
			ReleaseAssert(*line, "Out of memory");
			(*line)[s.cursorCol] = c;
			++s.cursorCol;
			if (GetCursorPos() > s.pen.drawArea.x2) {
				s.displayCol += horViewScroll;
				RedrawActiveLine();
			} else {
				--s.cursorCol;
				DrawFromCursor();
				++s.cursorCol;
			}
			XorCursor();
			s.cursorDrawn = 1;
			s.cursorTimeout = cursorPeriod;
		} else {
			Beep();
		}
		break;
	}
}

static void HandleEnter(void)
{
	char **line;

	if (s.cursorDrawn) {
		XorCursor();
	}

	if (s.displayCol != 0) {
		s.displayCol = 0;
		RedrawActiveLine();
	}

	s.cursorCol = 0;
	s.cursorDrawn = 1;
	s.cursorTimeout = cursorPeriod;

	++s.cursorLine;
	s.lines = XArray_Insert(s.lines, s.cursorLine);
	ReleaseAssert(s.lines, "Out of memory");
	line = s.lines + s.cursorLine;
	*line = XArray_Alloc(1, char);
	ReleaseAssert(*line, "Out of memory");
	strcpy(*line, "");

	if (s.cursorLine > s.displayLine + s.pen.drawArea.y2 - s.pen.drawArea.y1) {
		ShiftDisplayDown();
		++s.displayLine;
		XorCursor();
	} else {
		ShiftDisplayDownFrom(s.cursorLine - 1 - s.displayLine + s.pen.drawArea.x1);
		XorCursor();
	}
}

void Editor_Step(void)
{
	KeyEvent *keyPress;

	if (Editor_running) switch (Editor_mode) {
	case Editor_commandMode:
		break;
	case Editor_insertMode:
		// Update cursor
		if (!--s.cursorTimeout) {
			XorCursor();
			s.cursorDrawn = !s.cursorDrawn;
			s.cursorTimeout = cursorPeriod;
		}

		// Keyboard input
		if ((keyPress = Key_GetPress())) {
			switch(keyPress->key) {
			case Key_0:
				if (keyPress->capsShift && !keyPress->symbolShift) {
					HandleDel();
				} else {
					HandleChar(keyPress);
				}
				break;
			case Key_5:
				if (keyPress->capsShift && !keyPress->symbolShift) {
					HandleLeft();
				} else {
					HandleChar(keyPress);
				}
				break;
			case Key_6:
				if (keyPress->capsShift && !keyPress->symbolShift) {
					HandleDown();
				} else {
					HandleChar(keyPress);
				}
				break;
			case Key_7:
				if (keyPress->capsShift && !keyPress->symbolShift) {
					HandleUp();
				} else {
					HandleChar(keyPress);
				}
				break;
			case Key_8:
				if (keyPress->capsShift && !keyPress->symbolShift) {
					HandleRight();
				} else {
					HandleChar(keyPress);
				}
				break;
			case Key_enter:
				if (!keyPress->capsShift && !keyPress->symbolShift) {
					HandleEnter();
				} else {
					HandleChar(keyPress);
				}
				break;
			case Key_space:
				if (keyPress->capsShift && !keyPress->symbolShift) {
					ReleaseAssert(0, "Test error screen");
				} else {
					HandleChar(keyPress);
				}
				break;
			default:
				HandleChar(keyPress);
				break;
			}
			if (!s.cursorDrawn) {
				s.cursorDrawn = 1;
				XorCursor();
			}
			s.cursorTimeout = cursorPeriod;
		}
		break;
	}
}
