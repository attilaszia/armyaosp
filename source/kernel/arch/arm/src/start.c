/* C entry point for ARM architecture
*
*  Copyright (c) 2016 Attila Szasz
*
*
*/

#include <console.h>

const char* build_date = __DATE__;
const char* build_time = __TIME__;

void arch_start() {
    /* Initialize screen */

    init_screen();
    
    int i;
    kprintf(
        INFO,
        "Booting yaOSp 0.0.6-arm built on %s %s.\n",
        build_date,
        build_time
    );
    /* Do the real work here */
}
