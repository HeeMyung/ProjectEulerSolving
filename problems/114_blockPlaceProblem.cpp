#include <stdio.h>
#include <map>
#include <vector>

#define MAXSLOT 30

long long blackCheckCounts[MAXSLOT];
long long redCheckCounts[MAXSLOT];

long long GetCheckSetCount(bool curBlockIsBlack, int curPos)
{
	if( curPos > MAXSLOT )
	{
		return 0;
	}
	else if( !curBlockIsBlack && curPos == MAXSLOT )
		return 1;
	if( curPos == MAXSLOT - 1 )
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
		ret = GetCheckSetCount(true, curPos + 1) + GetCheckSetCount(false, curPos + 3);
		blackCheckCounts[curPos] = ret;
	}
	else
	{
		ret = GetCheckSetCount(true, curPos + 1) + GetCheckSetCount(false, curPos + 1);
		redCheckCounts[curPos] = ret;
	}
	//printf("(%s,%d) -> %d\n", curBlockIsBlack ? "Black" : "Red", curPos, ret);
	return ret;
}

void InitializeCheckCounts()
{
	memset(blackCheckCounts, 0, sizeof(blackCheckCounts));
	memset(redCheckCounts, 0, sizeof(redCheckCounts));
}

int main()
{
	InitializeCheckCounts();
	long long testCount = GetCheckSetCount(true, 0);
	printf("answer : %lld\n", testCount);
}
