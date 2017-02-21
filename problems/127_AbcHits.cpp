#include <stdio.h>
#include "prime.h"
#include "iterator.h"
#include <functional>

HeeM::Primes g_primes;

struct ABC
{
	ABC(int _a, int _b, int _c) : a(_a), b(_b), c(_c)
	{
	}

	static std::vector<ABC> Next(const ABC& abc)
	{
		HeeM::Primes::PrimeFactors& aFactors = g_primes.GetPrimeFactors(abc.a);
		HeeM::Primes::PrimeFactors& bFactors = g_primes.GetPrimeFactors(abc.b);
		HeeM::Primes::PrimeFactors& cFactors = g_primes.GetPrimeFactors(abc.c);

		auto& primes = g_primes.GetPrimes();

		std::vector<ABC> ret;
		auto Adder = [&](long long start, long long limit, long long primeBase, const std::set<long long>& exceptSetA, const std::set<long long>& exceptSetB, std::function<ABC(long long)> generator)
		{
			for (auto primeIter = primes.begin(); primeIter != primes.end(); ++primeIter)
			{
				auto prime = *primeIter;
				if (prime < primeBase)
					continue;
				if (exceptSetA.find(prime) != exceptSetA.end())
					continue;
				if (exceptSetB.find(prime) != exceptSetB.end())
					continue;

				auto nextValue = start * prime;
				if (nextValue >= limit)
					break;

				ret.emplace_back(generator(nextValue));
			}
		};
		Adder(abc.a, abc.b, abc.a == 1 ? 1 : *(aFactors.factors.rbegin()), bFactors.GetFactors(), cFactors.GetFactors(), [&](long long newA) 
		{
			return ABC(newA, abc.b, abc.c);
		});
		Adder(abc.b, abc.c, abc.b == 1 ? 1 : *(bFactors.factors.rbegin()), aFactors.GetFactors(), cFactors.GetFactors(), [&](long long newB)
		{
			return ABC(abc.a, newB, abc.c);
		});
		Adder(abc.c, 120000, abc.c == 1 ? 1 : *(cFactors.factors.rbegin()), aFactors.GetFactors(), bFactors.GetFactors(), [&](long long newC)
		{
			return ABC(abc.a, abc.b, newC);
		});
		return ret;
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

		long long rad = aFactors.Rad() * bFactors.Rad() * cFactors.Rad();
		if (rad >= c)
			return false;
		else
			return true;
	}

	long long a, b, c;
};

int main()
{
	g_primes.Init(5);
	ABC start(1, 1, 1);
	Iterator<ABC, &ABC::Next> iter(start);

	long long cSum = 0;
	int count = 0;
	while(true)
	{
		ABC n(1, 1, 1);
		if( !iter.GetNext(n) )
			break;
		//printf("a: %d, b: %d\n", n.a, n.b);
		if( n.Hit() )
		{
			printf("Hit (%lld,%lld,%lld)\n", n.a, n.b, n.c);
			cSum += n.c;
			++count;
		}
	}
	printf("count: %d, Answer : %lld\n", count, cSum);
}
