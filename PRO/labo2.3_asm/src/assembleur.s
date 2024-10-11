#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

.section .text,"ax"
.cpu cortex-m3
.thumb
.syntax unified

.global funcexo1
.global funcexo2
.global funcexo3


/*****************************************************
 * function     : exercice1
 * R0: a
 * R1: b
 * R2: c
 * R3: d
 * SP: &e
 * return value : *e = a XOR b XOR c XOR d
 *****************************************************/
.thumb_func
funcexo1:

	EOR r0, r0, r1
	EOR r0, r0, r2
	EOR r0, r0, r3

	LDR r2, [SP]
	STR r0, [r2]
	bx  lr

/*****************************************************
 * 32 bits (unsigned) multiplication with overflow detection
 * r0: multiplicand
 * r1: multiplier
 * return values :
 * r0 = r0 * r1, r1=1 if 32 bits overflow (0 otherwise)
 *****************************************************/
.thumb_func
mult32:
	umull r0,r1,r0,r1
	cmp   r1,#0
	it    ne
	movne r1,#1				// add carry to r1
	bx    lr

/*****************************************************
 * function     : exercice 2
 * R0: a
 * R1: b
 * R2: c
 * R3: d
 * return value : a*b+c*d or 0 if overflow
 *****************************************************/
.thumb_func
funcexo2:
	push {r4, lr}

	BL mult32
	CMP r1, #1
	BEQ overflow

	MOV r4, r0

	MOV r0, r2
	mov r1 ,r3
	bl mult32
	cmp r1, #1
	BEQ overflow

	adds r0, r0, r4
	bcs overflow

	b end

overflow:
	mov r1, #1
	pop {r4, lr}
	bx lr

end:
	pop {r4, lr}
	bx   lr
	
	
/*****************************************************
 * function     : exercice 3
 * R0: a
 * R1: b and c (c in high 16 bits)
 * R2: d
 * R3: e
 * return value : addition of the elements of the structure
 *****************************************************/
.thumb_func
funcexo3:

	PUSH {R4}

	lsr R4, R1, #16 // Décale R1 de 16 a droite => il ne reste plus que c
//	sxth r4, r4 // passe de 16 bits à 32

	AND R1, R1, #0xFF // mask pour avoir b
	sxtb r1, r1 // passe de 8 bits a 32

	sxtb r2, r2 // 8 bit -> 32

	ADD R0, R1
	ADD R0, R2
	ADD R0, r3
	ADD R0, R4

	POP {R4}

	bx    lr

//.weak add_sat
.ltorg
