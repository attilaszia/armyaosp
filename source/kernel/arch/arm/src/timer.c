#include <arch/armtimer.h>

static volatile arm_timer_t* timer_regs = (arm_timer_t*)RPI_ARMTIMER_BASE;

void init_timer ( void ) {
	timer_regs->Load = 0x400;
	timer_regs->Control =
            RPI_ARMTIMER_CTRL_23BIT |
            RPI_ARMTIMER_CTRL_ENABLE |
            RPI_ARMTIMER_CTRL_INT_ENABLE |
            RPI_ARMTIMER_CTRL_PRESCALE_256;
}
