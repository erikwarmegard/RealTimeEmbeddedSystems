#include <stdlib.h>
#include <stdio.h>
#include "exponential.h"

#include <CUnit.h>
#include <Basic.h>

int init_suite(void) {return 0;}
int clean_suite(void) {return 0;}

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
	//ExpStruct *e1 = (ExpStruct *) malloc(sizeof(ExpStruct));
	//e1 = iexp(2);
	//printExp(e1);
	
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
	
	// Add test iexp function in Suite1
	if((NULL == CU_add_test(pSuite1, "\n\n...Testing iexp function...\n\n",test_iexp))){
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	// Add test power function in Suite1
	if((NULL == CU_add_test(pSuite1, "\n\n...Testing power function...\n\n",test_power))){
		CU_cleanup_registry();
		return CU_get_error();
	}

	// Add test factorial function in Suite1
	if((NULL == CU_add_test(pSuite1, "\n\n...Testing factorial function...\n\n",test_factorial))){
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_run_tests(); // Output to the screen
	
	CU_cleanup_registry();
		
	return CU_get_error();
}
