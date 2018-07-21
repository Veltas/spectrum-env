#include "env.h"
#include <string.h>

#include "graphics.h"

Byte Graphics_borderColor;

void
clear_screen(unsigned char color_attr, unsigned char border_color)
{
	memset(g_displayFile, 0, sizeof g_displayFile);
	memset(g_displayAttr, color_attr, sizeof g_displayAttr);
	Graphics_borderColor = border_color;
	g_ioPort = Graphics_borderColor % 010;
}
