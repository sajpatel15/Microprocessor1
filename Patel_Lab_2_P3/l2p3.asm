	.text
	.align
	.global main

MemAddr1 .field 0x20000000

main:
	LDR R3, MemAddr1;R3 is pointing to the the address 0x20000000

;part a
	MOV R5, #20; R5 = 20
	STR R5, [R3]; R3 = R5

	MOV R5, #20; R5 = 20
	STR R5, [R3, #4]; ADDRESS OF R3 PLUS 4 BYTES = 20

	MOV R5, #0; R5 = 0
	STR R5, [R3, #8]; ADDRESS OF R3 PLUS 8 BYTES = 0

	MOV R5, #0; R5 = 0
	STR R5, [R3, #12]; ADDRESS OF R3 PLUS 12 BYTES = 0

;part b
	LDR R7, [R3, #4]; LOAD THE VALUE OF THE VALUE AFTER R3 INTO THE REGISTER R7
	LDR R8, [R3]; R8 = R3
	ADD R6, R8, R7; R6 = R8 + R7

	LDR R7, [R3, #8]; LOAD THE VALUE THAT COMES AFTER THE NEXT TWO VALUES AFTER R3 INTO THE REGISTER R7
	ADD R6, R6, R7; R6 = R6 + R7

	LDR R7, [R3, #12]; LOAD THE VALUE THAT COMES AFTER THE NEXT THREE VALUES AFTER R3 INTO THE REGISTER R7
	ADD R6, R6, R7; R6 = R6 + R7

	MOV R7, #4; R7 = 4
	UDIV R6, R6, R7; R6 = R6 / R7
	STR R6, [R3]; R3 = R6


	;forever loop
	B $
	.end

