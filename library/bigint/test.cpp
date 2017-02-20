#include "bigint.h"
#include <stdio.h>

int main()
{
	BigInt i, j;
	i =	1000000000;
	i = i * 100000000;
	printf("%s\n", (const char*) i);
	j = 200000000;
	i = i / j;
	printf("%s\n", (const char*)i);
	return 0;
}
