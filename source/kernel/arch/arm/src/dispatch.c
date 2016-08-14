/* Interrupt handling
 * 
 * Copyright (c) 2016 Attila Szasz
 *
 *
 */

#include <console.h>

void dispatch( void ) {
    kprintf( INFO, "Interrupt!\n");
}
