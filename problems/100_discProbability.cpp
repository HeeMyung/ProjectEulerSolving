#include "bigint.h"
#include <stdio.h>

int main()
{
	BigInt one = BigInt(1000000000)*BigInt(1000000000);

	BigInt y = one * 20;
	BigInt x = one * 14;
	BigInt zero = BigInt(0);
	BigInt add = one;
	BigInt prevx = one * 2,prevy = one * 3;
	printf("%s %s\n", (const char*)x, (const char*)y);
	while(1)
	{
		BigInt a = x * (x + one) * 2;
		BigInt b = y * (y + one);
		if( b > a )
		{
			//printf("y decreased :%s\n", (const char*)y);
			y = y - one;
		}
		else if( b < a )
		{
			//printf("x decreased :%s\n", (const char*)x);
			x = x - one;
		}
		else
		{	
			printf("matched (%s, %s)\n", (const char*)(x/one), (const char*)(y/one));
			//printf("prevData (%s, %s)\n", (const char*)prevx, (const char*)prevy);
			BigInt tempx = x * one, tempy = y * one;
			//printf("tempData (%s, %s)\n", (const char*)tempx, (const char*)tempy);
			BigInt ratiox = tempx / prevx, ratioy = tempy / prevy;
			prevx = x;
			prevy = y;
			x = x * ratiox / one;
			x.fillWith(18, 0);	
			y = y * ratioy / one;
			y.fillWith(18, 0);
			//printf("next (%s, %s)\n", (const char*)x, (const char*)y);
		}
	}
	return 0;
}
