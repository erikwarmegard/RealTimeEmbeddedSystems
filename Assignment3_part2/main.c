/*
 * Part of the code below has been developed by Johan Nordlander and Fredrik Bengtsson at LTU.
 * Part of the code has been also developed, modified and extended to ARMv8 by Wagner de Morais and Hazem Ali.
*/
#include <stdlib.h>
#include <stdio.h>
#include "lib/iexp.h"
#include "lib/tinythreads.h"
#include "lib/rpi3.h"
#include "lib/piface.h"
#include <math.h>
#define PUTTOLDC(fmt, args...){ \
	char s[100]; \
    sprintf(s, fmt, ##args); \
    piface_puts(s); \
}


int is_prime(int i) { //done by erik and johan
    for(int j=2; j<= i/2 ;j++ ){
			if(i%j==0){ return 0; }
    }
    return 1;
}


void computeExponential(int pos) {
		ExpStruct *e1;
		for(int n = 1; n < 22 ; n++) {// stops at n=22, ...01807,...
        e1 = iexp(n);
				printAtSeg(pos,e1->expInt);
        yield();
				free(e1);
    }

}

//Each segment (seg:0...3) can take up 8 digits in space
// ------------------
// |S0:XXXXXS1:XXXXX|
// |S2:XXXXXS3:XXXXX|
// ------------------
void printAtSeg(int seg, int num) { // To be implemented
		if(seg>3 ||seg< 0){ return; }
		int row=(seg/2) ; //used their function
		int col=(seg%2)*8 ; // used their function
		piface_set_cursor(col,row); //set the cursor to point to a segment
		PUTTOLDC("T%i:%d", seg, num);	//insert the new content at that location (override-text)

}

void computePrimes(int pos) {
    for(int n = 1; ; n++) {
        if (is_prime(n)) {
						printAtSeg(pos,n);
            yield();
        }
    }
}

void computePower(int pos) {
    for(int n = 0; ; n++) {
				printAtSeg(pos,n*n);
        busy_wait(1000000u); //delay added for visualization purposes!!!
        yield();
    }
}

void busy_wait(uint32_t t) {
    for(volatile uint32_t i=0; i < t; )
        i++;
}

int main() {
    piface_init();
    spawn(computePower, 1);
		spawn(computePrimes, 2);
		spawn(computeExponential, 3);
    computePower(0);
}
