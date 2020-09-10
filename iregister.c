//  Created by Mohammadreza Mousavi [mohmou] on 9/5/14.
//  Updated by Masoumeh Taromirad on 11/08/16.
//  Updated by Wagner Morais and Johannes van Esch on 28/08/18.
//  Copyright (c) 2014 by Mohammadreza Mousavi [mohmou]. All rights reserved.
 
#include <stdlib.h>
#include <stdio.h>
#include "iregister.h"


void resetAll(iRegister *r){
	if (r == NULL) return;
	r->content &= (0 << 0); // Mask all bits in register with 0
}


void setBit(int i, iRegister *r){
	if ((i > 31) | (i < 0)) return;
	if (r == NULL) return;
	r->content |= (1 << i);	
}


void setAll(iRegister *r) {
	if (r == NULL) return;
	r->content |= ~(0 << 0); // OR all bits with 1
}


int getBit(int i, iRegister *r) {
        if (r == NULL) {
          return -1;
        }
	else if (i >= 32 || i < 0) {
          return -1;
        }
	else return (unsigned int) ((r->content) & ( 1 << i )) >> i; // Mask out the bit, then shift it to the far right so it gets returned as the integer
}


void assignNibble(int start, int value, iRegister *r) {
	if(start > 29) return;
	if (r == NULL) return;
	r->content &= ~(15 << start); 
	r->content |= (value << start);
}


int getNibble(int start, iRegister *r) {
	if(start > 29 || start < 0) return NULL;
	if (r == NULL) return NULL;
	return ((r->content) & ( (unsigned) 15 << start )) >> start;
}


//FIXME: Will eventually fill up all memory space if called too much.
char *reg2str(iRegister *r) {
	char *reg = (char*) malloc(sizeof(char) * 32);
	
	int i;
	
	for(i = 0; i < 32; i++){
		if(getBit(i,r)){
			reg[i] = 49;
		} else reg[i] = 48;
	}
	
	return reg;
}


// Note: added the loop to prevent added 1s
void shiftRight(int i, iRegister *r) {
	if (i > 31 || i < 0) return;
	if (r == NULL) return;
	
        r->content = r->content >> i;
        for(int j = 0; j < i; j++){
          resetBit(31-j ,r);
        }
}


void shiftLeft(int i, iRegister *r) {
	if (i > 31 || i < 0) return;
	if (r == NULL) return;
	r->content = (r->content << i);
}


void resetBit(int i, iRegister *r) {
        if (i > 31 || i < 0) return;
	if (r == NULL) return;
	r->content &= ~(1 << i);
}
