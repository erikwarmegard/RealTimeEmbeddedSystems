//  Created by Mohammadreza Mousavi [mohmou] on 9/5/14.
//  Updated by Masoumeh Taromirad on 11/08/16.
//  Updated by Wagner Morais and Johannes van Esch on 28/08/18.
//  Copyright (c) 2014 by Mohammadreza Mousavi [mohmou]. All rights reserved.
 
#include <stdlib.h>
#include <stdio.h>
#include "iregister.h"


void resetAll(iRegister *r){
	if (r == Null) return;
	r->content &= (0 << 0); // Mask all bits in register with 0
}


void setBit(int i, iRegister *r){
	if (r == Null) return;
	r->content |= ~(1 << i);	
}


void setAll(iRegister *r) {
	if (r == Null) return;
	r->content |= ~(0 << 0); // OR all bits with 1
}


int getBit(int i, iRegister r*) {
	if (i > 31 || i < 0) return;
	if (r == Null) return;
	return ((r->content) & ( 1 << i )) >> i; // Mask out the bit, then shift it to the far right so it gets returned as the integer
}


// Might be false, verify with test
void assignNibble(int start, int value, iRegister *r) {
	if(start > 29) return;
	if (r == Null) return;
	r->content &= ~(15 << start); 
	r->content |= (value << start);
}


int getNibble(int start, iRegister *r) {
	if(start > 29) return;
	if (r == Null) return;
	return ((r->content) & ( 15 << start )) >> start;
}


//FIXME: Will eventually fill up all memory space if called too much.
char *reg2str(iRegister *r) {
	register = (char*) malloc(sizeof(char) * 32);
	
	int i;
	
	for(i = 0; i < 31){
		if(getBit(i,r)){
			register[i] = 49;
		} else register[i] = 48;
	}
	
	return register;
}


void shiftRight(int i, iRegister *r) {
	if (i > 31 || i < 0) return;
	if (r == Null) return;
	r->content = (r->content >> i);
}


void shiftLeft(int, iRegister *r) {
	if (i > 31 || i < 0) return;
	if (r == Null) return;
	r->content = (r->content << i);
}


void resetBit(int i, iRegister *r) {
	if (r == Null) return;
	r->content &= ~(1 << i);
}
