/* Written by Alex Chadwick. 
*
*  This code is part of the Baking Pie tutorials' example implementation. For now
*  the only change I made was to rename the functions with C style casing.
*
*	random.s contains code to do with generating pseudo random numbers.
*/

/*
* random is a function with an input of the last number it generated, and an 
* output of the next number in a pseduo random number sequence.
* C++ Signature: u32 random(u32 lastValue);
*/
.globl random
random:
	xnm .req r0
	a .req r1
	
	mov a,#0xef00
	mul a,xnm
	mul a,xnm
	add a,xnm
	.unreq xnm
	add r0,a,#73
	
	.unreq a
	mov pc,lr
