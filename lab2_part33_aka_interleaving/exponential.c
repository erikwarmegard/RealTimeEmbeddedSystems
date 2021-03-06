#include <stdlib.h>
#include <stdio.h>
#include "exponential.h"
#include <math.h>
#include <rpi3.h>


int led=0;
void blinkLed(void){
        if(led==1) {GPIO->GPCLR0 = (1 << 16); led=0;}
	else{GPIO->GPSET0 = (1 << 16); led=1;}
	
}

void delay(long unsigned int delayTime) {
    long unsigned int i = 0;
    while(i <= delayTime){
        i++;
	//if(i % (delayTime/8) ==1){blinkLed();}
    }
    return;
}

unsigned long int factorial(int number){
	if(number == 0) {
		return 1;
	}
	if(number < 0) {
		return 1;
	}
	int answer = 1;
	int i;
	for(i = number; i > 0; i--){
		answer *= i;
	}
	return answer;
}


unsigned long int power(int base, int expo) {
	if(expo>21) {
		return -1;
	}
	int answer = 1;
	for(int i = 0; i < expo; i++) {
		answer *=base;
	}
	return answer;
}


double calculateExponant(int n){ //calc exponent
	double dExponent = 1.0; //for i=0 (always 1)

	for(int i=1; i < (n+1) ;i++){
		delay(4000000); //M. visualize: delay to visualize the growing behavior of n+1 with out eyes
		double factor =factorial(i);
		dExponent +=((power(n,i) / factor));
		blinkLed(); //M. visualize: need to add blindLed() ->interleaving achived
	}
	return dExponent;
}


ExpStruct *iexp(int n) {
	ExpStruct * exponent = malloc(sizeof(ExpStruct));

	if(n>21) {
		exponent->expInt = 0;
		exponent->expFraction = 0;
		return exponent;
	}

	double fractionValue = calculateExponant(n); //call to: gets the exponent for n
	double value= 1.0;

	exponent->expFraction = modf(fractionValue, &value)*100.0;
	exponent->expInt = (int) value;
	return exponent;
}

char* expo2string(ExpStruct * exp){
		char * temp = malloc(sizeof(char)*32); //pointer to store the string in
		sprintf(temp, "%d.%02d",exp->expInt,exp->expFraction); //adress so where our string/char[] is stored (remeber to free)
		return temp;

}
