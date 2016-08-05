/* Written by Alex Chadwick. 
*
*  This code is part of the Baking Pie tutorials' example implementation. For now
*  the only change I made was to rename the functions with C style casing.
*
*	mailbox.s contains code that interacts with the mailbox for communication
*	with various devices.
*/

/*
* get_mailbox_base returns the base address of the mailbox region as a physical
* address in register r0.
* C++ Signature: void* get_mailbox_base()
*/
.globl get_mailbox_base
get_mailbox_base: 
	ldr r0,=0x2000B880
	mov pc,lr

/*
* mailbox_read returns the current value in the mailbox addressed to a channel
* given in the low 4 bits of r0, as the top 28 bits of r0.
* C++ Signature: u32 mailbox_read(u8 channel)
*/
.globl mailbox_read
mailbox_read: 
	and r3,r0,#0xf
	mov r2,lr
	bl get_mailbox_base
	mov lr,r2
	
	rightmail$:
		wait1$: 
			ldr r2,[r0,#24]
			tst r2,#0x40000000
			bne wait1$
			
		ldr r1,[r0,#0]
		and r2,r1,#0xf
		teq r2,r3
		bne rightmail$

	and r0,r1,#0xfffffff0
	mov pc,lr

/*
* mailbox_write writes the value given in the top 28 bits of r0 to the channel
* given in the low 4 bits of r1.
* C++ Signature: void mailbox_write(u32 value, u8 channel)
*/
.globl mailbox_write
mailbox_write: 
	and r2,r1,#0xf
	and r1,r0,#0xfffffff0
	orr r1,r2
	mov r2,lr
	bl get_mailbox_base
	mov lr,r2

	wait2$: 
		ldr r2,[r0,#24]
		tst r2,#0x80000000
		bne wait2$

	str r1,[r0,#32]
	mov pc,lr
