/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
*/
#include <stdlib.h>
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

void showExponentOnScreen(int i){
  char * c = malloc(sizeof(char)*32);
  sprintf(c,"%d: ",i);

  piface_puts(c);
  ExpStruct * e1 = iexp((int)i);
  char * f1 = expo2string(e1);
  piface_puts(f1);
  free(f1);
  free(e1);
  free(c);
  delay(7000000); //delay
  piface_clear(); //clear screen
}




int main()
{

  piface_clear();
  while (1){

    for(int i=1; i<23; i++){ //at i=22 or 23 we will reach overflow in calcExpo => zero!
        showExponentOnScreen(i);
    }

  }

	return 0;
}
