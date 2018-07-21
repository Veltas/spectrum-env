#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include "defs.h"

typedef struct {
	Byte x1, y1, x2, y2;
} U8Rect;

enum {
	ink_black     = 00,
	ink_blue      = 01,
	ink_red       = 02,
	ink_magenta   = 03,
	ink_green     = 04,
	ink_cyan      = 05,
	ink_yellow    = 06,
	ink_white     = 07,
	paper_black   = 000,
	paper_blue    = 010,
	paper_red     = 020,
	paper_magenta = 030,
	paper_green   = 040,
	paper_cyan    = 050,
	paper_yellow  = 060,
	paper_white   = 070,
	attr_bright   = 1<<6,
	attr_flashing = 1<<7
};

extern Byte Graphics_borderColor;

void
clear_screen(unsigned char color_attr, unsigned char border_color);

void
plot_point(unsigned char x, unsigned char y);

void
plot_line(
	unsigned char x1,
	unsigned char y1,
	unsigned char x2,
	unsigned char y2
);

// Given a horizontal and vertical coordinate, returns address of byte in
// display file.
Byte *GetDisplay(Byte x, Byte y);

// Given a horizontal coordinate, returns byte with bit representing that
// location.
Byte GetDisplayMask(Byte x);

extern Byte BitmapBits[8];

#endif // GRAPHICS_H_INCLUDED
