; vim: set syntax=z80:

#code _HEADER
	; complain if this isn't first
	.org _project_start
_init:
#local
	; Disable ROM interrupt handler
	di
	; Place stack at RAM end (before interrupt catch)
	ld hl, 0xFFF4
	ld sp, hl
	; Initialize _DATA section
	ld hl, _DATA
	ld (hl), 0
	ld de, _DATA+1
	ld bc, _DATA_size-1
	ldir
	; Enable our interrupt handler and init allocator
	call _interrupts_init
	call _AllocInit
	; GSINIT()
	call _GSINIT
	; init other stuff
	ld bc, 56 | (7 << 8)
	push bc
	call _clear_screen
	pop bc
	call _Editor_Init
	call _Editor_RedrawAll
	; main()
	call _main
	; fflush(NULL)
	;ld bc, 0
	;push bc
	;call _fflush
	;pop bc
	; do not exit
	jr $
#endlocal
