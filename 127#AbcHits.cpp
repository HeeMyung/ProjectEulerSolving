#include <stdio.h>
#include "library/prime/prime.h"
#include "library/iterater/iterater.h"

HeeM::Primes g_primes;

struct ABC
{
	ABC(int _a, int _b) : a(_a), b(_b), c(a+b)
	{}

	static std::vector<ABC> Next(const ABC& abc)
	{
		std::vector<ABC> ret;
		for(int i = abc.a+1; i < abc.b; ++i)
		{
			if( g_primes.IsCoprime(i, abc.b) )
			{
				ret.push_back(ABC(i, abc.b));
				return ret;
			}
		}
		ret.push_back(ABC(1, abc.b+1));
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
		long long rad = g_primes.Rad(a*b*c);
		if( rad >= c )
			return false;
		else if( g_primes.IsCoprime(a, b) && g_primes.IsCoprime(b, c) && g_primes.IsCoprime(a, c) )
		{
			printf("a*b*c: %lld, rad : %lld\n", a*b*c, rad);
			return true;
		}
		else
			return false;
	}

	long long a, b, c;
};

int main()
{
	g_primes.Init(8);
	ABC start(1, 2);
	PriorityIterater<ABC, &ABC::Next> iter(start);

	long long cSum = 0;
	while(true)
	{
		ABC n(0, 0);
		if( !iter.GetNext(n) )
			break;
		if( n.c >= 1000 )
			break;
		if( n.Hit() )
		{
			printf("Hit (%lld,%lld,%lld)\n", n.a, n.b, n.c);
			cSum += n.c;
		}
	}
	printf("Answer : %lld\n", cSum);
}
