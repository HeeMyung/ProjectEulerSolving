#include "prime.h"
#include <stdio.h>
#include <time.h>

int main()
{
	HeeM::Primes prime;
	prime.Init(8);
	srand(time(NULL));
	for(int i = 0; i < 10; ++i)
	{
		long long check = rand()%100;
		
		printf("%lld -> %s\n", check, prime.IsPrime(check) ? "prime" : "not prime");
	}
}

