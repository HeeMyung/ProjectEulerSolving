#include <stdio.h>
#include "common.h"

int main()
{
	long long n = 16;
	long long r = 2;
	printf("factorial(%lld) : %lld\n", n, HeeM::factorial(n));
	printf("%lld combination %lld : %lld\n", n, r, HeeM::combination(n, r));
	printf("%lld power %lld : %lld\n", n, r, HeeM::power(n, r));
}
