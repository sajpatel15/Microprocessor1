	.text
	.align 2
	.global main

MemAddr1 .field 0x20000000
MemAddr2 .field 0x20000020

main:

	LDR R3, MemAddr1; R3 is pointing to the the address 0x20000000
	LDR R4, MemAddr2; R4 is pointing to the the address 0x20000004


	MOV R2, #1h; R2 = 1
	STR R2, [R3], #4; STORE R2 INTO R3 THEN INCREMENT THE ADDRESS OF R3 BY 4

	MOV R2, #2h; R3 = 2
	STR R2, [R3], #4; STORE R2 INTO R3+4 THEN INCREMENT THE ADDRESS OF R3 BY 4

	MOV R2, #3h; R3 = 3
	STR R2, [R3], #4; STORE R2 INTO R3+8 THEN INCREMENT THE ADDRESS OF R3 BY 4

	MOV R2, #4h; R3 = 4
	STR R2, [R3], #4; STORE R2 INTO R3+12 THEN INCREMENT THE ADDRESS OF R3 BY 4

	MOV R2, #5h; R3 = 5
	STR R2, [R3]; STORE R2 INTO R3+16 THEN INCREMENT THE ADDRESS OF R3 BY 4

	LDR R3, MemAddr1; RESET THE ADDRESS AT WHICH R3 IS POINTING TO 0X20000000
	MOV R5, #0; R5 = 0

	 ;STARTING A FOR LOOP
for:
		LDR R6, [R3], #4 ;LOAD THE VALUE R3 INTO R6 THEN INCREMENT THE ADDRESS OF R6 BY 4
		;BRANCH WITH LINK (LINK BEING SQUARE THAT IS DEFINED AT THE BOTTOM
		BL square

		STR R7, [R4], #4 ;STORE THE VALUE R7 INTO R4 THEN INCREMENT THE ADDRESS OF R4 BY 4
		ADD R5, #1; R5 = 1

		CMPS R5, #5; COMPARES THE VALUE OF R5 WITH 5 AND RAISES A FLAG ACCORDING TO THE DIFFERENCE BETWEEN THE TWO VALUES
		; GO BACK TO THE START OF THE LOOP
		BNE for
;forever loop

	B $
	; FUNCTION SQUARE TO WHICH THE CODE IN THE FOR LOOP BRANCHES TO
square:
		MUL R7, R6, R6; R7 = R6 * R6
		BX LR; RETURN FROM FUNCTION CALL
	.end
