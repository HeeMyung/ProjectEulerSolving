#include <stdio.h>

#define ABS(a) ( a > 0 ? a : -a )
#define NORMAL(a)	(a / ABS(a))
bool isBouncyNumber(int n)
{
	int direction = 0;
	while(n >= 10)
	{
		int next = ((n%10)-((n/10)%10));
		if( next * direction < 0 )
			return true;
		else if( next != 0 && direction == 0 )
		{
			direction = NORMAL(next);
		}
		n /= 10;
	}
	return false;
}

int main()
{
	int testSet[5] = {133478, 564233, 98211, 20406, 14799};
	int bouncyCount = 0, noBouncyCount = 0;
	int n = 1;
	while(true)
	{
		if( isBouncyNumber(n) )
		{
			//printf("%d is BouncyNumber\n", testSet[i]);
			bouncyCount++;
		}
		else
		{
			//printf("%d is not BouncyNumber\n", testSet[i]);
			noBouncyCount++;
		}
		if( bouncyCount == noBouncyCount )
		{
			printf("50%% point! %d\n", n);
		}
		else if( bouncyCount == 9 * noBouncyCount )
		{
			printf("90%% point! %d\n", n);
		}
		else if( bouncyCount == 99 * noBouncyCount)
		{
			printf("99%% point! %d\n", n);
			break;
		}
		++n;
	}
}
