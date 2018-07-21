#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include "defs.h"
#include "util.h"

#include "keyboard.h"

typedef struct {
	Byte isDown:1, isRepeat:1, timeout;
} KeyState;

// Timeout before pressed key starts to autorepeat (in frames)
#define repeatTimeout 25

// Time between autorepeat key triggers
#define repeatPeriod 1

#define LEN(arr) ((sizeof arr) / (sizeof *(arr)))

static KeyState keyStates[40];
static KeyEvent pushes[16];
static Byte     pushesStart,
                nPushes,
                autoKey = (Byte)-1;

static const unsigned halfRowAddrs[8] = {
	0x7FFEu,
	0xBFFEu,
	0xDFFEu,
	0xEFFEu,
	0xF7FEu,
	0xFBFEu,
	0xFDFEu,
	0xFEFEu
};
static const Byte halfRowMasks[8] = {
	2,
	0,
	0,
	0,
	0,
	0,
	0,
	1
};

static void PushPress(unsigned key)
{
	KeyEvent *event;

	if (nPushes < LEN(pushes)) {
		Click();
		event = pushes + (pushesStart + nPushes) % LEN(pushes);
		++nPushes;
		event->key = key;
		event->capsShift = Key_IsDown(Key_capsShift);
		event->symbolShift = Key_IsDown(Key_symbolShift);
	}
}

void ScanHalfRow(Byte i)
{
	KeyState *keyState;
	unsigned halfRowAddr, input;
	Byte halfRowMask, bit, bitN, keyStateI;

	halfRowAddr = halfRowAddrs[i];
	halfRowMask = halfRowMasks[i];

	// Get half-row keyboard state
	input = (Input16(halfRowAddr) & 0x1F) | halfRowMasks[i];

	// Test key bits
	if (input == 0x1F) {
		// Optimized case when all keys are up on the half-row, the most
		// common situation.
		__builtin_memset(keyStates + 5*i, 0, 5*sizeof *keyStates);
	} else {
		for (bit = 1, bitN = 0; bit <= 16; bit <<= 1, ++bitN) {
			keyStateI = 5*i + bitN;
			keyState = keyStates + keyStateI;
			if (input & bit) {
				// Key is up
				__builtin_memset(keyState, 0, sizeof *keyState);
			} else {
				// Key is down
				unsigned key = (halfRowAddr&0xFF00) | bit;
				if (keyState->isDown) {
					if (autoKey == keyStateI) {
						if (keyState->timeout) {
							--keyState->timeout;
						} else {
							keyState->timeout = repeatPeriod;
							PushPress(key);
						}
					}
				} else {
					keyState->isDown = 1;
					keyState->timeout = repeatTimeout;
					autoKey = keyStateI;
					PushPress(key);
				}
			}
		}
	}
}

void Key_Scan(void)
{
	Byte i;
	for (i = 0; i < 8; ++i) {
		ScanHalfRow(i);
	}
}

Byte Key_IsDown(unsigned key)
{
	return !((key & 0xFF) & Input16((key & 0xFF00) | 0xFE));
}

unsigned Key_ToEnum(char character)
{
	switch (character) {
		default:   return 0;
		case '\n': return Key_enter;
		case ' ':  return Key_space;
		case '0':  return Key_0;
		case '1':  return Key_1;
		case '2':  return Key_2;
		case '3':  return Key_3;
		case '4':  return Key_4;
		case '5':  return Key_5;
		case '6':  return Key_6;
		case '7':  return Key_7;
		case '8':  return Key_8;
		case '9':  return Key_9;
		case 'a':  return Key_a;
		case 'b':  return Key_b;
		case 'c':  return Key_c;
		case 'd':  return Key_d;
		case 'e':  return Key_e;
		case 'f':  return Key_f;
		case 'g':  return Key_g;
		case 'h':  return Key_h;
		case 'i':  return Key_i;
		case 'j':  return Key_j;
		case 'k':  return Key_k;
		case 'l':  return Key_l;
		case 'm':  return Key_m;
		case 'n':  return Key_n;
		case 'o':  return Key_o;
		case 'p':  return Key_p;
		case 'q':  return Key_q;
		case 'r':  return Key_r;
		case 's':  return Key_s;
		case 't':  return Key_t;
		case 'u':  return Key_u;
		case 'v':  return Key_v;
		case 'w':  return Key_w;
		case 'x':  return Key_x;
		case 'y':  return Key_y;
		case 'z':  return Key_z;
	}
}

char Key_ToChar(unsigned enumKey)
{
	switch (enumKey) {
		default:        return 0;
		case Key_enter: return '\n';
		case Key_space: return ' ';
		case Key_0:     return '0';
		case Key_1:     return '1';
		case Key_2:     return '2';
		case Key_3:     return '3';
		case Key_4:     return '4';
		case Key_5:     return '5';
		case Key_6:     return '6';
		case Key_7:     return '7';
		case Key_8:     return '8';
		case Key_9:     return '9';
		case Key_a:     return 'a';
		case Key_b:     return 'b';
		case Key_c:     return 'c';
		case Key_d:     return 'd';
		case Key_e:     return 'e';
		case Key_f:     return 'f';
		case Key_g:     return 'g';
		case Key_h:     return 'h';
		case Key_i:     return 'i';
		case Key_j:     return 'j';
		case Key_k:     return 'k';
		case Key_l:     return 'l';
		case Key_m:     return 'm';
		case Key_n:     return 'n';
		case Key_o:     return 'o';
		case Key_p:     return 'p';
		case Key_q:     return 'q';
		case Key_r:     return 'r';
		case Key_s:     return 's';
		case Key_t:     return 't';
		case Key_u:     return 'u';
		case Key_v:     return 'v';
		case Key_w:     return 'w';
		case Key_x:     return 'x';
		case Key_y:     return 'y';
		case Key_z:     return 'z';
	}
}

KeyEvent *Key_GetPress(void)
{
	KeyEvent *result = NULL;
	if (nPushes > 0) {
		result = pushes + pushesStart;
		pushesStart = (pushesStart + 1) % LEN(pushes);
		--nPushes;
	}
	return result;
}

char KeyEvent_ToChar(const KeyEvent *keyEvent)
{
	static const char
		digitSymbolMap[10] = {
			'_',
			'!',
			'@',
			'#',
			'$',
			'%',
			'&',
			'\'',
			'(',
			')'
		},
		alphaSymbolMap[26] = {
			'~',  // a
			'*',  // b
			'?',  // c
			'\\', // d
			0,    // e
			'{',  // f
			'}',  // g
			'^',  // h
			0,    // i
			'-',  // j
			'+',  // k
			'=',  // l
			'.',  // m
			',',  // n
			';',  // o
			'"',  // p
			0,    // q
			'<',  // r
			'|',  // s
			'>',  // t
			']',  // u
			'/',  // v
			0,    // w
			0x60, // x
			'[',  // y
			':'   // z
		};

	char result;
	Byte capsShift, symbolShift;

	result = Key_ToChar(keyEvent->key);
	capsShift = keyEvent->capsShift;
	symbolShift = keyEvent->symbolShift;

	if (!capsShift && !symbolShift) {
	} else if (capsShift && !symbolShift) {
		if (isalpha(result)) {
			result = toupper(result);
		} else {
			result = 0;
		}
	} else if (!capsShift && symbolShift) {
		if (isalpha(result)) {
			result = alphaSymbolMap[result - 'a'];
		} else if (isdigit(result)) {
			result = digitSymbolMap[result - '0'];
		} else {
			result = 0;
		}
	} else { // capsShift && symbolShift
		if (result == 'p') {
			result = 0x7F;
		} else {
			result = 0;
		}
	}

	return result;
}
