/*
    Part of the Raspberry-Pi Bare Metal Tutorials
    https://www.valvers.com/rpi/bare-metal/
    Copyright (c) 2013-2020, Brian Sidebotham

    This software is licensed under the MIT License.
    Please see the LICENSE file included with this software.
*/

/*
 * Part of the code below has been developed by Johan Nordlander and Fredrik Bengtsson at LTU.
 * Part of the code has been also developed, modified and extended to ARMv8 by Wagner de Morais and Hazem Ali.
*/

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdarg.h>

#include "tinythreads.h"
#include "rpi3.h"
#include "piface.h"

#include "rpi-armtimer.h"
#include "rpi-systimer.h"
#include "rpi-interrupts.h"

__attribute__(( always_inline )) static inline void enable_interrupts() {
  __asm volatile("cpsie i \n"); //AIF???
}

__attribute__(( always_inline )) static inline void disable_interrupts() {
  __asm volatile("cpsid i \n"); //AIF???
}

__attribute__(( always_inline )) static inline void no_operation() {
  __asm volatile("nop \n"); //AIF
}

#define DISABLE()       disable_interrupts()
#define ENABLE()        enable_interrupts()
#define MAXINT          0x7fffffff
#define PUTTOLDC(fmt, args...){ \
	char s[100]; \
    sprintf(s, fmt, ##args); \
    piface_puts(s); \
}

// Mutex variable to guard critical sections
mutex mute = MUTEX_INIT;

void printAtSeg(int seg, const char* fmt, ...) {

  if(seg>3 || seg< 0){ return; }
  va_list args;
  va_start(args, fmt);
  int row=(seg/2) ;
  int col=(seg%2)*8 ;
  piface_set_cursor(col,row); //set the cursor to point to a segment
  char s[100];
  sprintf(s, fmt, va_arg(args, int), va_arg(args, int));
  piface_puts(s);
  va_end(args);
}

void busy_wait(uint32_t t) {
    for(volatile uint32_t i=0; i < t; )
        i++;
}

void computeSomething(int pos) {
    lock(&mute);
    printAtSeg(pos % 4, "S%d_%d", pos, ticks);
    busy_wait(100000u);

    unlock(&mute);
}



// @brief The BCM2835 Interupt controller peripheral at it's base address
static rpi_irq_controller_t* rpiIRQController =
        (rpi_irq_controller_t*)RPI_INTERRUPT_CONTROLLER_BASE;

// @brief Return the IRQ Controller register set
static rpi_irq_controller_t* RPI_GetIrqController( void )
{
    return rpiIRQController;
}

void RPI_EnableARMTimerInterrupt(void)
{
    RPI_GetIrqController()->Enable_Basic_IRQs = RPI_BASIC_ARM_TIMER_IRQ;
}

void initTimerInterrupts()
{
    RPI_EnableARMTimerInterrupt();
    /* Setup the system timer interrupt
       Timer frequency = Clk/256 * 0x400
       0xF3C is about 1 second
    */
    RPI_GetArmTimer()->Load = 0xF3C;
    /* Setup the ARM Timer */
    RPI_GetArmTimer()->Control =
            RPI_ARMTIMER_CTRL_23BIT |
            RPI_ARMTIMER_CTRL_ENABLE |
            RPI_ARMTIMER_CTRL_INT_ENABLE |
            RPI_ARMTIMER_CTRL_PRESCALE_256;
    /* Enable interrupts! */
    ENABLE();
}

int main() {
    piface_init();
    spawnWithDeadline(3, 3, computeSomething, 0);
    spawnWithDeadline(5, 5, computeSomething, 1);
    spawnWithDeadline(7, 7, computeSomething, 2);




    initTimerInterrupts();
    while (1) no_operation();

}
