#include <stddef.h>
#include <limits.h>
#include "interrupt.h"

volatile unsigned long frame_counter;

void handle_interrupt(void)
{
	// Placeholder interrupt function, might add more to this later
	++frame_counter;
}
