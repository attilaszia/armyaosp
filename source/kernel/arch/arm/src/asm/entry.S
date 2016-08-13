/* Entry point of the kernel.
*
* The VideoCore GPU has loaded our binary at 0x8000, so now we have to set up
* the exception vector for the core, then we set up an environment for C code
* to run, zeroing out .bss and setting up the kernel stack.
*/

#include <arm.h>

.section .init
    .globl _start
    
    /*
    * ELF entry point, although the symbol is not needed, we include it.
    */
    .func _start
_start:
    /* We should deal with ATAGs first, but it is omitted for now */
    b reset_handler
    .endfunc 

/* Exception vector table */
_vectors:
    ldr pc, reset_addr
    ldr pc, undef_addr
    ldr pc, swi_addr 
    ldr pc, prefetch_addr
    ldr pc, abort_addr
    ldr pc, reserved_addr
    ldr pc, irq_addr
    ldr pc, fiq_addr

reset_addr:    .word reset_handler
undef_addr:    .word reset_handler
swi_addr:      .word reset_handler
prefetch_addr: .word reset_handler
abort_addr:    .word reset_handler
reserved_addr: .word reset_handler
irq_addr:      .word irq_handler
fiq_addr:      .word reset_handler

_endvectors:

.section .text
    .func reset_handler
reset_handler:
    /* Enter SYS mode with disabled interrupts */
    cpsid if, #ARM_MODE_SYS

    /*Copy the exception table to 0x0. This is 16 words.*/
    mov r0, #0
    ldr r1, =_vectors
    ldmia r1!, {r2-r9}
    stmia r0!, {r2-r9}
    ldmia r1!, {r2-r9}
    stmia r0!, {r2-r9}

    /* Some mangling of the Control Register to allow unalign mem access */
    mrc p15, 0, r0, c1, c0, 0
    orr r0, #1 << 22
    mcr p15, 0, r0, c1, c0, 0
    /* Clear the .bss section */
    ldr r0, =_bss
    ldr r1, =_end
    mov r2, #0
    mov r3, #0
    mov r4, #0
    mov r5, #0
    b bssloopa
bssloopb:
    stmia r0!, {r2-r5}
bssloopa:
    cmp r0,r1             /* did we hit the end yet */
    blo bssloopb          /* if not, go again */
    
    add sp, r1, #0x2000   /* lets have a 8K stack after the kernel end */
 
    b arch_start          /* call into architecture specific C code */
    .endfunc



