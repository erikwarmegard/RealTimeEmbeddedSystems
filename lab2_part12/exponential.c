#include <stdlib.h>
#include <stdio.h>
#include "exponential.h"
#include <math.h>
#include <CUnit.h>
#include <Basic.h>


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


