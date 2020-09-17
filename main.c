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
  resetAll(NULL);
  // Should not resolve in error!

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
  /* 4. iRegister is NULL */
  setAll(NULL);
  // Should not resolve in error


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
  /* TEST: assignNibble(int pos, int value, iRegister *r)*/
  /* 1. Assign the first nibble */
  r.content = 0;
  int startPos = 1;
  int theValue = 14;
  assignNibble(startPos, theValue, &r);
  int theNibble = (r.content & (theValue << (startPos-1)*4) );
  theNibble = (theNibble >> (startPos-1)*4);
  assert(theNibble == theValue);
  /* 2. Assign the last nibble */
  r.content = 0;
  startPos = 8;
  theValue = 14;
  assignNibble(startPos, theValue, &r);
  theNibble = NULL;
  theNibble = (r.content & (theValue << (startPos-1)*4));
  theNibble = ((unsigned)theNibble >> (startPos-1)*4);
  assert(theNibble == theValue);
  /* 3. Assign with all zeros */
  r.content = 0;
  startPos = 2;
  theValue = 0;
  assignNibble(startPos, theValue, &r);
  theNibble = NULL;
  theNibble = (r.content & (theValue << (startPos-1)*4));
  theNibble = (theNibble >> (startPos-1)*4);
  assert(theNibble == theValue);
  /* 4. Assign with all ones */
  resetAll(&r);
  startPos = 4;
  theValue = 15;
  assignNibble(startPos,theValue,&r);
  theNibble = NULL;
  theNibble = (r.content & (theValue << (startPos-1)*4));
  theNibble = (theNibble >> (startPos-1)*4);
  assert(theNibble == theValue);

  /* TEST: getNibble(int pos, iRegister *r) */
  /* 1. Get the second nibble */
  r.content = 0;
  r.content = (15 << 4);
  assert(getNibble(2,&r) == 15); //fetch nibble 2 and check =15.
  /* 2. Get the last nibble */
  r.content = 0xF0000000;
  int aNibble = getNibble(8,&r); //8: is the lsat nibble (input:1-8).
  assert(aNibble == 15);
  /* 3. Try to get nibble out of range */
  r.content = 0;
  assert(getNibble(10, &r) == NULL);
  /* 4. Get nibble, all other bits should remain unchanged */
  r.content = 0;
  r.content = 0x000000F0;
  getNibble(4,&r);
  assert(r.content == 0x000000F0);

  
  /*TEST: reg2str(iRegister *r) */ //TODO: Make this with assert, if possible
  /*1. Test by printing the characters at the pointer location*/
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
  /*Test 2. THIS MIGHT BE HARD TO DO WITHOUT ANY DIRECTION FROM THE TEACHER*/
  /*Test 3. THIS MIGHT BE HARD TO DO WITHOUT ANY DIRECTION FROM THE TEACHER*/
  /*Test 4. THIS MIGHT BE HARD TO DO WITHOUT ANY DIRECTION FROM THE TEACHER*/

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
  //1. Set everything to 1:s, than reset the i'th bit
  r.content |= ~(0 << 32);
  int bitToReset = 8;
  resetBit(bitToReset, &r);
  theBit = NULL;
  theBit = (r.content &(1 << bitToReset));
  theBit = theBit >> bitToReset;
  assert(theBit==0);
  //2. i input, bigger than 31 => should not change the content r.content
  int beforeValue = r.content;
  resetBit(33,&r);
  int afterValue =r.content;
  assert(beforeValue==afterValue);
  //3. input i= -1 < 0: => does not result in a change of r.content
  beforeValue = r.content;
  resetBit(-1,&r);
  afterValue =r.content;
  assert(beforeValue==afterValue); //r.content should stay the same
   //4. set all bits to 0. set the bit nr.3 till 0, kolla så att bit 3 + samtliga bitar =0
  r.content =0x0;
  resetBit(3,&r);
  assert((r.content &(1 << 2))==0); // the 3:rd bit should we 0 not 1
  for(int i=0; i<32; i++){
    assert((r.content &(1 << i))==0);
  }

  printf ("\n");
  return 0;
}
