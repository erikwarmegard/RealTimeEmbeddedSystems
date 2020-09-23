To run this CUnit test you will need to download the sourceForge compiler. 
We ran it on Linus with the raspberry pi 3.
You will need to have the files exponential.c and exponential.h

-To be able to run it you must perform a default setup and update everything!

to compile it do:
gcc -Wall -I$HOME/local/include/CUnit myTest.c exponential.c -L$HOME/local/lib -lcunit -0 myTest

ro run:
LD_LIBRARY_PATH=$HOME/local/lib ./myTest
