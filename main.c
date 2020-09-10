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
  
  
  /* TEST: reg2str(iRegister *r) */ //TODO: Make this with assert, if possible
  /*Test 1. Test by printing the characters at the pointer location*/
  resetAll(&r);
  assignNibble(23,15,&r);
  char *pointer = reg2str(&r);
 
  char *end = pointer + 31;
  char *index = pointer;
  int i = 31; //format printer
  while(end >= index) {
    printf("%d: %c\n",i,*end);
    i--;
    end--;
  }
  /*Test 2.*/
  
  /* TEST: shiftRight(int i, iRegister *r)  JOHAN -precis klar*/ 
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
  
  /*3. If  you  want to right shift: 32+ steps => Do nothing (r is unchanged)*/
  int registerBefore =r.content;
  int registerAfterwards =0;
  shiftRight(32, &r);
  registerAfterwards = r.content;
  assert(registerAfterwards==registerBefore);
  
  /*4. If  you  want to right shift, less than: (-1) steps => Do nothing (r is unchanged)*/
  registerBefore =r.content;
  registerAfterwards =0;
  shiftRight(-1, &r);
  registerAfterwards = r.content;
  assert(registerAfterwards==registerBefore);  
  
  
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
  
  /*3. If  you  want to left shift: 32+ steps => Do nothing */
  registerBefore =0; //declared above
  registerAfterwards =0;
  registerBefore = r.content;
  shiftLeft(32,&r);
  registerAfterwards = r.content;
  assert(registerAfterwards==registerBefore);
  /*4. If  you  want to left shift, less than: (-1) steps => Do nothing */
  registerBefore = r.content;
  shiftLeft(-1,&r);
  registerAfterwards = r.content;
  assert(registerAfterwards==registerBefore);
  
  
  /* TEST: resetBit(int i, iRegister *r) */
  //TEST 1. Set everything to 1:s, than reset the i'th bit
  r.content |= ~(0 << 32);
  int bitToReset = 8;
  resetBit(bitToReset, &r);
  theBit = NULL;
  theBit = (r.content &(1 << bitToReset)); 
  theBit = theBit >> bitToReset;
  assert(theBit==0);
  //TEST 2. i input, bigger than 31 => should not change the content r.content
  int beforeValue = r.content;
  resetBit(33,&r);
  int afterValue =r.content;
  assert(beforeValue==afterValue);
      //assert(resetBit(33,&r)==-1); 
  
  //TEST 3. input i= -1 < 0: => does not result in a change of r.content
  beforeValue = r.content;
  resetBit(-1,&r);
  afterValue =r.content;
  assert(beforeValue==afterValue); //r.content should stay the same
   //TEST 4. ?
   
  printf ("\n");
  return 0;
}