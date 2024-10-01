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
.global majuscule

/*****************************************************
 * function     : exercice1
 * R0: A pointer
 * R1: B pointer
 * return value : *A + *B
 *****************************************************/
.thumb_func
funcexo1:
	ldr r0, [r0]
	ldr r1, [r1]
	adds r0, r0, r1
	bcs carry
	b end
carry:
	mov r0, #0

end:
	bx  lr


/*****************************************************
 * function     : exercice2
 * R0: A pointer
 * R1: B pointer
 * R2: arrays size
 * return value : B[]=2*A[]
 *****************************************************/
.thumb_func
funcexo2:
	mov r3, #0			//i = 0
	cmp r3, r2			//i ?= size
	beq end_loop			// i >= size => end

loop:
	cmp r3, r2  		// i ?= size
	bge end_loop			// i >= size => end
	add r1, r3 			// B[i]
	add r0, r3			// A[i]
	lsl r1, r0, #1		// B[i] = 2*A[I]
	add r3, r3, #1		// i += 1
	b loop

end_loop:
	bx  lr


.thumb_func
majuscule:

	bx lr


//.weak add_sat
.ltorg
