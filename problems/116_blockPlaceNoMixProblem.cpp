#include <stdio.h>
#include <map>
#include <vector>

std::vector<long long> CheckCounts;

long long GetCheckSetCount(int curPos, int proceedSize, int limit)
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
	ret = GetCheckSetCount(curPos + 1, proceedSize, limit) + GetCheckSetCount(curPos + proceedSize, proceedSize, limit);

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
	for(int i = 2; i <= 4; ++i)
	{
		InitializeCheckCounts(blockCount);
		long long testCount = GetCheckSetCount(0, i, blockCount) - 1;
		printf("F(%d, %d) : %lld\n", i, blockCount, testCount);
		sum += testCount;
	}
	printf("answer : %lld\n", sum);
}
