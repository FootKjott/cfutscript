#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "futscript.h"

int main()
{
	color c;
	c.r = 0;
	c.g = 0;
	c.b = 0;
	printf("start");
	
	printf("\ndone=%d", waitforpxnot(0, 0, c, 10, 10));

	return 0;
}