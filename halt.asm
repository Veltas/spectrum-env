; vim: set syntax=z80:
	.module halt_asm
	.area _CODE

;;;;;;;;;;;;;;;;;;;
; void Halt(void) ;
;;;;;;;;;;;;;;;;;;;
_Halt:
#local
	halt
	ret
#endlocal
