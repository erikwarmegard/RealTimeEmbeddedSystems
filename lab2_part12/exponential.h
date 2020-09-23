#include <stdio.h>

struct expStruct {
int expInt;
int expFraction;
};

typedef struct expStruct ExpStruct;


/** @brief Calculate the value of e^n with two degrees of precision (Using Taylor Series)
 * 
 * 	e^x = 1 + x/1! + x^2/2! + x^3/3! + ... 
 *
 *  @param n Exponent value of type integer 
 * 
 *  @return *ExpStruct A pointer to a new ExpStruct
 * 
 *  Pre-condition: n != Null
 * 
 *  Post-condition: After iexp(int), iexp(int) != Null
 *  
 *  Properties:
 *  when n > 0: iexp(int n) = e^n
 *  when n < 0: iexp(int n) = 1/e^n 
 *  when n = 0: iexp(int n) = 1
 * 
 *  test-cases: 
 *  1. Integer value n = 0
 *  2. Integer value n > 0
 *  3. Integer value n < 0
 *  4. Integer value n = Null
 */ 
 
ExpStruct *iexp(int);


/** @brief Print the exponent struct
 *
 *  @param e Pointer to the struct  
 * 
 *  @return void
 * 
 *  Pre-condition: e != Null
 * 
 *  Post-condition: After e is printed out on the console
 * 
 *  test-cases: 
 *  1. Struct parameter e != Null
 *  2. Struct parameter e = Null
 */ 
 
void printExp(ExpStruct *);

double factorial(int);

double power(double, double);
