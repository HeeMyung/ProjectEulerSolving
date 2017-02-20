#include<stdio.h>
#include "prime.h"

long long Test(long long a, long long n)
{
	if( n % 2 == 0 )
		return 2;
	else
		return ((2*a*n) % (a*a));
}

int main()
{
	HeeM::Primes p;
	p.Init(6);
	long long answer = 0;
	const auto& pVec = p.GetPrimes();
	for(size_t iter = 0; iter < pVec.size(); ++iter)
	{
		long long i = pVec[iter];
		long long t = Test(i, (long long)(iter+1));
		printf("Test(%lld) : %lld.. (%lld^%lu + %lld^%lu) %% %lld == %lld\n", i, t, i-1, iter+1, i+1, iter+1, i*i, t);
		if( t > 10000000000 )
		{
			answer = iter + 1;
			break;
		}
	}
	printf("Answer:%lld\n", answer);
}
