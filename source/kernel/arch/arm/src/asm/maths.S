/* Written by Alex Chadwick. 
*
*  This code is part of the Baking Pie tutorials' example implementation. For now
*  the only change I made was to rename the functions with C style casing.
*
*	maths.s contains the rountines for mathematics.
*/

/* NEW
* divide_u32 Divides one unsigned 32 bit number in r0 by another in r1 and 
* returns the result in r0 and the remainder in r1.
* C++ Signature: u32x2 divide_u32(u32 dividend, u32 divisor);
* This is implemented as binary long division.
*/
.globl divide_u32
divide_u32:
	result .req r0
	remainder .req r1
	shift .req r2
	current .req r3

	clz shift,r1
	clz r3,r0
	subs shift,r3
	lsl current,r1,shift
	mov remainder,r0
	mov result,#0
	blt divide_u32Return$
	
	divide_u32Loop$:
		cmp remainder,current
		blt divide_u32LoopContinue$

		add result,result,#1
		subs remainder,current
		lsleq result,shift 
		beq divide_u32Return$

	divide_u32LoopContinue$:
		subs shift,#1
		lsrge current,#1
		lslge result,#1
		bge divide_u32Loop$
	
divide_u32Return$:
	.unreq current
	mov pc,lr
	
	.unreq result
	.unreq remainder
	.unreq shift
