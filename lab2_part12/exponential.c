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
	double answer = 1;
	for(int i = 0; i < expo; i++) {
		answer *=base;
	}
	return answer;
}


ExpStruct *iexp(int n) {
	ExpStruct * exponent = (ExpStruct *) malloc(sizeof(ExpStruct));

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

void test_sum() {
		CU_ASSERT(5 == sum(3,2));
		//CU_ASSERT(
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
	
	// Add test1 to suite1
	if((NULL == CU_add_test(pSuite1, "\n\n...Testing Sum function...\n\n",test_sum))){
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	CU_basic_run_tests(); // Output to the screen
	
	CU_cleanup_registry();
		
	return CU_get_error();
}
