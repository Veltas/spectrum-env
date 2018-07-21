#include "util.h"

void PrintDecimal(Pen *pen, unsigned num)
{
	char     print[2] = {0};
	unsigned unit     = 10000;
	if (!num) {
		print[0] = '0';
		DrawText(pen, print);
	} else {
		while (!(num/unit)) unit /= 10;
		for (; unit; unit /= 10) {
			unsigned remove = num/unit;
			print[0] = '0' + remove;
			DrawText(pen, print);
			num -= remove*unit;
		}
	}
}
