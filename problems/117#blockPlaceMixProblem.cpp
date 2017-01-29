#include <stdio.h>
#include <map>
#include <vector>

std::vector<long long> CheckCounts;

long long GetCheckSetCount(int curPos, int limit)
{
	if( curPos > limit )
	{
		return 0;
	}
	if( curPos >= limit - 1 )
		return 1;
	
	if( CheckCounts[curPos] > 0)
	{
		return CheckCounts[curPos];
	}

	long long ret = 0;
	for(int i = 1; i < 5; ++i)
	{
		ret += GetCheckSetCount(curPos + i, limit);
	}

	CheckCounts[curPos] = ret;
	//printf("(%s,%d) -> %d\n", curBlockIsBlack ? "Black" : "Red", curPos, ret);
	return ret;
}

void InitializeCheckCounts(int n)
{
	CheckCounts.clear();
	CheckCounts.resize(n);
}

int main()
{
	long long sum = 0;
	int blockCount = 50;
	InitializeCheckCounts(blockCount);
	long long testCount = GetCheckSetCount(0, blockCount);
	printf("answer : %lld\n", testCount);
}
