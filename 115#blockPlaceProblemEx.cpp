#include <stdio.h>
#include <map>
#include <vector>

#define MAXSLOT 30

std::vector<long long> blackCheckCounts;
std::vector<long long> redCheckCounts;

long long GetCheckSetCount(bool curBlockIsBlack, int curPos, int proceedSize, int limit)
{
	if( curPos > limit )
	{
		return 0;
	}
	else if( !curBlockIsBlack && curPos == limit )
		return 1;
	if( curPos == limit - 1 )
		return curBlockIsBlack ? 1 : 2;
	
	if( curBlockIsBlack && blackCheckCounts[curPos] > 0)
	{
		return blackCheckCounts[curPos];
	}
	else if( !curBlockIsBlack && redCheckCounts[curPos] > 0 )
	{
		return redCheckCounts[curPos];
	}

	long long ret = 0;

	if( curBlockIsBlack )
	{
		ret = GetCheckSetCount(true, curPos + 1, proceedSize, limit) + GetCheckSetCount(false, curPos + proceedSize, proceedSize, limit);
		blackCheckCounts[curPos] = ret;
	}
	else
	{
		ret = GetCheckSetCount(true, curPos + 1, proceedSize, limit) + GetCheckSetCount(false, curPos + 1, proceedSize, limit);
		redCheckCounts[curPos] = ret;
	}
	//printf("(%s,%d) -> %d\n", curBlockIsBlack ? "Black" : "Red", curPos, ret);
	return ret;
}

void InitializeCheckCounts(int n)
{
	blackCheckCounts.clear();
	blackCheckCounts.resize(n);
	redCheckCounts.clear();
	redCheckCounts.resize(n);
}

int main()
{
	int N = 51;
	while(true)
	{
		InitializeCheckCounts(N);
		long long testCount = GetCheckSetCount(true, 0, 50, N);
		printf("F(%d, %d) : %lld\n", 50, N, testCount);
		if( testCount > 1000000 )
			break;
		++N;
	}
	printf("N : %d\n", N);
}
