#include <stdio.h>
#include "prime.h"
#include "iterator.h"
#include <functional>

HeeM::Primes g_primes;

std::set<std::pair<int, int> > g_noSet;
int main()
{
	g_primes.Init(6);

	long long cSum = 0;
	int count = 0;

	const int limit = 120000;

	for (int c = 3; c < limit; ++c)
	{
		auto& cFactors = g_primes.GetPrimeFactors(c);
		bool bitholder[limit] = { false, };
		for (auto prime : cFactors.factors)
		{
			for (int i = 1; i * prime < c; ++i)
			{
				bitholder[i * prime] = true;
			}
		}
		auto radLimit = c / cFactors.Rad();
		for (int a = 1; a < c / 2; ++a)
		{
			int b = c - a;
			if (bitholder[a] || bitholder[b])
				continue;
			auto& aFactors = g_primes.GetPrimeFactors(a);
			auto& bFactors = g_primes.GetPrimeFactors(b);
			if (aFactors.Rad() * bFactors.Rad() > radLimit)
				continue;
			if (aFactors.HasCommonDivisor(bFactors))
				continue;
			++count;
			cSum += c;
			printf("Hit (%d, %d, %d)\n", a, b, c);
		}
	}
	printf("count: %d, Answer : %lld\n", count, cSum);
}
