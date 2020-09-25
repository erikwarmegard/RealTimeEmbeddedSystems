#include <stdio.h>

struct expStruct {
int expInt;
int expFraction;
};

typedef struct expStruct ExpStruct;


ExpStruct *iexp(int);

char * expo2string(ExpStruct * exp); //new
