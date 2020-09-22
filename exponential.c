#include <stdlib.h>
#include <stdio.h>
#include "exponential.h"
#include <math.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

int init_suite(void) {return 0;}
int clean_suite(void) {return 0;}

double factorial(int number){
	if(number == 0) {
		return 1;
	}
	
	if(number < 0) {
		printf("Negative input!");
		return -1;
	}
	
	double answer = 1;
	
	int i = 1;
	for(i = number; i > 0; i--){
		answer *= i;
	}
	return answer;
}


double power(double base, double expo) {
	if(expo>21) {
		return -1;
	}
	double answer = 1;
	for(int i = 0; i < expo; i++) {
		answer *=base;
	}
	return answer;
}


ExpStruct *iexp(int n) {
	ExpStruct * exponent = (ExpStruct *) malloc(sizeof(ExpStruct));

	if(n>21) { 
		exponent->expInt = -1;
		exponent->expFraction = 0;
		return exponent;
	}

	double dExponent = 1; //
	double value = 1.0;
	
	for(int i=1; i<10;i++){
		int factor =factorial(i);
		dExponent +=((power(n,i)/factor));
	}
	
	exponent->expFraction = modf(dExponent, &value)*100;
	exponent->expInt = (int) value;
	return exponent;
}


void printExp(ExpStruct * e){
	printf("Exponent: %d.%d\n", e->expInt, e->expFraction);
}


int sum(int a, int b) {
	return (a + b);
}

void test_factorial() {
	/* 1. 0 as input */
	CU_ASSERT(1 == factorial(0));
	/* 2, Negative input */
	CU_ASSERT(-1 == factorial(-1));
	/* 3. Function returns a mathematically correct value */
	CU_ASSERT(120 == factorial(5));
}	

void test_power() {
	/* 1. Function returns a mathematically correct value */
	CU_ASSERT(32 == power(2,5));
	/* 2. Exponent is 0 */
	CU_ASSERT(1 == power(2,0));
	/* 3. Base is 0 */
	CU_ASSERT(0 == power(0,2));
	/* 4. Exponent is two large */
	CU_ASSERT(-1 == power(2,9999999));
}	

void test_iexp() {
	ExpStruct *e1 = (ExpStruct *) malloc(sizeof(ExpStruct));
	
	/* 2. Function calculates the math correctly */
	e1 = iexp(2);
	CU_ASSERT(7 == e1->expInt);
	CU_ASSERT(38 == e1->expFraction);
	
	/* 3. Input parameter is very large */
	e1 = iexp(23);
	CU_ASSERT(-1 == e1->expInt);
	CU_ASSERT(0 == e1->expFraction);
	
	/* 4. Input parameter is 0 */
	e1 = iexp(0);
	CU_ASSERT(1 == e1->expInt);
	CU_ASSERT(0 == e1->expFraction);
	
	free(e1);
}


int main() {
	ExpStruct *e1 = (ExpStruct *) malloc(sizeof(ExpStruct));

	e1 = iexp(2);
	printExp(e1);
	
	CU_pSuite pSuite1 = NULL;
	
	// Initialize CUnit test registry
	if(CUE_SUCCESS != CU_initialize_registry()){
		return CU_get_error();
	}
		
	// Add suite1 to registry
	pSuite1 = CU_add_suite("Basic_Test_Suite1", init_suite, clean_suite);
	if(NULL == pSuite1) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	// Add test iexp function
	if((NULL == CU_add_test(pSuite1, "\n\n...Testing iexp function...\n\n",test_iexp))){
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	// Add test power function
	if((NULL == CU_add_test(pSuite1, "\n\n...Testing power function...\n\n",test_power))){
		CU_cleanup_registry();
		return CU_get_error();
	}

	// Add test factorial function
	if((NULL == CU_add_test(pSuite1, "\n\n...Testing factorial function...\n\n",test_factorial))){
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_run_tests(); // Output to the screen
	
	CU_cleanup_registry();
		
	return CU_get_error();
}
