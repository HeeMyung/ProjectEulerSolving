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
	primeField[1] = true;	// 1은 소수가 아니야
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

long long Primes::GetCommonDenominator(std::vector<long long> params)
{
	std::map<long long, size_t> maxFactors;
	auto FillMaxFactors = [&maxFactors](PrimeFactors& pf)
	{
		for (auto factor : pf.GetFactors())
		{
			size_t presence = pf.GetPresence(factor);
			maxFactors[factor] = std::max(presence, maxFactors[factor]);
		}
	};
	for (auto param : params)
	{
		auto& pfs = GetPrimeFactors(param);
		FillMaxFactors(pfs);
	}

	long long mcd = 1;
	for (auto mf : maxFactors)
		mcd *= (long long)std::pow(mf.first, (long long)mf.second);
	return mcd;
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

HeeM::Primes::PrimeFactors& Primes::GetPrimeFactors(long long n)
{
	if (n == 1)
	{
		static HeeM::Primes::PrimeFactors base;
		return base;
	}
	else if (IsPrime(n))
	{
		auto iter = primeFactors.insert(std::make_pair(n, GetPrimeFactors(1) * n));
		return iter.first->second;
	}

	auto found = primeFactors.find(n);
	if (found != primeFactors.end())
	{
		return found->second;
	}

	Primes::PrimeFactors ret;
	auto& primes = GetPrimes();
	auto primeIter = primes.begin();
	for (auto primeIter = primes.begin(); primeIter != primes.end(); ++primeIter)
	{
		auto prime = *primeIter;
		if (n % prime == 0)
		{
			auto& pf = GetPrimeFactors(n / prime);
			auto iter = primeFactors.insert(std::make_pair(n, pf * prime));
			return iter.first->second;
		}
	}
	throw(std::exception());
}

Primes::PrimeFactors::PrimeFactors() : rad(1)
{
	
}

bool Primes::PrimeFactors::HasCommonDivisor(const PrimeFactors& primeFactors) const
{
	for (auto f : primeFactors.factors)
		if (factors.find(f) != factors.end())
			return true;
	return false;
}

const std::set<long long> Primes::PrimeFactors::GetFactors() const
{
	return factors;
}

size_t Primes::PrimeFactors::GetPresence(long long factor)
{
	return presence[factor];
}

long long Primes::PrimeFactors::Rad() const
{
	return rad;
}

HeeM::Primes::PrimeFactors Primes::PrimeFactors::operator*(long long prime) const
{
	PrimeFactors copy;
	copy.factors = factors;
	copy.presence = presence;
	copy.rad = rad;
	if (factors.find(prime) == factors.end())
		copy.rad *= prime;
	copy.factors.insert(prime);
	++copy.presence[prime];
	return copy;
}

}
