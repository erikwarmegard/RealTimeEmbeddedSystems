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


int led=0;
void blinkLed(void){
        if(led==1) {GPIO->GPCLR0 = (1 << 16); led=0;}
	else{GPIO->GPSET0 = (1 << 16); led=1;}
	
}


void showExponentOnScreen(int i){
  ExpStruct * e1 = iexp((int)i);  //we are bliking inside the exponential calc.
  piface_clear(); //clear screen
  char * c = malloc(sizeof(char)*32);
  sprintf(c,"%d: ",i);
  piface_puts(c);
  char * f1 = expo2string(e1);
  piface_puts(f1);
  free(f1);
  free(e1);
  free(c);


}



int main()
{
  /* Enable GPIO16 as an output */
  GPIO->GPFSEL1 |= (1 << 18);
  GPIO->GPCLR0 = (1 << 16);
  piface_clear();
  while (1){

    for(int i=1; i<20; i++){
        showExponentOnScreen(i);
	blinkLed();
  	
    }

  }

	return 0;
}
