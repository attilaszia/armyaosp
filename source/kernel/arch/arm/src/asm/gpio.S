/* Written by Alex Chadwick. 
*
*  This code is part of the Baking Pie tutorials' example implementation. For now
*  the only change I made was to rename the functions with C style casing.
*
*	gpio.s contains the rountines for manipulation of the GPIO ports.
*/

/*
* According to the EABI, all method calls should use r0-r3 for passing
* parameters, should preserve registers r4-r8,r10-r11,sp between calls, and 
* should return values in r0 (and r1 if needed). 
* It does also stipulate many things about how methods should use the registers
* and stack during calls, but we're using hand coded assembly. All we need to 
* do is obey the start and end conditions, and if all our methods do this, they
* would all work from C.
*/

/*
* get_gpio_address returns the base address of the GPIO region as a physical address
* in register r0.
* C++ Signature: void* get_gpio_address()
*/
.globl get_gpio_address
get_gpio_address: 
	gpioAddr .req r0
	ldr gpioAddr,=0x20200000
	mov pc,lr
	.unreq gpioAddr

/*
* set_gpio_function sets the function of the GPIO register addressed by r0 to the
* low  3 bits of r1.
* C++ Signature: void set_gpio_function(u32 gpioRegister, u32 function)
*/
.globl set_gpio_function
set_gpio_function:
    pinNum .req r0
    pinFunc .req r1
	cmp pinNum,#53
	cmpls pinFunc,#7
	movhi pc,lr

	push {lr}
	mov r2,pinNum
	.unreq pinNum
	pinNum .req r2
	bl get_gpio_address
	gpioAddr .req r0

	functionLoop$:
		cmp pinNum,#9
		subhi pinNum,#10
		addhi gpioAddr,#4
		bhi functionLoop$

	add pinNum, pinNum,lsl #1
	lsl pinFunc,pinNum

	mask .req r3
	mov mask,#7					/* r3 = 111 in binary */
	lsl mask,pinNum				/* r3 = 11100..00 where the 111 is in the same position as the function in r1 */
	.unreq pinNum

	mvn mask,mask				/* r3 = 11..1100011..11 where the 000 is in the same poisiont as the function in r1 */
	oldFunc .req r2
	ldr oldFunc,[gpioAddr]		/* r2 = existing code */
	and oldFunc,mask			/* r2 = existing code with bits for this pin all 0 */
	.unreq mask

	orr pinFunc,oldFunc			/* r1 = existing code with correct bits set */
	.unreq oldFunc

	str pinFunc,[gpioAddr]
	.unreq pinFunc
	.unreq gpioAddr
	pop {pc}

/*
* set_gpio sets the GPIO pin addressed by register r0 high if r1 != 0 and low
* otherwise. 
* C++ Signature: void set_gpio(u32 gpioRegister, u32 value)
*/
.globl set_gpio
set_gpio:	
    pinNum .req r0
    pinVal .req r1

	cmp pinNum,#53
	movhi pc,lr
	push {lr}
	mov r2,pinNum	
    .unreq pinNum	
    pinNum .req r2
	bl get_gpio_address
    gpioAddr .req r0

	pinBank .req r3
	lsr pinBank,pinNum,#5
	lsl pinBank,#2
	add gpioAddr,pinBank
	.unreq pinBank

	and pinNum,#31
	setBit .req r3
	mov setBit,#1
	lsl setBit,pinNum
	.unreq pinNum

	teq pinVal,#0
	.unreq pinVal
	streq setBit,[gpioAddr,#40]
	strne setBit,[gpioAddr,#28]
	.unreq setBit
	.unreq gpioAddr
	pop {pc}
