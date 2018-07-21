; vim: set syntax=z80:
#local

#code _CODE

; Stores corresponding addresses of scanlines
	.align 512
scanline_table:
	dw 0x4000
	dw 0x4100
	dw 0x4200
	dw 0x4300
	dw 0x4400
	dw 0x4500
	dw 0x4600
	dw 0x4700
	dw 0x4020
	dw 0x4120
	dw 0x4220
	dw 0x4320
	dw 0x4420
	dw 0x4520
	dw 0x4620
	dw 0x4720
	dw 0x4040
	dw 0x4140
	dw 0x4240
	dw 0x4340
	dw 0x4440
	dw 0x4540
	dw 0x4640
	dw 0x4740
	dw 0x4060
	dw 0x4160
	dw 0x4260
	dw 0x4360
	dw 0x4460
	dw 0x4560
	dw 0x4660
	dw 0x4760
	dw 0x4080
	dw 0x4180
	dw 0x4280
	dw 0x4380
	dw 0x4480
	dw 0x4580
	dw 0x4680
	dw 0x4780
	dw 0x40A0
	dw 0x41A0
	dw 0x42A0
	dw 0x43A0
	dw 0x44A0
	dw 0x45A0
	dw 0x46A0
	dw 0x47A0
	dw 0x40C0
	dw 0x41C0
	dw 0x42C0
	dw 0x43C0
	dw 0x44C0
	dw 0x45C0
	dw 0x46C0
	dw 0x47C0
	dw 0x40E0
	dw 0x41E0
	dw 0x42E0
	dw 0x43E0
	dw 0x44E0
	dw 0x45E0
	dw 0x46E0
	dw 0x47E0
	dw 0x4800
	dw 0x4900
	dw 0x4A00
	dw 0x4B00
	dw 0x4C00
	dw 0x4D00
	dw 0x4E00
	dw 0x4F00
	dw 0x4820
	dw 0x4920
	dw 0x4A20
	dw 0x4B20
	dw 0x4C20
	dw 0x4D20
	dw 0x4E20
	dw 0x4F20
	dw 0x4840
	dw 0x4940
	dw 0x4A40
	dw 0x4B40
	dw 0x4C40
	dw 0x4D40
	dw 0x4E40
	dw 0x4F40
	dw 0x4860
	dw 0x4960
	dw 0x4A60
	dw 0x4B60
	dw 0x4C60
	dw 0x4D60
	dw 0x4E60
	dw 0x4F60
	dw 0x4880
	dw 0x4980
	dw 0x4A80
	dw 0x4B80
	dw 0x4C80
	dw 0x4D80
	dw 0x4E80
	dw 0x4F80
	dw 0x48A0
	dw 0x49A0
	dw 0x4AA0
	dw 0x4BA0
	dw 0x4CA0
	dw 0x4DA0
	dw 0x4EA0
	dw 0x4FA0
	dw 0x48C0
	dw 0x49C0
	dw 0x4AC0
	dw 0x4BC0
	dw 0x4CC0
	dw 0x4DC0
	dw 0x4EC0
	dw 0x4FC0
	dw 0x48E0
	dw 0x49E0
	dw 0x4AE0
	dw 0x4BE0
	dw 0x4CE0
	dw 0x4DE0
	dw 0x4EE0
	dw 0x4FE0
	dw 0x5000
	dw 0x5100
	dw 0x5200
	dw 0x5300
	dw 0x5400
	dw 0x5500
	dw 0x5600
	dw 0x5700
	dw 0x5020
	dw 0x5120
	dw 0x5220
	dw 0x5320
	dw 0x5420
	dw 0x5520
	dw 0x5620
	dw 0x5720
	dw 0x5040
	dw 0x5140
	dw 0x5240
	dw 0x5340
	dw 0x5440
	dw 0x5540
	dw 0x5640
	dw 0x5740
	dw 0x5060
	dw 0x5160
	dw 0x5260
	dw 0x5360
	dw 0x5460
	dw 0x5560
	dw 0x5660
	dw 0x5760
	dw 0x5080
	dw 0x5180
	dw 0x5280
	dw 0x5380
	dw 0x5480
	dw 0x5580
	dw 0x5680
	dw 0x5780
	dw 0x50A0
	dw 0x51A0
	dw 0x52A0
	dw 0x53A0
	dw 0x54A0
	dw 0x55A0
	dw 0x56A0
	dw 0x57A0
	dw 0x50C0
	dw 0x51C0
	dw 0x52C0
	dw 0x53C0
	dw 0x54C0
	dw 0x55C0
	dw 0x56C0
	dw 0x57C0
	dw 0x50E0
	dw 0x51E0
	dw 0x52E0
	dw 0x53E0
	dw 0x54E0
	dw 0x55E0
	dw 0x56E0
	dw 0x57E0

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; void plot_point(unsigned char x, unsigned char y) ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#local
_plot_point::
	pop af
	pop bc
	push bc
	push af

_plot_point_fastcall::
	; load scanline address
	ld l, b
	ld h, scanline_table >> 9
	add hl, hl
	ld e, (hl)
	inc hl
	ld d, (hl)

	; horizontal offset
	ld a, c
	and 0xF8
	rrca
	rrca
	rrca
	or e
	ld e, a

	; load a with bit to set
	ld h, _BitmapBits >> 8
	ld a, c
	and 0x07
	ld l, a
	ld a, (hl)

	; write bit
	ex de, hl
	or (hl)
	ld (hl), a

	ret
#endlocal

	.align 256

_BitmapBits::
	db 0x80
	db 0x40
	db 0x20
	db 0x10
	db 0x08
	db 0x04
	db 0x02
	db 0x01

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; void plot_line(byte x1, byte y1, byte x2, byte y2) ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Bresenham's Algorithm
_plot_line:
#local
	; l = x1, h = y1, e = x2, d = y2
	pop af
	pop hl
	pop de
	push de
	push hl
	push af

	push ix
	ld ix, 0
	add ix, sp

	; ensure vectors are in left-to-right order
	ld a, e
	sub l
	jr nc, correct_order
		ex de, hl
		neg
correct_order:
	push hl
	ld b, a

	; if y1 > y2
	ld a, d
	sub h
	jr c, negative_gradient
		; non-negative gradient
		; store dx, dy
		ld c, a
		push bc

		cp b
		jr nc, dy_ge_1
			; dx > dy
			; TODO

dy_ge_1:
			; dy >= dx
			; store 2dx-2dy, 2dx
			ld a, b
			sub c
			add a, a
			ld c, a
			ld a, b
			add a, a
			ld b, a
			push bc

			; store decision variable, loop counter
			ld c, (ix-4)
			sub c
			ld b, a
			dec c
			push bc

			; draw first pixel
			ld c, l
			ld b, h
			call _plot_point_fastcall

cont2:
				; check decision variable
				ld a, (ix-7)
				add a, a
				jr nc, decision_ge_zero2
					; p < 0
					; plot_point(x, ++y)
					ld c, (ix-2)
					ld b, (ix-1)
					inc b
					ld (ix-1), b
					call _plot_point_fastcall

					; p += 2dx
					ld a, (ix-7)
					add a, (ix-6)
					ld (ix-7), a

					jp decision_end2
decision_ge_zero2:
					; pk >= 0
					; plot_point(++x, ++y)
					ld c, (ix-2)
					inc c
					ld (ix-2), c
					ld b, (ix-1)
					inc b
					ld (ix-1), b
					call _plot_point_fastcall

					; p += 2dx - 2dy
					ld a, (ix-7)
					add a, (ix-5)
					ld (ix-7), a
decision_end2:

				dec (ix-8)
				jr nz, cont2

			ld sp, ix
			pop ix
			ret

negative_gradient:
		; negative gradient
		; store dx, dy
		neg
		ld c, a
		push bc

		; TODO
#endlocal

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Byte *GetDisplay(Byte x, Byte y) ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#local
_GetDisplay::
	pop af
	pop bc ; b = $y, c = $x
	push bc
	push af

	; load scanline address
	ld l, b
	ld h, scanline_table >> 9
	add hl, hl
	ld e, (hl)
	inc hl
	ld d, (hl)

	; horizontal offset
	ld a, c
	and 0xF8
	rrca
	rrca
	rrca
	or e
	ld e, a

	ex de, hl

	ret
#endlocal

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Byte GetDisplayMask(Byte x) ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
#local
_GetDisplayMask::
	pop af
	dec sp
	pop bc ; b = $x
	push bc
	inc sp
	push af

	ld h, _BitmapBits >> 8
	ld a, b
	and 0x07
	ld l, a
	ld l, (hl)

	ret
#endlocal

#endlocal
