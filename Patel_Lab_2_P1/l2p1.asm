	.text
	.align 2
	.global main

MemAddr1 .field 0x20000000
MemAddr2 .field 0x20000004

main:
	LDR R3, MemAddr1; R3 is pointing to the the address 0x20000000
	LDR R4, MemAddr2; R4 is pointing to the the address 0x20000004
;part a
	MOV R5, #0FF00h; R5 = FF00
	STR R5, [R3]; R3 = R5
	MOV R5, #02FFh; R5 = 02FF
	STR R5, [R4]; R4 = R5

	LDR R6, [R3]; R6 = R3
	LDR R7, [R4]; R7 = R4

;part b
	ADDS R8, R6, R7; R8 = R6 + R7
	MOV R5, #0FF00h; R5 = FF00
	MOVT R5, #4FF0h; R5 = 4FF0FF0
	STR R5, [R3]; R3 = R5
	MOV R5, #02FFh; R5 = 02FF
	MOVT R5, #4FFFh; R5 = 4FFF02FF
	STR R5, [R4]; R4 = R5

	LDR R6, [R3]; R6 = R3
	LDR R7, [R4]; R7 = R4

	ADDS R8, R6, R7; R8 = R6 + R7

	;forever loop
	B $
	.end
