#include "prime.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
	HeeM::Primes prime;
	prime.Init(7);
	srand(time(NULL));
	for(int i = 0; i < 10; ++i)
	{
		long long check = rand()%100;
		
		printf("%lld -> %s\n", check, prime.IsPrime(check) ? "prime" : "not prime");
	}

	for(int i = 0; i < 100; ++i)
	{
		printf("%dth prime is : %lld\n", i+1, prime[i]);
	}

	bool cop = prime.IsCoprime(5, 27);
	bool cop2 = prime.IsCoprime(27, 32);
	bool cop3 = prime.IsCoprime(5, 32);
	long long rad = prime.Rad(4320);
	printf("%s, %s, %s, %lld\n", cop ? "true" : "false", cop2 ? "true" : "false", cop3 ? "true" : "false", rad);
}

