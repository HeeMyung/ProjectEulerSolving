#include "library/common/common.h"
#include "library/bigint/bigint.h"

#define MIN(a,b) ( (a) > (b) ? (b) : (a) )
#define ABS(a) ( (a) > 0 ? (a) : -(a) )
#define NORMAL(a)	((a) / ABS(a))

bool isBouncyNumber(int n)
{
	int direction = 0;
	while(n >= 10)
	{
		int next = ((n%10)-((n/10)%10));
		if( next * direction < 0 )
			return true;
		else if( next != 0 && direction == 0 )
		{
			direction = NORMAL(next);
		}
		n /= 10;
	}
	return false;
}

bool isIncreaseNumber(int n, int& out_level)
{
	int direction = 0;
	int level = 0;
	out_level = 0;
	while(n >= 10)
	{
		int next = ((n%10)-((n/10)%10));
		if( next * direction < 0 )
			return false;
		else if( next != 0 && direction == 0 )
		{
			direction = NORMAL(next);
			level++;
		}
		else if( next != 0 )
		{
			level++;
		}
		n /= 10;
	}
	out_level = level;
	return direction <= 0;
}

void Test(int jari)
{
	int max = HeeM::power(10, jari);
	int firstlevelCheck = HeeM::power(10, jari-1);
	std::vector<int> levelCount;
	levelCount.resize(jari);
	int total = 0;
	for(int i = 1; i < max; ++i)
	{
		int level;
		if( isIncreaseNumber(i, level) )
		{
			if( i < firstlevelCheck )
				level++;
			levelCount[level]++;
		}
		if( !isBouncyNumber(i) )
		{
			total++;
		}
	}
	for(int i = 0; i < jari; ++i)
	{
		printf("level:%d -> %d\n", i, levelCount[i]);
	}
	printf("Total : %d\n", total);
}

BigInt CountNonBouncyNumber(int jari)
{
	BigInt answer(0);
	
	for(int rjari = 1; rjari <= jari; ++rjari)
	{
		printf("check Jari : %d\n", rjari);
		for(int cs = 0; cs < 2; ++cs)
		{
			for(int level = cs; level <= 9; level++)
			{
				if( 10-cs < level || rjari-1 < level )
					continue;
				BigInt candidateCount = HeeM::combination(BigInt(10-cs), BigInt(level+1));
				BigInt levelTypeCount = HeeM::combination(BigInt(rjari-1), BigInt(level));
				printf("level:%d, candidateCount:%s, levelTypeCount:%s\n", level, (const char*)candidateCount, (const char*)levelTypeCount);
				answer = answer + (candidateCount * levelTypeCount);
			}
		}
		answer = answer - BigInt(1);
		printf("current Sum : %s\n", (const char*)answer);
		//Test(rjari);
	}
	//Test(jari);
	return answer;
}

int main()
{
	BigInt a = CountNonBouncyNumber(100);
	printf("NonBouncyNumber Count : %s\n", (const char*)a);
}
