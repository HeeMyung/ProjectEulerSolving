#include "prime.h"
#include <math.h>

namespace HeeM
{
	long long power(long long n, long long r)
	{
		if( r <= 0 )
		{
			return 1;
		}
		return power(n, r-1) * n;
	}
	void Primes::Init(int limit )
	{
		primeList.clear();
		long long rLimit = power((long long)10, limit);
		mapLimit = rLimit;
		primeField.resize(rLimit);
		long long count = 0;
		for(long long x = 2; x < rLimit; x++)
		{
			if( primeField[x] )
				continue;
			else
			{
				//printf("found prime : %lld\n", x);
				primeList.push_back(x);
				for(long long i = x * x; i < rLimit; i+=x)
				{
					primeField[i] = true;
				}
			}
		}
	}
	const std::vector<long long>& Primes::GetPrimes()
	{
		return primeList;
	}
	bool Primes::IsPrime(long long n)
	{
		if( n < mapLimit )
			return primeField[n] == false;
		else if( mapLimit * mapLimit < n )
		{
			printf("계산범위를 초과하였습니다. limit:%lld, n:%lld\n", mapLimit * mapLimit , n);
			return false;
		}

		for(std::vector<long long>::iterator iter = primeList.begin(); iter != primeList.end() && sqrt(*iter) >= *iter; ++iter)
		{
			if( n % *iter == 0 )
			{
				return true;
			}
		}
		return false;
	}
}
