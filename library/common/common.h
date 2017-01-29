#include <stdio.h>
#include <set>

namespace HeeM
{
	template<class T> T factorial(const T& n)
	{
		if( n <= T((int)1) )
		{
			return T((int)1);
		}
		else 
		{
			//T ret = factorial(n - T((int)1)) * n;
			//T cp = n;
			//printf("factorial(%s) : %s\n", (const char*)cp, (const char*)ret);
			//return ret;
			return factorial(n - T((int)1)) * n;
		}	
	}
	template<class T> T combination(const T& n, const T& r)
	{
		return (factorial(n) / factorial(r)) / factorial(n - r);
	}
	template<class T> T power(const T& n, const T& r)
	{
		if( r <= T((int)0) )
		{
			return 1;
		}
		return power(n, r - T((int)1)) * n;
	}
	void print_set(const std::set<int> t)
	{
		printf("{ ");
		for(auto iter = t.cbegin(); iter != t.cend(); ++iter)
		{
			if( iter != t.begin() )
			{
				printf(", ");
			}
			printf("%d", *iter);
		}
		printf(" }");
	}
}
