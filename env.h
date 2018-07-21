#ifndef ENV_H_INCLUDED
#define ENV_H_INCLUDED

__sfr __at 0xFE g_ioPort;

// font_bitmap[c] is the bitmap of character c for printable c
__at(15360) volatile unsigned char g_fontBitmaps[128][8];

__at(16384) volatile unsigned char g_displayFile[32*24*8];
__at(22528) volatile unsigned char g_displayAttr[32*24];

#endif // ENV_H_INCLUDED
