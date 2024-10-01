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
.global funcexo4

/*****************************************************
 * function     : exercice1
 * arguments    : unsigned integer number: register R0
                : unsigned integer number: register R1
 * return value : unsigned integer result: register R0
 *   Code for the first exercise
 *****************************************************/
.thumb_func
funcexo1:
	subs r2, r0, r1
	bhi  funcexo1_next
	sub  r2, r1, r0
funcexo1_next:
    mov     r0, r2

	mov	pc, r14		/* end of subroutine */


/*****************************************************
 * function     : exercice2
 * arguments    : unsigned integer number: register R0
 * return value : unsigned integer result: register R0
 *   Code for the second exercise
 *****************************************************/
.thumb_func
funcexo2:
	mov	  r1, #0
	mov	  r2, #1
funcexo2_loop:
	add   r1, r1, r2
	add   r2, r2, #1
	subs  r3, r0, r1
	bpl   funcexo2_loop
	mov   r0, r1

	mov	pc, r14		/* end of subroutine */



/*****************************************************
 * function     : exercice3 - Fibonacci
 * arguments    : unsigned integer number: register R0
 * return value : unsigned integer number: register R0
 *   Code for the third exercise
 *****************************************************/
.thumb_func
funcexo3:

    // Initialize a and b
    mov   r1, #2        // r1 = a = 2
    mov   r2, #1        // r2 = b = 1
    mov   r3, #0        // r3 = i = 0

    cmp   r0, #0
    beq   end           // If n == 0, branch to end

funcexo3_loop:
    cmp   r3, r0
    bge   end           // If i >= n, exit the loop

    add   r1, r1, r2    // a = a + b (r1 = r1 + r2)
    sub   r2, r1, r2    // b = a - b (r2 = r1 - r2)

    add   r3, r3, #1    // i++

    b     funcexo3_loop

end:
    mov   r0, r1

    mov   pc, r14  /* end of subroutine */

/*****************************************************
 * function     : exercice4
 * arguments    : long long: register R1,R0
                : unsigned integer: register R2
 * return value : long long: register R1,R0
 *   Code for the fourth exercise
 *****************************************************/
.thumb_func
funcexo4:

    cmp     R2, #0
    beq     shift_left          // If dir == 0, go to shift_left
    cmp     R2, #1
    beq     shift_right         // If dir == 1, go to shift_right

    b       return_a

shift_left:
    lsls    R0, R0, #1         	// Shift lower 32 bits (R0) left by 1
    lsl     R1, R1, #1         	// Shift upper 32 bits (R1) left by 1
    adc 	r1,	r1,	#0			// Add carry bit r1 = r1 + 0 + c
    b       return_a

shift_right:
    lsrs    R1, R1, #1			// Shift right s pour modifié les fanions
    rrx		r0, r0				// RRX : Prend le carry shift et le met dans MSB et LSB vas dans le carry

    b       return_a

return_a:
	mov	pc, r14		/* end of subroutine */


.weak funcexo1, funcexo2, funcexo3, funcexo4
.ltorg
