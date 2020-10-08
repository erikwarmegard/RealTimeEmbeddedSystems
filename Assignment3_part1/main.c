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


//Each segment (seg:0...3) can take up 8 digits in space
// ------------------
// |S0:XXXXXS1:XXXXX|
// |S2:XXXXXS3:XXXXX|
// ------------------
void printAtSeg(int seg, int num) { // To be implemented
		if(seg>3 ||seg< 0){ return; }
		int row=(seg/2) + 1; //first row =1
		int col=(seg%2)*8 ; // first col =0
		piface_set_cursor(col,row); //set the cursor to point to a segment
		PUTTOLDC("T%i:%d", seg, num);	//insert the new content at that location (override-text)

}
// The function declaration above displays an integer content in a given segment.
// However, to display arbitrary arguments (float, double, ...etc), you can use
// Variadic arguments with proper string formatting.
// Please check the url: https://en.cppreference.com/w/c/language/variadic
// For example, you could redeclare printAtSeg as:
//
//              void printAtSeg(int seg, const char* fmt, ...) {
//                  To be implemented
//              }
//
// and call it via printAtSeg(1, "S%i: %.1f", 1, 3.14);

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
	//this file does not include computeExponent!
	piface_init();
	spawn(computePower, 1);
	computePower(0);
}
