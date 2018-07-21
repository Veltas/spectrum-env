; vim: set syntax=z80:

; Trim AuditAssert's from the release build
#cflags -DNAUDIT

_project_start equ 0x8000

#target BIN

#code _HEADER, _project_start
#code _GSINIT
#code _HOME
#code _CODE
#code _INITIALIZER
#data _INITIALIZED, _INITIALIZER, _INITIALIZER_size
#code _CABS, _INITIALIZER_end, 0
#code _GSFINAL, *, 0

#data _DATA
#data _DABS, *, 0
#data _RSEG, *, 0

#include "start.asm"
#include "interrupts.asm"
#include "halt.asm"
#include "handle_interrupt.c"
#include "string.asm"
#include "xarray.c"
#include "main.c"
#include "graphics.c"
#include "graphics.asm"
#include "util.asm"
#include "util.c"
#include "font.asm"
#include "text.c"
#include "text.asm"
#include "assert.c"
#include "allocator.c"
#include "keyboard.c"
#include "editor.c"

#include standard library

; Must come last
#code _GSINIT
	ret
