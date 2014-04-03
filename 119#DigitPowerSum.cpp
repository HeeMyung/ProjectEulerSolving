#include "library/bigint/bigint.h"
#include <map>
#include <vector>
#include <set>
#include <queue>

typedef long long numtype;
std::map<numtype, std::vector<int> > g_checkNums;
struct cmp_
{
	bool operator()(const numtype& a, const numtype& b) const
	{
		return a > b;
	}
} cmp;
std::priority_queue<numtype, std::vector<numtype>, cmp_> g_checkQueue;
std::set<numtype> g_set;

int NumSum(numtype n)
{
	int sum = 0;
	while(n)
	{
		sum += n % 10;
		n /= 10;
	}
	return sum;
}

int NumLength(numtype n)
{
	int ret = 0;
	while(n)
	{
		n /= 10;
		++ret;
	}
	return ret;
}

void push(numtype n)
{
	if( g_set.find(n) == g_set.end() )
	{
		g_checkQueue.push(n);
		g_set.insert(n);
		//printf("%lld pushed\n", n);
	}
}

int main()
{
	int count = 0;
	g_checkQueue.push(2);
	while(count < 30)
	{
		numtype t = g_checkQueue.top();
		//printf("%lld\n", t);
		//getchar();
		g_checkQueue.pop();
		int numsum = NumSum(t);
		std::vector<int>& checkVec = g_checkNums[t];
		for(auto i = checkVec.begin(); i != checkVec.end(); ++i)
		{
			if( *i == numsum )
			{
				printf("찾았다:%lld\n", t);
				++count;
			}
			numtype target = t * (*i);
			g_checkNums[target].push_back(*i);
			push(target);
		}
		if( t > 1000 )
		{
			continue;
		}
		g_checkNums[t*t].push_back((int)t);
		push(t*t);
		push(t+1);
	}
}
