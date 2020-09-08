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
 *   - Allocate memory for iRegister 
 *   - use setAll(r) to set all bits
 *   - printf to verify that all bits are set
 *   - use resetAll(r) to reset all bits 
 *   - printf to verify that all bits are reset
 *  2. No bits are set
 *   - Allocate memory for iRegister (calloc() to set the bits to zero)
 *   - printf to verify that all bits are zero
 *   - user resetAll(r) to reset all bits 
 *   - printf to verify that nothing has changed
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
 *  1. Bit input out of range
 *   - setBit(33,r)
 *   - Printf() an error
 *   - Return before effecting the register
 *
 *  2. Set three bits of register
 *   - Clear register with resetAll(r)
 *   - printf() to verify that all bits are zero.
 *   - setBit(0,r), setbit(3,r), setBit(7,r) 
 *   - getBit(0,r), getBig(3,r), getBig(7,r)
 *   - The three bits should be set
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
 *  1. Set all bits
 *   - Allocate memory for iRegister 
 *   - use setAll(r) to set all bits
 *   - printf to verify that all bits are set
 *   - use setAll(r) to set all bits
 *   - printf to verify that nothing has changed
 *
 *  2. No bits are set
 *   - Allocate memory for iRegister (calloc() to set the bits to zero)
 *   - printf to verify that all bits are zero
 *   - user setAll(r) to set all bits 
 *   - printf to verify that all bits are set 
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
 *  1. Bit input out of range
 *  - getBit(33,r)
 *  - Printf() an error
 *  - Return before reading the wrong bit
 *  2. Read the right bit
 *  - Allocate memory for iRegister (calloc() to set all to zero)
 *  - setBit(10,r)
 *  - getBit(10,r) should return 1 
 *  - printf() to verify
 */ 
int getBit(int, iRegister *);


/** @brief set the first (for pos=1) or the second (for pos=2) four bits of iRegsiter
 * 
 *  @param start is the lowest bit (position 1) 
 *
 *  @param value value of Nibble
 *
 *  @param r A pointer to a memory location of a iRegister data structure.
 *
 *  @return void
 * 
 *  Pre-condition: 0 <= start < 29, value != Null, 0 <= value < 16 and iRegister != Null
 *  Post-condition: iRegister != Null
 *  
 *  properties: After assignNibble(start,value,r). getNibble(start, r) = value 
 *  
 *  test-cases:
 *  1. Wrong input
 *  - assignNibble(33, 4, r)
 *  - Should return with error
 *  2. Validate insert
 *  - assignNibble(0,7,r)
 *  - getNibble(0,r) should be = 7
 */ 
void assignNibble(int, int, iRegister *);


/** @brief get the first (for pos=1) or the second (for pos=2) four bits of iRegsiter
 * 
 *  @param i start bit
 *
 *  @param r A pointer to a memory location of a iRegister data structure.
 *
 *  @return int (current state of that nibble)
 * 
 *  Pre-condition: 0 <= i < 32 and iRegister != Null
 *  Post-condition: iRegister != Null
 *  
 *  properties: 0 <= getNibble(i,r) < 15, getNibble(i,r) != Null
 *    
 *  test-cases:
 *  1. Get the correct Nibble
 *  - assignNibble(0,7,r)
 *  - print getNibble(0,r) to verify value is ...XXXX0111
 *  2. Index out of range
 *  - getNibble(30,r)
 *  - should return and provide error due to index > 29
 */ 
int getNibble(int, iRegister *);


/** returns a pointer to an array of 32 characters, with each character 
 *  representing the corresponding bit of the iRegister, i.e., if the bit is set,
 *  then the character is "1" (ASCII char with code 49), or otherwise is "0" 
 *  (ASCII char with code 48)
 */
char *reg2str(iRegister *);


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
 *  1. Division by two
 *  - Allocate memory for iRegister r
 *  - setBit(3,r)
 *  - printf() to verify that register equals "8"
 *  - shiftRight(1,r)
 *  - printf() to verify that register equals "4" (divided by two)
 *   
 *  2. Control most significant bit (In case of signed integer)
 *  - Allocate memory for iRegister r
 *  - setBit(3,r)
 *  - shiftRight(1,r)
 *  - getBit(31,r) should be 0 
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
 *  1. Multiplication by two
 *  - Allocate memory for iRegister r
 *  - setBit(2,r)
 *  - printf() to verify that register equals "4"
 *  - shiftLeft(1,r)
 *  - printf() to verify that register equals "8" (multiply by two) 
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
 *  1,2,3. Allocate memory to an iRegister r
 *  first do resetAll(&r),
 *  then set the i'th bit of &x by setBit(i, &r) for i = 0, 15 and 23 and then
 *  display the result after each and every call by 
 *    printf("%s",reg2str(r)) 
 */
void resetBit(int, iRegister *);

#endif
