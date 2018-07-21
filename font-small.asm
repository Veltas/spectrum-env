; vim: set syntax=z80:

	.module font_file
	.area _CODE

#data _INITIALIZED
	ds 96*8

#code _INITIALIZER
_g_font:
	; space
	db 3
	db 00000000b
	db 00000000b
	db 00000000b
	db 00000000b
	db 00000000b
	db 00000000b
	db 00000000b
	; !
	db 2
	db 10000000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 00000000b
	db 10000000b
	db 00000000b
	; "
	db 4
	db 10100000b
	db 10100000b
	db 00000000b
	db 00000000b
	db 00000000b
	db 00000000b
	db 00000000b
	; #
	db 6
	db 00000000b
	db 01010000b
	db 11111000b
	db 01010000b
	db 11111000b
	db 01010000b
	db 00000000b
	; $
	db 6
	db 00100000b
	db 01111000b
	db 10100000b
	db 01110000b
	db 00101000b
	db 11110000b
	db 00100000b
	; %
	db 6
	db 00000000b
	db 00000000b
	db 10010000b
	db 00100000b
	db 01000000b
	db 10010000b
	db 00000000b
	; &
	db 5
	db 01000000b
	db 10100000b
	db 10000000b
	db 01010000b
	db 10100000b
	db 01010000b
	db 00000000b
	; '
	db 2
	db 10000000b
	db 10000000b
	db 00000000b
	db 00000000b
	db 00000000b
	db 00000000b
	db 00000000b
	; (
	db 3
	db 01000000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 01000000b
	; )
	db 3
	db 10000000b
	db 01000000b
	db 01000000b
	db 01000000b
	db 01000000b
	db 01000000b
	db 10000000b
	; *
	db 4
	db 00000000b
	db 10100000b
	db 01000000b
	db 10100000b
	db 00000000b
	db 00000000b
	db 00000000b
	; +
	db 4
	db 00000000b
	db 00000000b
	db 01000000b
	db 11100000b
	db 01000000b
	db 00000000b
	db 00000000b
	; ,
	db 2
	db 00000000b
	db 00000000b
	db 00000000b
	db 00000000b
	db 00000000b
	db 10000000b
	db 10000000b
	; -
	db 4
	db 00000000b
	db 00000000b
	db 00000000b
	db 11100000b
	db 00000000b
	db 00000000b
	db 00000000b
	; .
	db 2
	db 00000000b
	db 00000000b
	db 00000000b
	db 00000000b
	db 00000000b
	db 10000000b
	db 00000000b
	; /
	db 4
	db 00100000b
	db 00100000b
	db 01000000b
	db 01000000b
	db 10000000b
	db 10000000b
	db 00000000b
	; 0
	db 4
	db 01000000b
	db 10100000b
	db 10100000b
	db 10100000b
	db 10100000b
	db 01000000b
	db 00000000b
	; 1
	db 4
	db 01000000b
	db 11000000b
	db 01000000b
	db 01000000b
	db 01000000b
	db 11100000b
	db 00000000b
	; 2
	db 4
	db 01000000b
	db 10100000b
	db 00100000b
	db 01000000b
	db 10000000b
	db 11100000b
	db 00000000b
	; 3
	db 4
	db 11000000b
	db 00100000b
	db 01000000b
	db 00100000b
	db 00100000b
	db 11000000b
	db 00000000b
	; 4
	db 4
	db 10100000b
	db 10100000b
	db 11100000b
	db 00100000b
	db 00100000b
	db 00100000b
	db 00000000b
	; 5
	db 4
	db 11100000b
	db 10000000b
	db 11000000b
	db 00100000b
	db 00100000b
	db 11000000b
	db 00000000b
	; 6
	db 4
	db 01100000b
	db 10000000b
	db 11000000b
	db 10100000b
	db 10100000b
	db 01000000b
	db 00000000b
	; 7
	db 4
	db 11100000b
	db 00100000b
	db 01000000b
	db 01000000b
	db 01000000b
	db 01000000b
	db 00000000b
	; 8
	db 4
	db 01000000b
	db 10100000b
	db 01000000b
	db 10100000b
	db 10100000b
	db 01000000b
	db 00000000b
	; 9
	db 4
	db 01000000b
	db 10100000b
	db 01100000b
	db 00100000b
	db 10100000b
	db 01000000b
	db 00000000b
	; :
	db 2
	db 00000000b
	db 10000000b
	db 00000000b
	db 00000000b
	db 00000000b
	db 10000000b
	db 00000000b
	; ;
	db 2
	db 00000000b
	db 10000000b
	db 00000000b
	db 00000000b
	db 00000000b
	db 10000000b
	db 10000000b
	; <
	db 4
	db 00000000b
	db 00100000b
	db 01000000b
	db 10000000b
	db 01000000b
	db 00100000b
	db 00000000b
	; =
	db 4
	db 00000000b
	db 00000000b
	db 11100000b
	db 00000000b
	db 11100000b
	db 00000000b
	db 00000000b
	; >
	db 4
	db 00000000b
	db 10000000b
	db 01000000b
	db 00100000b
	db 01000000b
	db 10000000b
	db 00000000b
	; ?
	db 4
	db 01000000b
	db 10100000b
	db 00100000b
	db 01000000b
	db 00000000b
	db 01000000b
	db 00000000b
	; @
	db 5
	db 00000000b
	db 01100000b
	db 10110000b
	db 10110000b
	db 10000000b
	db 01100000b
	db 00000000b
	; A
	db 4
	db 01000000b
	db 10100000b
	db 11100000b
	db 10100000b
	db 10100000b
	db 10100000b
	db 00000000b
	; B
	db 4
	db 11000000b
	db 10100000b
	db 11000000b
	db 10100000b
	db 10100000b
	db 11000000b
	db 00000000b
	; C
	db 4
	db 01100000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 01100000b
	db 00000000b
	; D
	db 4
	db 11000000b
	db 10100000b
	db 10100000b
	db 10100000b
	db 10100000b
	db 11000000b
	db 00000000b
	; E
	db 4
	db 11100000b
	db 10000000b
	db 11000000b
	db 10000000b
	db 10000000b
	db 11100000b
	db 00000000b
	; F
	db 4
	db 11100000b
	db 10000000b
	db 11000000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 00000000b
	; G
	db 4
	db 01100000b
	db 10000000b
	db 10000000b
	db 10100000b
	db 10100000b
	db 01100000b
	db 00000000b
	; H
	db 4
	db 10100000b
	db 10100000b
	db 11100000b
	db 10100000b
	db 10100000b
	db 10100000b
	db 00000000b
	; I
	db 4
	db 11100000b
	db 01000000b
	db 01000000b
	db 01000000b
	db 01000000b
	db 11100000b
	db 00000000b
	; J
	db 4
	db 11100000b
	db 00100000b
	db 00100000b
	db 00100000b
	db 00100000b
	db 11000000b
	db 00000000b
	; K
	db 4
	db 10100000b
	db 10100000b
	db 11000000b
	db 11000000b
	db 10100000b
	db 10100000b
	db 00000000b
	; L
	db 4
	db 10000000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 11100000b
	db 00000000b
	; M
	db 6
	db 10001000b
	db 11011000b
	db 10101000b
	db 10001000b
	db 10001000b
	db 10001000b
	db 00000000b
	; N
	db 5
	db 10010000b
	db 11010000b
	db 10110000b
	db 10010000b
	db 10010000b
	db 10010000b
	db 00000000b
	; O
	db 5
	db 01100000b
	db 10010000b
	db 10010000b
	db 10010000b
	db 10010000b
	db 01100000b
	db 00000000b
	; P
	db 4
	db 11000000b
	db 10100000b
	db 11000000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 00000000b
	; Q
	db 5
	db 01100000b
	db 10010000b
	db 10010000b
	db 10010000b
	db 10110000b
	db 01110000b
	db 00000000b
	; R
	db 4
	db 11000000b
	db 10100000b
	db 11000000b
	db 11000000b
	db 10100000b
	db 10100000b
	db 00000000b
	; S
	db 4
	db 01100000b
	db 10000000b
	db 01000000b
	db 00100000b
	db 00100000b
	db 11000000b
	db 00000000b
	; T
	db 4
	db 11100000b
	db 01000000b
	db 01000000b
	db 01000000b
	db 01000000b
	db 01000000b
	db 00000000b
	; U
	db 4
	db 10100000b
	db 10100000b
	db 10100000b
	db 10100000b
	db 10100000b
	db 01100000b
	db 00000000b
	; V
	db 4
	db 10100000b
	db 10100000b
	db 10100000b
	db 10100000b
	db 01000000b
	db 01000000b
	db 00000000b
	; W
	db 6
	db 10001000b
	db 10001000b
	db 10001000b
	db 10101000b
	db 01010000b
	db 01010000b
	db 00000000b
	; X
	db 4
	db 10100000b
	db 10100000b
	db 01000000b
	db 10100000b
	db 10100000b
	db 10100000b
	db 00000000b
	; Y
	db 4
	db 10100000b
	db 10100000b
	db 01000000b
	db 01000000b
	db 01000000b
	db 01000000b
	db 00000000b
	; Z
	db 4
	db 11100000b
	db 00100000b
	db 01000000b
	db 01000000b
	db 10000000b
	db 11100000b
	db 00000000b
	; [
	db 3
	db 11000000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 11000000b
	; \
	db 4
	db 10000000b
	db 10000000b
	db 01000000b
	db 01000000b
	db 00100000b
	db 00100000b
	db 00000000b
	; ]
	db 3
	db 11000000b
	db 01000000b
	db 01000000b
	db 01000000b
	db 01000000b
	db 01000000b
	db 11000000b
	; ^
	db 4
	db 01000000b
	db 10100000b
	db 00000000b
	db 00000000b
	db 00000000b
	db 00000000b
	db 00000000b
	; _
	db 4
	db 00000000b
	db 00000000b
	db 00000000b
	db 00000000b
	db 00000000b
	db 00000000b
	db 11100000b
	; £
	db 5
	db 01100000b
	db 10010000b
	db 01000000b
	db 11100000b
	db 01000000b
	db 11110000b
	db 00000000b
	; a
	db 4
	db 00000000b
	db 00000000b
	db 01100000b
	db 10100000b
	db 10100000b
	db 01100000b
	db 00000000b
	; b
	db 4
	db 10000000b
	db 10000000b
	db 11000000b
	db 10100000b
	db 10100000b
	db 11000000b
	db 00000000b
	; c
	db 3
	db 00000000b
	db 00000000b
	db 01000000b
	db 10000000b
	db 10000000b
	db 01000000b
	db 00000000b
	; d
	db 4
	db 00100000b
	db 00100000b
	db 01100000b
	db 10100000b
	db 10100000b
	db 01100000b
	db 00000000b
	; e
	db 4
	db 00000000b
	db 00000000b
	db 01000000b
	db 10100000b
	db 11000000b
	db 01100000b
	db 00000000b
	; f
	db 3
	db 01000000b
	db 10000000b
	db 10000000b
	db 11000000b
	db 10000000b
	db 10000000b
	db 00000000b
	; g
	db 4
	db 00000000b
	db 00000000b
	db 01100000b
	db 10100000b
	db 01100000b
	db 00100000b
	db 11000000b
	; h
	db 4
	db 10000000b
	db 10000000b
	db 11000000b
	db 10100000b
	db 10100000b
	db 10100000b
	db 00000000b
	; i
	db 2
	db 10000000b
	db 00000000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 00000000b
	; j
	db 3
	db 01000000b
	db 00000000b
	db 01000000b
	db 01000000b
	db 01000000b
	db 01000000b
	db 10000000b
	; k
	db 4
	db 10000000b
	db 10000000b
	db 10100000b
	db 11000000b
	db 10100000b
	db 10100000b
	db 00000000b
	; l
	db 2
	db 10000000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 00000000b
	; m
	db 6
	db 00000000b
	db 00000000b
	db 11010000b
	db 10101000b
	db 10101000b
	db 10101000b
	db 00000000b
	; n
	db 4
	db 00000000b
	db 00000000b
	db 11000000b
	db 10100000b
	db 10100000b
	db 10100000b
	db 00000000b
	; o
	db 4
	db 00000000b
	db 00000000b
	db 01000000b
	db 10100000b
	db 10100000b
	db 01000000b
	db 00000000b
	; p
	db 4
	db 00000000b
	db 00000000b
	db 11000000b
	db 10100000b
	db 10100000b
	db 11000000b
	db 10000000b
	; q
	db 4
	db 00000000b
	db 00000000b
	db 01100000b
	db 10100000b
	db 10100000b
	db 01100000b
	db 00100000b
	; r
	db 3
	db 00000000b
	db 00000000b
	db 11000000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 00000000b
	; s
	db 4
	db 00000000b
	db 00000000b
	db 01100000b
	db 10000000b
	db 01100000b
	db 11000000b
	db 00000000b
	; t
	db 3
	db 10000000b
	db 10000000b
	db 11000000b
	db 10000000b
	db 10000000b
	db 01000000b
	db 00000000b
	; u
	db 4
	db 00000000b
	db 00000000b
	db 10100000b
	db 10100000b
	db 10100000b
	db 01100000b
	db 00000000b
	; v
	db 4
	db 00000000b
	db 00000000b
	db 10100000b
	db 10100000b
	db 10100000b
	db 01000000b
	db 00000000b
	; w
	db 6
	db 00000000b
	db 00000000b
	db 10001000b
	db 10001000b
	db 10101000b
	db 01010000b
	db 00000000b
	; x
	db 4
	db 00000000b
	db 00000000b
	db 10100000b
	db 01000000b
	db 01000000b
	db 10100000b
	db 00000000b
	; y
	db 4
	db 00000000b
	db 00000000b
	db 10100000b
	db 10100000b
	db 01100000b
	db 00100000b
	db 11000000b
	; z
	db 4
	db 00000000b
	db 00000000b
	db 11100000b
	db 00100000b
	db 01000000b
	db 11100000b
	db 00000000b
	; {
	db 4
	db 00100000b
	db 01000000b
	db 01000000b
	db 11000000b
	db 01000000b
	db 01000000b
	db 00100000b
	; |
	db 2
	db 10000000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 10000000b
	db 10000000b
	; }
	db 4
	db 10000000b
	db 01000000b
	db 01000000b
	db 01100000b
	db 01000000b
	db 01000000b
	db 10000000b
	; ~
	db 5
	db 00000000b
	db 00000000b
	db 01010000b
	db 10100000b
	db 00000000b
	db 00000000b
	db 00000000b
	; copyright
	db 8
	db 00111000b
	db 01000100b
	db 10011010b
	db 10100010b
	db 10011010b
	db 01000100b
	db 00111000b