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
    if(r->content != 0) {
      // exit(-1);
    }
}


void setBit(int i, iRegister *r){
	if ((i > 31) | (i < 0)) return;
	if (r == NULL) return;
	r->content |= (1 << i);
    int theBit = (r->content & (1 << i));
    theBit = (theBit >> i);
    if(theBit != 1) {
      // exit(-1);
    }
}


void setAll(iRegister *r) {
	if (r == NULL) return;
	r->content |= ~(0 << 0); // OR all bits with 1
	if(r->content != 0xFFFFFFFF) {
          // exit(-1);
        }
}


int getBit(int i, iRegister *r) {
        if (r == NULL) {
          return -1;
        }
	else if (i >= 32 || i < 0) {
          return -1;
        }
	else {
          int theBit = (unsigned int) ((r->content) & ( 1 << i )) >> i; // Mask out the bit, then shift it to the far right so it gets returned as the integer
          if(r == NULL) {
            // exit(-1); 
          }
          return theBit;
        }
}


void assignNibble(int pos, int value, iRegister *r) {
	if(0 > pos || pos > 9) return;
	if (r == NULL) return;
	r->content &= ~(15 << (pos-1) * 4); //removes the old nibble from the register
	r->content |= (value << (pos-1) * 4); //adds the new nibble
	if(r == NULL) { 
          // exit(-1);
        }
}


int getNibble(int pos, iRegister *r) {
	if(0 > pos || pos > 9) return NULL;
	if (r == NULL) return NULL;
	int theNibble = ((r->content) & ( (unsigned) 15 << (pos-1) * 4 )) >> (pos-1) * 4;
    if(r == NULL) { 
      // exit(-1);
    }
    return theNibble;
}


char *reg2str(iRegister r) {
	if(r == NULL) {
		return NULL;
	}
	char *reg = (char*) malloc(sizeof(char) * 33);	
	int i;
	for(i = 0; i < 32; i++){
		if(getBit(i,&r)){
			reg[i] = 49;
		} else reg[i] = 48;
	}
        reg[32] = '\0'; // To end the string
	if(r == NULL) {
		// exit(-1);
	}
	return reg;
}


void shiftRight(int i, iRegister *r) {
	if (i > 31 || i < 0) return;
	if (r == NULL) return;
    r->content =  r->content >> i;
	if(r == NULL) { 
          // exit(-1);
        }
}


void shiftLeft(int i, iRegister *r) {
	if (i > 31 || i < 0) return;
	if (r == NULL) return;
	r->content = (r->content << i);
	if(r == NULL) { 
          // exit(-1);
        }
}


void resetBit(int i, iRegister *r) {
    if (i > 31 || i < 0) return;
	if (r == NULL) return;
	r->content &= ~(1 << i);
    int theBit = (r->content & (1 << i));
    theBit = (theBit >> i);
    if(theBit != 0) {
      // exit(-1);
    }	
}
