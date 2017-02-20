#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <queue>


std::vector<long long> primes;

void PrimeInit()
{
	bool* notprimes = new bool[100000];

	long long count = 0;
	for(long long x = 2; x < 100000; x++)
	{
		if( notprimes[x] )
			continue;
		else
		{
//			printf("found prime : %lld\n", x);
			primes.push_back(x);
			for(long long i = x * x; i < 100000; i+=x)
			{
				notprimes[i] = true;
			}
		}
	}
}

bool isPrime(long long n)
{
	if( n == 0 )
		return false;
	for(std::vector<long long>::iterator iter = primes.begin(); (*iter)*(*iter) <= n && iter != primes.end(); ++iter)
	{
		if( n % *iter == 0 )
			return false;
	}
	return true;
}

struct PAIR
{
	int index;
	int n;
	PAIR() : index(0), n(0) {}
	PAIR(int _index, int _n) : index(_index), n(_n) {}
};

struct NUMBER
{
	std::vector<PAIR> indexque;
	int size;
	int baseCount;
	int base;

	NUMBER() : size(0), baseCount(0), base(0)
	{
	}
	NUMBER(int _size, int _baseCount, int _base) : size(_size), baseCount(_baseCount), base(_base)
	{
		indexque.clear();
	}

	NUMBER operator+(const PAIR& p) const
	{
		if( indexque.size() >= size - baseCount )
		{
			printf("너무 많이 들어와서 무시함 queSize:%d, size:%d, baseCount%d\n", (int)indexque.size(), size, baseCount);
			return NUMBER();
		}
		if( p.n < 0 || p.n > 9 || p.index < 0 || p.index > baseCount )
		{
			printf("범위 벗어남 index:%d, n:%d\n", p.index, p.n);
			return NUMBER();
		}
		if( indexque.size() == 0 && p.n == 0 && p.index == 0 )
		{
			printf("첫자리에는 0들어올 수 없다.\n");
			return NUMBER();
		}
		if( indexque.size() > 0 )
		{
			const PAIR& lastp = (*indexque.rbegin());
			if( lastp.index > p.index )
			{
				printf("인덱스 값이 이전에 입력된 페어보다 낮습니다. last:%d, current:%d\n", lastp.index, p.index);
				return NUMBER();
			}
		}
		NUMBER ret = *this;
		ret.indexque.push_back(p);
		return ret;
	}

	long long toNumber()
	{
		if( indexque.size() + baseCount != size )
		{
			printf("아직 값이 덜 찼음\n");
			return 0;
		}
		long long retVal = 0;
		std::vector<PAIR>::iterator iter = indexque.begin();
		int i = 0;
		while(i <= baseCount)
		{
			if( iter != indexque.end() && i == (*iter).index )
			{
				retVal *= 10;
				retVal += (*iter++).n;
			}
			else if( i < baseCount )
			{
				retVal *= 10;
				retVal += base;
				++i;
			}
			else
			{
				break;
			}
		}
		return retVal;
	}
};

int N(int n, int d)
{
	return 0;
}

bool MSub(NUMBER n, int base, int curIndex, int remainTry)
{
	if( remainTry <= 0 )
	{
		return isPrime(n.toNumber());
	}
	for(int i = curIndex; i <= n.baseCount; ++i)
	{
		for(int d = 0; d <= 9 ; ++d)
		{
			if( d == base || (i == 0 && d == 0) || (base == 0 && n.indexque.size() == 0 && i > 0) )
				continue;
			if( MSub(n + PAIR(i, d), base, i, remainTry-1) )
				return true;
		}
	}
	return false;
}

int M(int n, int d)
{
	for(int baseCount = n; baseCount > 0; --baseCount)
	{
		NUMBER num(n, baseCount, d);
		if( MSub(num, d, 0, n - baseCount) )
			return baseCount;
	}
	return 0;
}

long long SSub(NUMBER n, int base, int curIndex, int remainTry)
{
	if( remainTry <= 0 )
	{
		long long calc = n.toNumber();
/*		if( isPrime(calc) )
		{
			printf("찾았다 %lld\n", calc);
		}*/
		return isPrime(calc) ? calc : 0;
	}
	long long sum = 0;
	for(int i = curIndex; i <= n.baseCount; ++i)
	{
		for(int d = 0; d <= 9 ; ++d)
		{
			if( d == base || (i == 0 && d == 0) || (base == 0 && n.indexque.size() == 0 && i > 0))
				continue;
			sum += SSub(n + PAIR(i, d), base, i, remainTry-1);
		}
	}
	return sum;
}

long long S(int n, int d)
{
	int baseCount = M(n, d);
	//printf("M(%d, %d) : %d\n", n, d, baseCount);
	NUMBER num(n, baseCount, d);
	return SSub(num, d, 0, n - baseCount);
}

int main()
{
	PrimeInit();
	long long sum = 0;
	for(int i = 0;i <= 9; ++i)
	{
		//printf("S(4, %d) : %lld\n", i, S(4, i));
		sum += S(10, i);
	}
	printf("Answer : %lld\n", sum);
}
