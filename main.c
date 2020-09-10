//  Created by Mohammadreza Mousavi [mohmou] on 9/5/14.
//  Updated by Masoumeh Taromirad on 11/08/16.
//  Updated by Wagner Morais and Johannes van Esch on 28/08/18.
//  Copyright (c) 2014 by Mohammadreza Mousavi [mohmou]. All rights reserved.

#include <stdlib.h>
#include <stdio.h>
#include <assert.h> 
#include "iregister.h"

int main ()
{
  iRegister r;
  char out[33];

  /* Put all your test cases for the implemented functions here */
  
  /* TEST: setAll(iRegister *r) */
  setAll(&r);
  assert(r.content == (-1));
 
  /* TEST: resetAll(iRegister *r) */
  r.content = (-1);
  assert(r.content == (-1));
  resetAll(&r);
  assert(r.content == 0);
  
  /* TEST: setBit(int i, iRegister *r) */
  resetAll(&r);
  assert(r.content == 0);
  setBit(4,&r);
  unsigned int theBit = (r.content & (1 << 4));
  theBit = (theBit >> 4);
  assert(theBit == 1);
  
  /* TEST: getBit(int i, iRegister *r) */
  resetAll(&r);
  r.content |= (1 << 8);
  
  for(int i = 0; i < 32; i++){
    if(i == 8) assert(getBit(i,&r) == 1);
    else assert(getBit(i,&r) == 0);
  }
  
  /* TEST: assignNibble(int start, int value, iRegister *r)*/
  resetAll(&r);
  int theValue = 14;
  int startBit = 23;
  assignNibble(startBit,theValue,&r);
  unsigned int theNibble = (r.content & (theValue << startBit));
  theNibble = (theNibble >> startBit);
  assert(theNibble == theValue);
  
  /* TEST: getNibble(int start, iRegister *r) */
  resetAll(&r);
  r.content = (15 << 4);
  assert(getNibble(4, &r) == 15);
  
  // TODO: Make this with assert, if possible
  /* TEST: reg2str(iRegister *r) */
  resetAll(&r);
  assignNibble(23,15,&r);
  char *pointer = reg2str(&r);
  
  
  char *end = pointer + 31;
  char *index = pointer;
  
  int i = 31;
  while(end >= index) {
    printf("%d: %c\n",i,*end);
    i--;
    end--;
  }
  
  /* TEST: shiftRight(int i, iRegister *r) */
  /* 1. Logic control, division by two */
  resetAll(&r);
  int oldValue = r.content = (1 << 3);
  shiftRight(1,&r);
  int newValue = r.content;
  assert(newValue == (oldValue / 2));

  /* 2. MSB should be 0 */
  resetAll(&r);
  shiftRight(31, &r);
  int MSB = r.content & (1 << 31);
  MSB = MSB >> 31;
  assert(MSB == 0);
  
  /* TEST: shiftLeft(int i, iRegister *r) */
  /* 1. Logic control, multiplication by two */
  resetAll(&r);
  oldValue = NULL;
  newValue = NULL;
  oldValue = r.content = (1 << 3);
  shiftLeft(1,&r);
  newValue = r.content;
  assert(newValue == (oldValue * 2));
  
  /* 2. LSB should be 0*/
  r.content |= ~(0 << 32);
  shiftLeft(31, &r);
  int LSB = r.content & (1 << 0);
  assert(LSB == 0);
  
  
  /* TEST: resetBit(int i, iRegister *r) */
  r.content |= ~(0 << 32);
  int bitToReset = 8;
  resetBit(bitToReset, &r);
  theBit = NULL;
  theBit = (r.content &(1 << bitToReset)); 
  theBit = theBit >> bitToReset;
  assert(theBit==0);
  
  
  printf ("\n");
  return 0;
}
s