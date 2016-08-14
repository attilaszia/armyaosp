/** Interrupt handling routines
 * 
 * Copyright (c) 2016 Attila Szasz 
 *
 * Constants and declarations associated with interrupt handling.
 */
/* Embedded Xinu, Copyright (C) 2009, 2013.  All rights reserved. */

#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

typedef void (*interrupt_handler_t)(void);

typedef unsigned long irqmask;  /**< machine status for disable/restore  */


void enable(void);
irqmask disable(void);
irqmask restore(irqmask);
void enable_irq(irqmask);
void disable_irq(irqmask);

/* Include IRQ definitions  */
#include "bcm2835.h"

#endif /* _INTERRUPT_H_ */
