#include "prime.h"
#include <math.h>
#include <algorithm>

namespace HeeM
{
long long power(long long n, long long r)
{
	if (r <= 0)
	{
		return 1;
	}
	return power(n, r - 1) * n;
}
void Primes::Init(int limit)
{
	primeList.clear();
	long long rLimit = power((long long)10, limit);
	mapLimit = rLimit;
	primeField.resize(rLimit);
	long long count = 0;
	for (long long x = 2; x < rLimit; x++)
	{
		if (primeField[x])
			continue;
		else
		{
			//printf("found prime : %lld\n", x);
			primeList.push_back(x);
			for (long long i = x * x; i < rLimit; i += x)
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
	if (n < mapLimit)
		return primeField[n] == false;
	else if (mapLimit * mapLimit < n)
	{
		printf("계산범위를 초과하였습니다. limit:%lld, n:%lld\n", mapLimit * mapLimit, n);
		return false;
	}

	for (std::vector<long long>::iterator iter = primeList.begin(); iter != primeList.end() && sqrt(*iter) >= *iter; ++iter)
	{
		if (n % *iter == 0)
		{
			return true;
		}
	}
	return false;
}

long long Primes::operator[](int index)
{
	if (primeList.size() <= index)
	{
		return false;
	}
	return primeList[index];
}
bool Primes::IsCoprime(long long a, long long b)
{
	auto min = std::min(a, b);
	auto max = std::max(a, b);
	auto primeIter = primeList.begin();
	while (min > 1 && primeIter != primeList.end())
	{
		bool isDivider = false;
		while (min > 1 && min % (*primeIter) == 0)
		{
			isDivider = true;
			min /= *primeIter;
		}
		if (isDivider && max % *primeIter == 0)
			return false;
		++primeIter;
	}
	return true;
}
long long Primes::Rad(long long n)
{
	long long cp = n;
	long long ret = 1;
	auto primeIter = primeList.begin();
	while (n > 1 && primeIter != primeList.end())
	{
		bool isDivider = false;
		while (n > 1 && n % (*primeIter) == 0)
		{
			isDivider = true;
			n /= *primeIter;
		}
		if (isDivider)
			ret *= *primeIter;
		++primeIter;
	}
	if (ret == 1)
		return cp;
	return ret;
}

Primes::PrimeFactors::PrimeFactors(Primes* primes, long long n) : rad(1)
{
	auto& rPrimes = primes->GetPrimes();
	auto primeIter = rPrimes.begin();
	while (n > 0 && primeIter != rPrimes.end())
	{
		auto prime = *primeIter++;
		size_t presence = 0;
		while (n % prime == 0)
		{
			++presence;
			n /= prime;
		}
		if (presence > 0)
		{
			factors.insert(prime);
			presences.push_back(presence);
			rad *= prime;
		}
	}
}

bool Primes::PrimeFactors::HasCommonDivisor(const PrimeFactors& primeFactors) const
{
	for (auto f : primeFactors.factors)
		if (factors.find(f) != factors.end())
			return true;
	return false;
}

long long Primes::PrimeFactors::Rad()
{
	return rad;
}

}
