#include <stdio.h>
#include "prime.h"
#include "iterator.h"
#include <functional>

HeeM::Primes g_primes;

struct ABC
{
	ABC(int _a, int _b) : a(_a), b(_b), c(a + b)
	{
	}

	bool operator<(const ABC& rhs) const
	{
		return c > rhs.c ? true :
			c < rhs.c ? false :
			a < rhs.a ? true :
			a > rhs.a ? false :
			b < rhs.b;
	}

	bool Hit()
	{
		if( a + b != c )
			return false;

		HeeM::Primes::PrimeFactors& aFactors = g_primes.GetPrimeFactors(a);
		HeeM::Primes::PrimeFactors& bFactors = g_primes.GetPrimeFactors(b);
		HeeM::Primes::PrimeFactors& cFactors = g_primes.GetPrimeFactors(c);
		
		if (bFactors.HasCommonDivisor(cFactors) || aFactors.HasCommonDivisor(cFactors))
			return false;

		long long rad = aFactors.Rad() * bFactors.Rad() * cFactors.Rad();
		if (rad >= c)
			return false;
		else
			return true;
	}

	long long a, b, c;
};
std::set<std::pair<int, int> > g_noSet;

int main()
{
	g_primes.Init(6);

	long long cSum = 0;
	int count = 0;

	const int limit = 120000;

	for (int b = 2; b < limit; ++b)
	{
		auto bFactors = g_primes.GetPrimeFactors(b);
		bool bitholder[limit] = { false, };
		for (auto prime : bFactors.factors)
		{
			for (int i = 1; i * prime < b; ++i)
			{
				bitholder[i * prime] = true;
			}
		}
		for (int a = 1; a < b && a + b < limit; ++a)
		{
			if (bitholder[a])
				continue;
			ABC t((long long)a, (long long)b);
			if (t.Hit())
			{
				++count;
				cSum += t.c;
				printf("Hit!: (%lld, %lld, %lld)\n", t.a, t.b, t.c);
			}
		}
	}
	printf("count: %d, Answer : %lld\n", count, cSum);
}
