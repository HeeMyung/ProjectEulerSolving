#include <stdio.h>
#include "prime.h"
#include "iterator.h"

HeeM::Primes g_primes;

std::map<int, HeeM::Primes::PrimeFactors> primeFactorCache;
HeeM::Primes::PrimeFactors& GetPrimeFactors(int n)
{
	auto found = primeFactorCache.find(n);
	if (found != primeFactorCache.end())
		return found->second;

	auto iter = primeFactorCache.insert({ n, HeeM::Primes::PrimeFactors(&g_primes, n) });
	return iter.first->second;
}

struct ABC
{
	ABC(int _a, int _b) : a(_a), b(_b), c(a+b)
	{}

	static std::vector<ABC> Next(const ABC& abc)
	{
		std::vector<ABC> ret;
		for(int i = abc.a+1; i < abc.b; ++i)
			ret.push_back(ABC(i, abc.b));

		ret.push_back(ABC(1, abc.b+1));
// 		for (auto& nabc : ret)
// 			printf("\t(%d,%d,%d)=>(%d,%d,%d)\n", abc.a, abc.b, abc.c, nabc.a, nabc.b, nabc.c);
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
		if( a >= b )
			return false;
		else if( a + b != c )
			return false;

		auto& aFactors = GetPrimeFactors(a);
		auto& bFactors = GetPrimeFactors(b);
		auto& cFactors = GetPrimeFactors(c);

		if( (aFactors.HasCommonDivisor(bFactors) || bFactors.HasCommonDivisor(cFactors) || aFactors.HasCommonDivisor(cFactors)) )
			return false;

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
	ABC start(1, 2);
	PriorityIterater<ABC, &ABC::Next> iter(start);

	long long cSum = 0;
	int count = 0;
	while(true)
	{
		ABC n(0, 0);
		if( !iter.GetNext(n) )
			break;
		//printf("a: %d, b: %d\n", n.a, n.b);
		if( n.c >= 3000 )
			break;
		if( n.Hit() )
		{
			printf("Hit (%lld,%lld,%lld)\n", n.a, n.b, n.c);
			cSum += n.c;
			++count;
		}
	}
	printf("count: %d, Answer : %lld\n", count, cSum);
}
