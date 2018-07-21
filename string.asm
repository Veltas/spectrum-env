; vim: set syntax=z80:
#local

#data _DATA
sp_store:
	ds 2
dest_store:
	ds 2
src_store:
	ds 2

#code _CODE

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; void *memset(void *s, int c, size_t n) ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_memset::
#local
	; store initial sp
	ld (sp_store), sp

	; critical section
	di

	; hl = $s
	; de = $c
	; bc = $n
	pop af
	pop hl
	pop de
	pop bc

	; rest of function assumes even number
	bit 0, c
	jr z, odd_skip
		ld (hl), e
		inc hl
		dec bc
odd_skip:
	
	; handle 0 case
	xor a
	cp c
	jr nz, zero_skip
	cp b
	jr z, end
zero_skip:

	; sp = $s + n
	add hl, bc
	ld sp, hl

	; de contains word to write
	ld d, e

	; store $n/32*32 for main loop counter
	ld a, 11100000b
	and c
	ld l, a
	ld h, b
	push hl

	; bc = $n%32/2
	ld a, 00011111b
	and c
	rra
	ld c, a
	xor a
	ld b, a

	; iy = write_loop + 16 - $n%32/2
	ld hl, write_loop+16
	sbc hl, bc
	ex de, hl
	ld iyl, e
	ld iyh, d
	ex de, hl

	; restore hl as main counter
	pop hl

	; set bc as decrement
	ld bc, -32

	; goto (iy)
	jp (iy)

write_loop:
		.rept 16
		push de
		.endm

		; decrement and loop check
		add hl, bc
		jp c, write_loop

end:
	; restore stack
	ld sp, (sp_store)

	; end critical section
	ei

	; return s
	pop af
	pop hl
	push hl
	push af
	ret
#endlocal

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; void *memmove(void *dest, const void *src, size_t n) ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_memmove::
#local
	; de = $dest
	; hl = $src
	; bc = $n
	pop af
	pop de
	pop hl
	pop bc
	push bc
	push hl
	push de
	push af

	push hl

	xor a
	sbc hl, de

	pop hl

	jr nc, memcpy_asc_fastcall
	jp memcpy_des_fastcall
#endlocal

; Copies 32 bytes quickly
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; void *memcpy32(void *dest, const void *src) ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#code _CODE
#local
_memcpy32::
	pop af
	pop de
	pop hl
	push hl
	push de
	push af

memcpy32_fastcall::
	; return value
	push de

	.rept 32
	ldi
	.endm

	pop hl
	ret
#endlocal

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; void *memcpy(void *dest, const void *src, size_t n) ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#code _CODE
#local
_memcpy::
memcpy_asc::
	pop af
	pop de
	pop hl
	pop bc
	push bc
	push hl
	push de
	push af
memcpy_fastcall::
memcpy_asc_fastcall::
	; store return value
	push de

	; iy = loop + (256-2*n)%256
	xor a
	sub a, c
	add a, a
	ld iyh, loop >> 8
	ld iyl, a

	ld a, 0

	; if (256-2*n)%256 == 0, jump to end first
	jp z, ldi_skip
	jp (iy)

	.align 256
loop:
	; perform copies
	.rept 128
	ldi
	.endm
ldi_skip:
	; loop check
	cp b
	jp nz, loop
	cp c
	jp nz, loop

	; return $dest
	pop hl
	ret
#endlocal

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; void *memcpy_des(void *dest, const void *src, size_t n) ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
_memcpy_des::
	; de = $dest
	; hl = $src
	; bc = $n
	pop af
	pop de
	pop hl
	pop bc
	push bc
	push hl
	push de
	push af
memcpy_des_fastcall::
#local
	; add $n-1 to hl and de
	add hl, bc
	dec hl
	ex de, hl
	add hl, bc
	dec hl
	ex de, hl

	; store n
	push bc

	; iy = write_loop + 32*2 - (n%32)*2
	push hl
	ld hl, write_loop+64
	ld a, 00011111b
	and c
	add a, a
	ld c, a
	xor a
	ld b, a
	sbc hl, bc
	ex de, hl
	ld iy, de
	ex de, hl
	pop hl

	; retrieve n
	pop bc

	; goto (iy)
	jp (iy)

write_loop:
		.rept 32
		ldd
		.endm

		; loop check
		cp c
		jr nz, write_loop
		cp b
		jr nz, write_loop

end:

	; return s
	inc de
	ex de, hl
	ret
#endlocal

#endlocal
