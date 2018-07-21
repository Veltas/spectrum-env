; vim: set syntax=z80:
	.module interrupts

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; void interrupts_init(void) ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_interrupts_init:
#local
	di
	ld a, 0x39
	ld i, a
	ld de, 0xfff4
	ld hl, ram_end_routine
	ld bc, 0x10000-0xfff4
	ldir
	im 2
	ei
	ret

interrupt_start:
	;ei
	;reti

	push af
	push bc
	push de
	push hl
	push ix
	push iy
	ex af, af'
	push af
	exx
	push bc
	push de
	push hl
	call _handle_interrupt
	pop hl
	pop de
	pop bc
	exx
	pop af
	ex af, af'
	pop iy
	pop ix
	pop hl
	pop de
	pop bc
	pop af
	ei
	reti

ram_end_routine:
	di
	jp interrupt_start
	org ram_end_routine+11
	db 0x18 ; jr opcode

#endlocal
