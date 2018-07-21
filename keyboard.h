#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include "defs.h"

typedef struct {
	unsigned key;
	Byte capsShift, symbolShift;
} KeyEvent;

// High byte: msb of input address for half-row
// Low byte: test bit for key in half-row
enum {
	Key_a = (0xFDu << 8) | 1,
	Key_b = (0x7Fu << 8) | 16,
	Key_c = (0xFEu << 8) | 8,
	Key_d = (0xFDu << 8) | 4,
	Key_e = (0xFBu << 8) | 4,
	Key_f = (0xFDu << 8) | 8,
	Key_g = (0xFDu << 8) | 16,
	Key_h = (0xBFu << 8) | 16,
	Key_i = (0xDFu << 8) | 4,
	Key_j = (0xBFu << 8) | 8,
	Key_k = (0xBFu << 8) | 4,
	Key_l = (0xBFu << 8) | 2,
	Key_m = (0x7Fu << 8) | 4,
	Key_n = (0x7Fu << 8) | 8,
	Key_o = (0xDFu << 8) | 2,
	Key_p = (0xDFu << 8) | 1,
	Key_q = (0xFBu << 8) | 1,
	Key_r = (0xFBu << 8) | 8,
	Key_s = (0xFDu << 8) | 2,
	Key_t = (0xFBu << 8) | 16,
	Key_u = (0xDFu << 8) | 8,
	Key_v = (0xFEu << 8) | 16,
	Key_w = (0xFBu << 8) | 2,
	Key_x = (0xFEu << 8) | 4,
	Key_y = (0xDFu << 8) | 16,
	Key_z = (0xFEu << 8) | 2,
	Key_0 = (0xEFu << 8) | 1,
	Key_1 = (0xF7u << 8) | 1,
	Key_2 = (0xF7u << 8) | 2,
	Key_3 = (0xF7u << 8) | 4,
	Key_4 = (0xF7u << 8) | 8,
	Key_5 = (0xF7u << 8) | 16,
	Key_6 = (0xEFu << 8) | 16,
	Key_7 = (0xEFu << 8) | 8,
	Key_8 = (0xEFu << 8) | 4,
	Key_9 = (0xEFu << 8) | 2,
	Key_capsShift = (0xFEu << 8) | 1,
	Key_symbolShift = (0x7Fu << 8) | 2,
	Key_space = (0x7Fu << 8) | 1,
	Key_enter = (0xBFu << 8) | 1
};

// Called once per frame, scans keyboard and updates driver key press info
void Key_Scan(void);

// Returns whether a given key is down or not
Byte Key_IsDown(unsigned key);

// Convert character in 'a'-'z', '0'-'9', ' ' or '\n' to a corresponding key
// enumerator. Returns 0 if not recognised.
unsigned Key_ToEnum(char character);

// Convert any key enumerator (except Key_capsShift or Key_symbolShift) to
// representative character.
char Key_ToChar(unsigned enumKey);

// Returns next press in key event queue, or null pointer if no presses are
// queued. Returned pointer is valid until next Key_Scan (usually on next
// frame). Will not generate separate events for caps and symbol shift keys.
KeyEvent *Key_GetPress(void);

// Converts a key event to a representative character, if any. Else returns 0.
char KeyEvent_ToChar(const KeyEvent *keyEvent);

#endif // KEYBOARD_H_INCLUDED
