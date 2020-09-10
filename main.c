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
  
  /* TEST: resetAll(iRegister *r) */
  /* 1. All bits are set */
  r.content = (-1);
  assert(r.content == (-1));
  resetAll(&r);
  assert(r.content == 0);
  /* 2. No bits are set */
  r.content = 0;
  resetAll(&r);
  assert(r.content == 0);
  /* 3. iRegister is NULL */
  
  /* 4. Half of the bits are set from start*/
  r.content = 0xFFFF0000;
  resetAll(&r);
  assert(r.content == 0);
    
  /* TEST: setAll(iRegister *r) */
  /* 1. All bits are set*/
  r.content = 0xFFFFFFFF;
  setAll(&r);
  assert(r.content == 0xFFFFFFFF);
  /* 2. All bits are zero*/
  r.content = 0;
  setAll(&r);
  assert(r.content == 0xFFFFFFFF);
  /* 3. Half of the bits are one*/
  r.content = 0xFFFF0000;
  setAll(&r);
  assert(r.content == 0xFFFFFFFF);
  /* 4. */
 
  
  /* TEST: setBit(int i, iRegister *r) */
  /* 1. Bit that should be set is already set */
  r.content = 0x00000002;
  setBit(2,&r);
  unsigned int theBit = (r.content & (1 << 2));
  theBit = (theBit >> 2);
  assert(theBit == 1);
  /* 2. Bit that should be set is zero */
  r.content = 0;
  setBit(1,&r);
  theBit = NULL;
  theBit = (r.content & (1 << 1));
  theBit = (theBit >> 1);
  assert(theBit == 1);
  /* 3. Set the first bit of iRegister */
  r.content = 0;
  setBit(0,&r);
  theBit = NULL;
  theBit = (r.content & (1 << 0));
  theBit = (theBit >> 0);
  assert(theBit == 1);
  /* 4. Set the last bit of iRegister */
  r.content = 0;
  setBit(31,&r);
  theBit = NULL;
  theBit = (r.content & (1 << 31));
  theBit = (theBit >> 31);
  assert(theBit == 1);
  
  /* TEST: getBit(int i, iRegister *r) */
  /* 1. Get 8th bit (set), all others should be the same*/
  r.content = 0;
  r.content |= (1 << 8);
  for(int i = 0; i < 32; i++){
    if(i == 8) assert(getBit(i,&r) == 1);
    else assert(getBit(i,&r) == 0);
  }
  /* 2. Get the first bit, all others should be the same */
  r.content = 1;
  for(int i = 0; i < 32; i++) {
    if(i == 0) assert(getBit(i,&r) == 1);
    else assert(getBit(i,&r) == 0);
  }
  /* 3. Get the last bit, all others should be the same */
  r.content = 0x80000000;
  int testBit;
  for(int i = 0; i < 32; i++) {
    testBit = getBit(i,&r);
    if(i == 31) assert(testBit == 1);
    else assert(getBit(i,&r) == 0);
  }
  /* 4. Get the 8th bit (zero), all others should be the same*/
  r.content = 0xFFFFFF7F;
  for(int i = 0; i < 32; i++){
    if(i == 7) assert(getBit(i,&r) == 0);
    else assert(getBit(i,&r) == 1);
  }
  /* TEST: assignNibble(int start, int value, iRegister *r)*/
  /* 1. Assign the first nibble */
  r.content = 0;
  int startBit = 0;
  int theValue = 14;
  assignNibble(startBit, theValue, &r);
  int theNibble = (r.content & (theValue << startBit));
  theNibble = (theNibble >> startBit);
  assert(theNibble == theValue);
  /* 2. Assign the last nibble */
  r.content = 0;
  startBit = 28;
  theValue = 14;
  assignNibble(startBit, theValue, &r);
  theNibble = NULL;
  theNibble = (r.content & (theValue << startBit));
  assert(theNibble == (theValue << startBit));
  /* 3. Assign with all zeros */
  r.content = 0;
  startBit = 4;
  theValue = 0;
  assignNibble(startBit, theValue, &r);
  theNibble = NULL;
  theNibble = (r.content & (theValue << startBit));
  theNibble = (theNibble >> startBit);
  assert(theNibble == theValue);
  /* 4. Assign with all ones */
  resetAll(&r);
  startBit = 4;
  theValue = 15;
  assignNibble(startBit,theValue,&r);
  theNibble = NULL;
  theNibble = (r.content & (theValue << startBit));
  theNibble = (theNibble >> startBit);
  assert(theNibble == theValue);
  
  /* TEST: getNibble(int start, iRegister *r) */
  /*TEST 1. resetBits => sets the second nibble to 0xF=1111 and checks with it's correct*/
  resetAll(&r);
  r.content = (15 << 4);
  assert(getNibble(4, &r) == 15);
  /*TEST 2*/
  
  /*TEST 3 trying to get/access the a Nibble, outside the 32 bit: you will get: NULL*/
  assert(getNibble(33, &r) == NULL);
  
  
  /*TEST 4 inputing start < 0 will result in no change att all*/
  assert(getNibble(-1, &r) == NULL);
  
  
  /* TEST: reg2str(iRegister *r) */ //TODO: Make this with assert, if possible
  /*Test 1. Test by printing the characters at the pointer location*/
  resetAll(&r);
  assignNibble(23,15,&r);
  char *pointer = reg2str(&r);
  
  
  char *end = pointer + 31;
  char *index = pointer;
  int i = 31; //used to format printf
  while(end >= index) {
    printf("%d: %c\n",i,*end);
    i--;
    end--;
  }
  /*Test 4. THIS MIGHT BE HARD TO DO WITHOUT ANY DIRECTION FROM THE TEACHER*/
  /*Test 3. THIS MIGHT BE HARD TO DO WITHOUT ANY DIRECTION FROM THE TEACHER*/
  /*Test 2. THIS MIGHT BE HARD TO DO WITHOUT ANY DIRECTION FROM THE TEACHER*/
  
  
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
