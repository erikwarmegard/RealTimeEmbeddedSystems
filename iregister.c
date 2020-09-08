//  Created by Mohammadreza Mousavi [mohmou] on 9/5/14.
//  Updated by Masoumeh Taromirad on 11/08/16.
//  Updated by Wagner Morais and Johannes van Esch on 28/08/18.
//  Copyright (c) 2014 by Mohammadreza Mousavi [mohmou]. All rights reserved.
 
#include <stdlib.h>
#include <stdio.h>
#include "iregister.h"

void resetBit(int i, iRegister *r) {
  r->content &= ~(1 << i);
}


void resetAll(iRegister *r){
 if(r==Null) return;
 //fetch the register r into a variable
 //AND OperATION: with 0 in all 32 bit => to clear them
 //insert the value in r 
 
}


void setBit(int, iRegister *);