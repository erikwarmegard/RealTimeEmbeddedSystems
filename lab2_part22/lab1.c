/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
*/

#include <stdio.h>
#include <rpi3.h>
#include "exponential.h"

void piface_puts(char c[]);
void piface_putc(char c);
void piface_clear();

void delay(long unsigned int delayTime) {
    long unsigned int i = 0;

    while(i <= delayTime){
        i++;
    }
    return;
}


int main()
{

    piface_clear();
    while (1)
    {

      for(int i=1; i<20; i++){
          char * c = malloc(sizeof(char)*32);
          sprintf(c,"%d: ",i);
          piface_puts(c);
          ExpStruct *e1 = (ExpStruct *) malloc(sizeof(ExpStruct));
          e1 = iexp(i);
          char * c1 = exponent2str(e1);
          piface_puts(c1);
          //double realEXP =exp(i);
          //printf("%d: %d.%d, \t real: %f \n",i,e1->expInt,e1->expFraction, realEXP);
          free(c1);
          free(e1);
          free(c);
          //dealy()
          delay(1400000);
      }

    }

	return 0;
}
