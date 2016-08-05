/* Written by Alex Chadwick. 
*
*  This code is part of the Baking Pie tutorials' example implementation. For now
*  the only change I made was to rename the functions with C style casing.
*
*	systemTime.s contains the code that interacts with the system timer.
*/

/*
* The system timer runs at 1MHz, and just counts always. Thus we can deduce
* timings by measuring the difference between two readings.
*/

/*
* get_system_timer_base returns the base address of the System Timer region as a
* physical address in register r0.
* C++ Signature: void* get_system_timer_base()
*/
.globl get_system_timer_base
get_system_timer_base: 
	ldr r0,=0x20003000
	mov pc,lr

/*
* get_timestamp gets the current timestamp of the system timer, and returns it
* in registers r0 and r1, with r1 being the most significant 32 bits.
* C++ Signature: u64 get_timestamp()
*/
.globl get_timestamp
get_timestamp:
	push {lr}
	bl get_system_timer_base
	ldrd r0,r1,[r0,#4]
	pop {pc}

/*
* timer_wait timer_waits at least a specified number of microseconds before returning.
* The duration to timer_wait is given in r0.
* C++ Signature: void timer_wait(u32 delayInMicroSeconds)
*/
.globl timer_wait
timer_wait:
	delay .req r2
	mov delay,r0	
	push {lr}
	bl get_timestamp
	start .req r3
	mov start,r0

	loop$:
		bl get_timestamp
		elapsed .req r1
		sub elapsed,r0,start
		cmp elapsed,delay
		.unreq elapsed
		bls loop$
		
	.unreq delay
	.unreq start
	pop {pc}
