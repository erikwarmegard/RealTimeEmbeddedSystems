//  Created by Mohammadreza Mousavi [mohmou] on 9/5/14.
//  Updated by Masoumeh Taromirad on 11/08/16.
//  Updated by Wagner Morais and Johannes van Esch on 28/08/18.
//  Copyright (c) 2014 by Mohammadreza Mousavi [mohmou]. All rights reserved.

#include <stdlib.h>
#include <stdio.h>
#include "iregister.h"

int main ()
{
  iRegister r;
  char out[33];

  /* Put all your test cases for the implemented functions here */

 //resetAll()
 setAll(&r);
 resetAll(&r)
 int i;
 for(i=0; i<32;i++){
   if(getBit(i,&r)!=0){
    	printf("error")
	break;
   }
}


  printf ("\n");
  return 0;
}
