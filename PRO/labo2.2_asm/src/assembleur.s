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

loop:
	cmp r3, r2  		// i ?= size
	bge end_loop			// i >= size => end

	ldr r0, [r0, r3, LSL #2] // load A[i] into r0 (A + i * 4)
	lsl r0, r0, #1          // r0 = 2 * A[i]

    cmp r0, #0xFFFFFFFF     // compare the result with maximum 32-bit value
    blo no_overflow         // if no overflow, continue

overflow:
    mov r0, #0              // return 0 on overflow
    bx lr

no_overflow:
    str r0, [r1, r3, LSL #2] // store r0 in B[i] (B + i * 4)

    add r3, r3, #1          // i += 1
    b loop

end_loop:
	mov r0, #1
	bx  lr


.thumb_func
majuscule:
    mov r1, #0              // Set r1 to 0 for index i

maj_loop:
    ldrb r2, [r0, r1]       // Load byte at chaine[i] into r2
    cmp r2, #0              // Compare chaine[i] with 0 (null terminator)
    beq maj_end_loop            // If chaine[i] == 0, exit loop

    cmp r2, #97             // Compare chaine[i] with 'a' (97)
    blt next_char           // If chaine[i] < 'a', skip to next character

    cmp r2, #122            // Compare chaine[i] with 'z' (122)
    bgt next_char           // If chaine[i] > 'z', skip to next character

    sub r2, r2, #32         // Convert to uppercase by subtracting 32

    strb r2, [r0, r1]       // Store the uppercase character back into chaine[i]

next_char:
    add r1, r1, #1          // Increment i
    b maj_loop                  // Repeat loop

maj_end_loop:
    bx lr                   // Return


//.weak add_sat
.ltorg
