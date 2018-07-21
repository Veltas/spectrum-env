#include <stddef.h>
#include "defs.h"

#include "text.h"

typedef struct {
	Byte width,
	     bitmap[7];
} FontGlyph;

extern const FontGlyph g_font[96];

#define GetGlyphData(n) (g_font + ((n)-32))

const char *DrawTextLine(Pen *pen, const char *text)
{
	const char *result = NULL;
	for (; *text; ++text) {
		if (*text == '\n') {
			pen->x = pen->drawArea.x1;
			++pen->y;
		} else if (DrawGlyph(pen, *text)) {
			result = text;
			break;
		}
	}
	return result;
}

const char *DrawText(Pen *pen, const char *text)
{
	while (text && pen->y <= pen->drawArea.y2) {
		const char *advance = DrawTextLine(pen, text);
		if (advance == text) {
			pen->x = pen->drawArea.x1;
			++pen->y;
		}
		text = advance;
	}
	return text;
}

Byte DrawTextChar(Pen *pen, char c)
{
	static char str[] = "a";
	str[0] = c;
	return !DrawText(pen, str);
}

Byte MeasureTextCharLength(char c)
{
	return GetGlyphData(c)->width;
}
