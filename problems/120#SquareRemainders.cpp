#include<stdio.h>

int Test(int a, int& b)
{
	int max = 0;
	for(int i = 1; i < 2 * a; i += 2)
	{
		//printf("a*i : %d, 나머지:%d\n", 2*a*i, (2*a*i)%(a*a));
		int x = ((2*a*i) % (a*a));
		if( max < x )
		{
			max = x;
			b = i;
		}
	}
	return max;
}

int main()
{
	long long sum = 0;
	for(int i = 3; i <= 1000; ++i)
	{
		int x;
		int t = Test(i, x);
		printf("Test(%d) : %d.. (%d^%d + %d^%d) %% %d == %d\n", i, t, i-1, x, i+1, x, i*i, t);
		sum += t;
	}
	printf("Answer:%lld\n", sum);
}
