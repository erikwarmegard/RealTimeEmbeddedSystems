#include <stdlib.h>
#include <stdio.h>
#include "exponential.h"
#include <math.h>

int main() {
	ExpStruct *e1 = (ExpStruct *) malloc(sizeof(ExpStruct));

	
	for(int i=1; i<10; i++){
		
		e1 = iexp(i);
		double realEXP =exp(i);
		printf("%d: %d.%d, \t real: %f \n",i,e1->expInt,e1->expFraction, realEXP);
		free(e1);
	}
	
	return 0;
}
