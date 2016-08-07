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
for (i = 1; i<28; i++ ) {
    kprintf(INFO, "%d\n",i);
}
    kprintf( INFO, "Rot in hell" );
    draw_line( 0, 0, 100, 100);
    /* Do the real work here */
}
