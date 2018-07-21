#ifndef ZAPP_TEXT_H_INCLUDED
#define ZAPP_TEXT_H_INCLUDED

#include <stddef.h>

#include "defs.h"
#include "graphics.h"

// Represents context for some rendering routines. y-direction sizes/coords are
// text rows, not pixel rows.
typedef struct {
	Byte   x, y;
	U8Rect drawArea;
} Pen;

// Attempt to render a glyph to the display file, at pen's position. The glyph
// will not be rendered if there is not enough room to draw the entire glyph
// from the pen's position. If the glyph is rendered the pen is updated to
// follow the glyph.
// Param pen[in,out]: Pen to render with.
// Param glyph[in]: The glyph to render. isprint((byte)glyph) must be non-zero.
// Return: If the glyph is rendered returns 0. If the glyph fails to render,
//         returns the width of the glyph + 1 in pixels.
Byte DrawGlyph(
	Pen  *pen,
	char glyph
);

// Renders as much text as possible to the screen before reaching the draw area
// boundary. The pen is updated to follow the end of the rendered text, if any
// is drawn.
// Param pen[in,out]: Pen to render with.
// Param text[in]: The text to render. Each character must return non-zero from
//                 isprint().
// Return: If all text is rendered, returns a null pointer. Otherwise, returns
//         the pointer to the first character that was not rendered.
const char *DrawTextLine(
	Pen        *pen,
	const char *text
);

// Renders as much text as possible, wrapping lines until draw area is
// exhausted.
// Returns: null pointer if all text rendered, or pointer to first character not
// rendered.
const char *DrawText(
	Pen        *pen, // Pen to render with.
	const char *text // Text to render. Each character must return non-zero
	                 // from isprint().
);

// Renders character if space, returns 0 if failed to render, 1 otherwise.
Byte DrawTextChar(
	Pen  *pen, // Pen to render with.
	char c     // Text character to render. Must return non-zero from
	           // isprint().
);

// Calculates the displacement length that would result from trying to render
// the first nChars characters from the text string.
size_t MeasureTextLength(
	const char *text,
	size_t     nChars
);

// Gets displacement length of a single character, equiv to
// (Byte)MeasureTextLength((char[]){c, 0}, 1);
Byte MeasureTextCharLength(
	char c
);

#endif // ZAPP_TEXT_H_INCLUDED
