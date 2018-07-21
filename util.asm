; vim: set syntax=z80:
#local

#code _CODE

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Byte add_with_carry(unsigned *res, unsigned n, unsigned m) ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_add_with_carry::
#local
	pop af
	pop de ; res
	pop hl ; n
	pop bc ; m
	push bc
	push hl
	push de
	push af

	add hl, bc
	ex de, hl
	ld (hl), e
	inc hl
	ld (hl), d

	ld l, 0
	ret nc
	inc l
	ret
#endlocal

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Byte Input16(unsigned addr) ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_Input16::
#local
	pop af
	pop bc
	push bc
	push af
	in l, (c)

	ret
#endlocal

;;;;;;;;;;;;;;;;;;;;
; void Click(void) ;
;;;;;;;;;;;;;;;;;;;;
_Click::
#local
	ld a, (_Graphics_borderColor)
	and 0x07
	ld e, a
	or 1 << 4
	ld l, a

	ld h, -1
	ld d, 1
	di
loop:
	ld a, (hl) ;timing
	ld a, (hl)
	ld b, 200
	djnz $
	ld b, 0
	djnz $

	ld a, l
	out (0xFE), a

	nop ;timing
	nop
	nop
	nop
	nop
	ld b, 198
	djnz $
	ld b, 0
	djnz $

	ld a, e
	out (0xFE), a

	ld a, d
	add a, h
	ld d, a
	jp nz, loop

	ei
	ret
#endlocal

;;;;;;;;;;;;;;;;;;;
; void Beep(void) ;
;;;;;;;;;;;;;;;;;;;
_Beep::
#local
	ld a, (_Graphics_borderColor)
	and 0x07
	ld e, a
	or 1 << 4
	ld l, a

	ld h, -1
	ld d, 50
	di
loop:
	;timing
	ld a, (hl)
	ld a, (hl)
	ld b, 0
	djnz $

	ld a, l
	out (0xFE), a

t2:
	;timing
	nop
	nop
	nop
	nop
	nop
	ld b, 254
	djnz $

	ld a, e
	out (0xFE), a

	ld a, d
	add a, h
	ld d, a
	jp nz, loop

	ei
	ret
#endlocal

;;;;;;;;;;;;;;;;;;;;;;;;;
; void *GetStackF(void) ;
;;;;;;;;;;;;;;;;;;;;;;;;;
_GetStackF::
	ld de, ix
	ex de, hl
	ret

#endlocal
