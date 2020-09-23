/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
*/

#include <stdio.h>
#include <rpi3.h>

void piface_puts(char c[]);
void piface_putc(char c);
void piface_clear();

int main()
{
    /* Enable GPIO16 as an output */
    GPIO->GPFSEL1 |= (1 << 18);
    
    /* Turn LED on */
    GPIO->GPSET0 |= (1 << 16);
    
    /* Write to PiFace's LCD screen */    
    piface_puts("Hello World!\n");

    while (1)
    {
      
    }

	return 0;
}