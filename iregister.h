//  Created by Mohammadreza Mousavi [mohmou] on 9/5/14.
//  Updated by Masoumeh Taromirad on 11/08/16.
//  Updated by Wagner Morais and Johannes van Esch on 28/08/18.
//  Copyright (c) 2014 by Mohammadreza Mousavi [mohmou]. All rights reserved.

#ifndef lab0_iregister_h
#define lab0_iregister_h

/**
 *  iRegister
 *  An iRegister is a structure which represents an 32-bit register and
 *  is equipped with standard operations to modify and display them.
 */
typedef struct{
    int content;
} iRegister;

/**
 *  Bellow you find the declarations for the functions to modify and display the
 *  memory content of a iRegister data structure. Before each declaration, a brief
 *  description about what the function shall do is given.
 *  Later in this file, the documentation for the resetBit function is given.
 *  Students should follow that format.
 */

/** @brief resets all the bits of the iRegister (to 0)
 *
 *  @param r A pointer to a memory location of a iRegister data structure.
 *
 *  @return void
 *
 *  Pre-condition: iRegister != Null
 *  Post-condition: after resetAll(r) all the bit of iRegister is 0
 *
 *  properties:
 *  After resetAll(r), (for 0 <= j < 32) => getBit(j, r) = 0
 *
 *  test-cases:
 *  1. All bits are set
 *  - set all bits to 1 (r.content = -1 = 0xFFFFFFFF)
 *  - assert that all bits are 1
 *  - resetAll(&r)
 *  - assert that all bits are 0
 *  2. No bits are set
 *  - set all bits to 0 (r.content = 0)
 *  - resetAll(&r)
 *  - assert that all bits remain as 0
 *  3. iRegister is NULL
 *  - resetAll(NULL) should not resolve in error
 *  4. Half of the bits are set from the start
 *  - set half the bits to 1 (r.content = 0xFFFF0000)
 *  - resetAll(&r)
 *  - assert that all bits are 0
 */
void resetAll(iRegister *);


/** @brief sets the i'th bit of the iRegister (to 1)
 *
 *  @param i The bit in the iRegister that will be set (to 1).
 *
 *  @param r A pointer to a memory location of a iRegister data structure.
 *
 *  @return void
 *
 *  Pre-condition: 0 <= i < 32 and iRegister != Null
 *  Post-condition: after setBit(i ,r) all the bit of iRegister should be the same except bit i'th, which is 1.
 *
 *  properties: After setBit(i,r), (for 0 <= j < 32) => getBit(i, r) = 1
 *
 *  test-cases:
 *  1. Bit that should be set is already set
 *  - set a bit manually (e.g r.content = 0x2)
 *  - setBit(2,&r)
 *  - mask out the bit from r.content
 *  - assert that the masked bit is set
 *  2. Bit that should be set is zero
 *  - set register to 0
 *  - setBit(1,&r)
 *  - mask out the bit from r.content
 *  - assert that the masked bit is set
 *  3. Set the first bit of iRegister
 *  - clear the register
 *  - setBit(0,&r)
 *  - mask out the first bit
 *  - assert that the first bit is set
 *  4. Set the last bit of iRegister
 *  - clear the register
 *  - setBit(31,&r)
 *  - mask out the bit from r.content
 *  - assert that the bit is set
 */
void setBit(int, iRegister *);


/** @brief setAll() the bits of the iRegister (to 1)
 *
 *  @param r A pointer to a memory location of a iRegister data structure.
 *
 *  @return void
 *
 *  Pre-condition: iRegister != Null
 *  Post-condition: after setAll(r) all the bit of iRegister is 1
 *
 *  properties: after setAll(r), for 0 <= j < 32 => getBit(j, r) = 1
 *
 *  test-cases:
 *  1. All bits are set
 *  - set all bits in register manually (r.content = 0xFFFFFFFF)
 *  - setAll(&r)
 *  - assert that all bits are still 1
 *  2. All bits are zero
 *  - reset all bits in register manually (r.content = 0)
 *  - setAll(&r);
 *  - assert that all bits are set
 *  3. Half of the bits are set
 *  - set half of the bits in the register
 *  - setAll(&r)
 *  - assert that all bits are set
 *  4. iRegister is NULL
 *  - resetAll(NULL) should not resolve in error
 */
void setAll(iRegister *);


/** @brief returns the i'th bit of the iRegister as an integer (1 if it is set, or 0 otherwise)
 *
 *  @param i is the bit in the iRegister that will be return.
 *
 *  @param r A pointer to a memory location of a iRegister data structure.
 *
 *  @return int (current state of the bit)
 *
 *  Pre-condition: 0 <= i < 32 and iRegister != Null
 *  Post-condition: after getBit(i ,r) all the bit of iRegister should be the same.
 *
 *  properties: setBit(1,r)=1, than after getBit(1,r), setBit(1,r)=1
 *
 *  test-cases:
 *  1. Get 8th (set), all others should be the same
 *  - set all bits to zero but the 8th bit manually
 *  - iterate through the register, assert that all but the 8th bit is zero
 *  2. Get the first bit, all others should be the same
 *  - set the first bit
 *  - iterate through the register, assert that all but the first bit is zero
 *  3. Get the last bit, all others should be the same
 *  - set the last bit in the register manually (r.content = 0x80000000)
 *  - iterate through the register, assert that all but the last bit is zero
 *  4. Get the 8th bit(zero), all others should be the same
 *  - Set all bits to 1 but the 8th bit manually (r.content = 0xFFFFFF7F)
 *  - iterate throught the register, assert that all but the 8th bit is 1
 */
int getBit(int, iRegister *);


/** @brief set the first (for pos=1) or the second (for pos=2) four bits of iRegsiter
 *
 *  @param pos can be 1-8 and represent which nibble you can to change.
 *
 *  @param value value of Nibble.
 *
 *  @param r A pointer to a memory location of a iRegister data structure.
 *
 *  @return void.
 *
 *  Pre-condition: 0 < pos < 9, value != Null, 0 <= value < 16 and iRegister != Null.
 *  Post-condition: iRegister != Null.
 *
 *  properties: After assignNibble(pos,value,r). getNibble(start, r) = value.
 *
 *  test-cases:
 *  1. Assign the first nibble (1)
 *  - clear the register
 *  - assignNibble(1, 14, &r)
 *  - Mask out the first nibble
 *  - assert that the nibble is 14
 *  2. Assign the last nibble (8)
 *  - clear the register
 *  - assignNibble(8, 14, &r)
 *  - mask out the last nibble
 *  - assert that the last nibble is 14
 *  3. Assign with all zeros
 *  - Clear the register
 *  - assignNibble(2,0,&r)
 *  - mask out the last nibble
 *  - assert that the last nibble is zero
 *  4. Assign with all ones
 *  - clear the register
 *  - assignNibble(4,15)
 *  - mask out the nibble
 *  - assert that the second nibble is all ones (15)
 */
void assignNibble(int, int, iRegister *);


/** @brief get the first (for pos=1) or the second (for pos=2) four bits of iRegsiter
 *
 *  @param i pos (of the nibble (1-8)).
 *
 *  @param r A pointer to a memory location of a iRegister data structure.
 *
 *  @return int (fetch a nibble = 4bits)
 *
 *  Pre-condition: 0 < pos < 9 and iRegister != Null
 *  Post-condition: iRegister != Null
 *
 *  properties: 0 <= getNibble(i,r) < 15, getNibble(i,r) != Null
 *
 *  test-cases:
 *  1. Get the second nibble
 *  - clear the register
 *  - set the second nibble
 *  - assert that getNibble(2,%r) is 15
 *  2. Get the last nibble
 *  - set the last nibble, clear the rest
 *  - assert that getNibble(8,&r) is 15
 *  3. Try to get a nibble out of range
 *  - clear the register
 *  - assert that getNibble(10,&r) is NULL
 *  4. Get a nibble, all other bits should remain unchanged
 *  - clear the register, set the second nibble
 *  - assert that the content  is unchanged after getNibble
 */
int getNibble(int, iRegister *);


/** @brief returns a pointer to an array of 32 characters, with each character
 *  representing the corresponding bit of the iRegister, i.e., if the bit is set,
 *  then the character is "1" (ASCII char with code 49), or otherwise is "0"
 *  (ASCII char with code 48)
 *  
 *  @param r An iRegister struct
 *
 *  @return Pointer to the start of the char array which represents the iRegister
 *
 *  Pre-condition: iRegister != NULL
 *  Post-condition: The allocated memory of the array != NULL
 *
 *  Properties: Allocates memory for 32 characters, last character is the null terminator.
 *
 *  test-cases:
 *  1. reg2str() should end at null terminator
 *  - set the iRegister content to a value 
 *  - create a pointer with reg2str() function 
 *  - iterate through the array until the null terminator arrives
 *  - assert that the function iterates 32 times
 *  2. reg2str() can print all ones 
 *  - set the iRegister content to all ones 
 *  - create a pointer with reg2str() function
 *  - iterate through the array until the null terminator arrives 
 *  - assert that all character all ones 
 *  3. reg2str() can print all zeros
 *  - set the iRegister content to all zeros 
 *  - create a pointer with reg2str() function
 *  - iterate through the array until the null terminator arrives 
 *  - assert that all character all zeros 
 *  4. reg2str() can print both ones and zeros
 *  - set the iRegister content to half zeros, half ones
 *  - create a pointer with reg2str() function
 *  - iterate through the array until the null terminator arrives 
 *  - assert that the first half of characters are ones, the rest are zeros  
 */
char *reg2str(iRegister);


/** @brief shifts all the bits of the iRegister to the right by n palces (appends 0
 *  from the left)
 *
 *  @param i is the amount of left-shift that will be performed
 *
 *  @param r A pointer to a memory location of a iRegister data structure.
 *
 *  @return void
 *
 *  Pre-condition: 0 <= i < 32 and iRegister != Null
 *  Post-condition: iRegister != Null
 *
 *  properties: reg2str(r) = 00000010, After shiftRight(1,r), reg2str(r) = 00000001. Division by two
 *
 *  test-cases:
 *  1. Division by two:
 *  - reset all bits to 0.
 *  - setBit(3,r) to 1.
 *  - shift Right 1 step.
 *  - assert to understand that 8 becomes 4.
 *
 *  2. Control most significant bit inserted is 0:
 *  - reset all bits to 0.
 *  - shift Right 31 steps
 *  - mask the last bit
 *  - assert that the last bit is 0 (not 1).
 *  3.
 *  - save the value register r.
 *  - shift right 32 (should result in: no change in r).
 *  - save the new value of r.
 *  - assert to check that old and new value are the same.
 *  4.
 *  - save the value register r.
 *  - shift right -1 (should result in => nothig!).
 *  - save the new value of r.
 *  - assert to check that old and new value are the same.
 */
void shiftRight(int, iRegister *);


 /** @brief shifts all the bits of the iRegister to the left by n palces (appends 0
 *  from the right)
 *
 *  @param i is the amount of left-shift that will be performed
 *
 *  @param r A pointer to a memory location of a iRegister data structure.
 *
 *  @return void
 *
 *  Pre-condition: 0 <= i < 32 and iRegister != Null
 *  Post-condition: iRegister != Null
 *
 *  properties: reg2str(r) = 00000001, After shiftLeft(1,r), reg2str(r) = 00000010. Multiplication by two
 *
 *  test-cases:
 *  1. Multiplication by two:
 *  -resetAll bits in r.
 *  -set r to 0x8
 *  -leftShift once
 *  -afterwards: assert to check that the newValue is the oldValue * 2
 *  2. LSB should be 0:
 *  -set all bits to 1.
 *  -than performs a leftShift
 *  -than controlls to see if the lowest bit is 0.
 *  3. leftShift more than 31.
 *  -stores the value of r.content.
 *  -tries to shift 32 bits.
 *  -controlls that no bits was changed (due to input being >31).
 *  4.
 *  -stores the value of r.content.
 *  -tries to shift -1 bits.
 *  -controlls that no bits was changed (due to input being negative).
 */
void shiftLeft(int, iRegister *);


/** @brief Resets the i'th bit of the iRegister (to 0)
 *
 *  @param i Is i'th bit of the iRegister to be reset
 *
 *  @param r A pointer to a memory location of a iRegister data structure.
 *
 *  @return void
 *
 *  Pre-condition: 0 <= i < 32 and iRegister != Null
 *
 *  Post-condition: after reset(i, r) the i'th bit of iRegister is 0, all other
 *  bits remain unchanged
 *
 *  properties:
 *  after resetBit(i, r),  getBit(i, r) = 0
 *  if getBit(i, r) == 0 then getBit(j, r) returns the same value for all 0 <= j < 32 and j <> i before and after resetBit(i, r)
 *
 *  test-cases:
 *  1.
 *  -set r to 0xFFFFFFFF (only 1:s)
 *  -reset bit nr 8.
 *  -mask out bit number 8.
 *  -Than: compare it to 0 (zero).
 *  2.
 *  -save the current value of r.
 *  -resets bit 33 (outside the register)
 *  -assert() to insure that the value of r is unchanged
 *  3.
 *  -save the current value of r.
 *  -resets bit -1 (outside the register)
 *  -assert() to insure that the value of r is unchanged
 *  4.
 *  -reset bits to 0.
 *  -resetBit -> 3.
 *  -assert to insure that bit 3 is set to 0.
 *  -Iterate and assert if all bits are 0.
 */
void resetBit(int, iRegister *);

#endif