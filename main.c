//  Created by Mohammadreza Mousavi [mohmou] on 9/5/14.
//  Updated by Masoumeh Taromirad on 11/08/16.
//  Updated by Wagner Morais and Johannes van Esch on 28/08/18.
//  Copyright (c) 2014 by Mohammadreza Mousavi [mohmou]. All rights reserved.

#include <stdlib.h>
#include <stdio.h>
#include <assert.h> 
#include "iregister.h"

int main ()
{
  iRegister r;
  char out[33];

  /* Put all your test cases for the implemented functions here */
  
  /* TEST: setAll(iRegister *r)*/
  setAll(&r);
  assert(r.content == (-1));
 
  /* TEST: resetAll(iRegister *r)*/
  r.content = (-1);
  assert(r.content == (-1));
  resetAll(&r);
  assert(r.content == 0);
  
  
  
  
  printf ("\n");
  return 0;
}
