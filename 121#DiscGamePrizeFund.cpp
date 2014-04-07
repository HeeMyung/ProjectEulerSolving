#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include "library/common/common.h"

std::map<std::pair<int,int>, long long> g_winCount;

int maxturn = 15;

long long Go(int turn, int curBluePick)
{
	if( turn > maxturn )
	{
		return curBluePick > maxturn / 2 ? 1 : 0;
	}
	std::pair<int, int> t = std::make_pair(turn, curBluePick);
	int winCount = g_winCount[t];
	if( winCount != 0 )
	{
		return winCount;
	}
	g_winCount[t] = Go(turn + 1, curBluePick + 1) + (turn) * Go(turn + 1, curBluePick);
	return g_winCount[t];
}

int main()
{
	long long total = HeeM::factorial<long long>(maxturn+1);
	long long count = Go(1, 0);
	printf("%lld/%lld, Answer:%lld\n", count, total, total/count);
}
