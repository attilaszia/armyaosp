/* Exception handlers
 *
 * Copyright (c) 2016 Attila Szasz
*/


#include <console.h>

void undef_handler( void ) {
    kprintf( INFO, "Undefined instruction" );
}

void swi_handler( void ) {
    kprintf( INFO, "Software interrupt" );
}

void prefetch_handler( void ) {
    kprintf( INFO, "Prefetch abort" );
}

void abort_handler( void ) {
    kprintf( INFO, "Abort (data)" );
}

void reserved_handler( void ) {
    kprintf( INFO, "Reserved" );
}
