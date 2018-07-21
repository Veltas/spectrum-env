; vim: set syntax=z80:
#local

#code _CODE
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Byte DrawGlyph(Pen *pen, char glyph) ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_DrawGlyph::
#local
	; A  = $glyph
	; IY = $pen
	pop bc
	pop iy
	dec sp
	pop af
	push af
	inc sp
	push iy
	push bc

	; store font record address
	add a, a
	add a, a
	ld d, 0
	rl d
	add a, a
	rl d
	ld e, a
	ld hl, _g_font-32*8
	add hl, de
	push hl

	; check font width
	ld e, (iy+0) ; x
	ld a, (iy+4) ; x boundary
	sub e
	jr c, out_of_room
	sub (hl) ; width
	jr c, out_of_room

	; update adjust_jump with correct jump address
	ld a, e
	and 111b
	add a, a
	add a, a
	ld c, a
	ld b, 0
	ld hl, adjust_stage + 28
	sbc hl, bc
	ld (adjust_jump+1), hl

	; DE = first write address
	ld a, (iy+1) ; y
	add a, a
	ld l, a
	ld h, 0
	ld bc, glyphline_table
	add hl, bc
	ld e, (hl)
	inc hl
	ld d, (hl)
	ld a, (iy+0) ; x
	ld b, a
	and 0xF8
	rrca
	rrca
	rrca
	ld l, a
	ld h, 0
	add hl, de
	ex de, hl

	; HL = first font bitmap address
	pop hl
	; update stored x position
	ld a, b
	add a, (hl)
	ld (iy+0), a
	inc hl

	; CF = 0
	xor a

	; B = 7, C = 0
	ld b, 7
	ld c, a
draw_loop:
	push bc

	; B = glyph entry to copy, C = 0
	ld b, (hl)
	ld c, 0

	; Adjust so B is first cell to write, C is second cell
adjust_jump:
	jp 0x0000
adjust_stage:
	rr b
	rr c
	rr b
	rr c
	rr b
	rr c
	rr b
	rr c
	rr b
	rr c
	rr b
	rr c
	rr b
	rr c

	inc hl
	ex de, hl

	; Write first cell
	ld a, b
	or (hl)
	ld (hl), a

	; Write second cell
	inc l
	ld a, c
	or (hl)
	ld (hl), a

	; Next write address
	dec l
	inc h
	ex de, hl

	; Loop
	pop bc
	djnz draw_loop

	; Done
	ld l, c
	ret

out_of_room:
	; Return glyph 'width'
	pop hl
	ld l, (hl)
	ret

glyphline_table:
	dw 0x4100
	dw 0x4120
	dw 0x4140
	dw 0x4160
	dw 0x4180
	dw 0x41A0
	dw 0x41C0
	dw 0x41E0
	dw 0x4900
	dw 0x4920
	dw 0x4940
	dw 0x4960
	dw 0x4980
	dw 0x49A0
	dw 0x49C0
	dw 0x49E0
	dw 0x5100
	dw 0x5120
	dw 0x5140
	dw 0x5160
	dw 0x5180
	dw 0x51A0
	dw 0x51C0
	dw 0x51E0
#endlocal

#code _CODE
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; size_t MeasureTextLength(const char *text, size_t nChars) ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_MeasureTextLength::
#local
	pop af
	pop bc ; bc = $text
	pop hl ; hl = $nChars
	push hl
	push bc
	push af

	; return zero if $nChars is zero
	xor a
	cp l
	jp nz, not_zero
	cp h
	ret z
not_zero:

	; otherwise calculate end_char_ld value to use
	add hl, bc
	ex de, hl
	xor a
	ld l, a
	ld h, a
	sbc hl, de
	ld (end_char_ld+1), hl

	; total starts at zero
	ld iy, 0

loop:
	; read character
	ld a, (bc)

	; locate font record
	add a, a
	add a, a
	ld d, 0
	rl d
	add a, a
	rl d
	ld e, a
	ld hl, _g_font-32*8
	add hl, de

	; read width and add to total
	ld e, (hl)
	ld d, 0
	add iy, de

	; increment string address, loop if not end
	inc bc
end_char_ld:
	ld hl, 0xBEEF
	add hl, bc
	jp nc, loop

	; return total
	push iy
	pop hl
	ret
#endlocal

#endlocal
