#include <stdlib.h>
#include <stdio.h>
#include "exponential.h"

int main() {
	ExpStruct *e1 = (ExpStruct *) malloc(sizeof(ExpStruct));

	e1 = iexp(2);
	printExp(e1);
	
	return 0;
}
