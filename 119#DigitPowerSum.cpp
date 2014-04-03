#include "library/bigint/bigint.h"
#include <map>
#include <vector>

std::map<BigInt, std::vector<int> > g_checkNums;

int NumSum(BigInt n)
{
	int sum = 0;
	const std::vector<char>& internal = n.getInternal();
	for(auto i = internal.cbegin(); i != internal.cend(); ++i)
	{
		sum += (int)*i;
	}
	return sum;
}

int main()
{
	int count = 0;
	int base = 2;
	while(count < 30)
	{
		BigInt t = base;
		int numsum = NumSum(t);
		std::vector<int>& checkVec = g_checkNums[t];
		for(auto i = checkVec.begin(); i != checkVec.end(); ++i)
		{
			if( *i == numsum )
			{
				printf("찾았다:%d\n", base);
			}
			g_checkNums[t * (*i)].push_back(*i);
		}
		if( t.length() > base )
		{
			++base;
			continue;
		}
		g_checkNums[t*t].push_back(base++);
	}
}
