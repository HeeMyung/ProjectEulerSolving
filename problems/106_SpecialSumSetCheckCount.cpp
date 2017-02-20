#include <map>
#include <vector>
#include "common.h"


struct state
{
	int minus, plus, nowPoint;
	bool check;
	state()
	{
		minus = 0; plus = 0, nowPoint = 0;
		check = false;
	}
	state(int m, int p, int n, bool c)
	{
		minus = m;
		plus = p;
		nowPoint = n;
		check = c;
	}
};

int GetCheckCount(int minus, int plus, int nowPoint, bool checked, std::vector<state> dum);

int main()
{
	int targetN = 12;
	int checkCount = 0;
	for(int k = 2; 2*k <= targetN; ++k)
	{
		int prod = HeeM::combination(targetN, 2 * k);
		int check = GetCheckCount(k-1, k, -1, false, std::vector<state>());
		printf("%d*%d:%d\n", prod, check, prod*check);
		checkCount += check * prod;
	}
	printf("%d\n", checkCount);
}

struct comp
{
	bool operator()(const state& a, const state& b) const
	{
		if( a.plus < b.plus )
			return true;
		else if (a.plus > b.plus)
			return false;
		
		if( a.minus < b.minus )
			return true;
		else if( a.minus > b.minus )
			return false;
		
		if( a.nowPoint < b.nowPoint )
			return true;
		else if( a.nowPoint > b.nowPoint )
			return false;

		if( a.check && !b.check )
			return true;
		else if( !a.check && b.check )
			return false;

		//printf("Perfact Same(%d,%d), (%d,%d), (%d,%d), (%s,%s)\n", a.plus, b.plus, a.minus, b.minus, a.nowPoint, b.nowPoint, a.check ? "true" : "false", b.check ? "true" : "false");
		return false;
	}
};

std::map<state, int, comp> g_stateMap;

int GetCheckCount(int minus, int plus, int nowPoint, bool checked, std::vector<state> dum)
{
	if( nowPoint > 0 )
		checked = true;
	state s(minus, plus, nowPoint, checked);
	if( g_stateMap.find(s) != g_stateMap.end() )
	{
		//printf("hit! %d, %d, %d, %s => %d\n", minus, plus, nowPoint, checked ? "true" : "false", g_stateMap[s]);
		return g_stateMap[s];
	}
	if( minus == 0 && plus == 0 && nowPoint == 0 && checked )
	{
		/*
		printf("( ");
		for(int i = 0; i+1 < dum.size(); ++i)
		{
			printf("%d -> ", dum[i].nowPoint);
		}
		if( dum.size() > 0 )
			printf("%d ", dum[dum.size()-1].nowPoint);
		printf(")\n");
		*/
		return 1;
	}
	else if( minus == 0 && plus == 0 && nowPoint == 0 && !checked)
		return 0;
	dum.push_back(s);
	int ret = 0;
	if( minus > 0 )
		ret += GetCheckCount( minus - 1, plus, nowPoint - 1, checked, dum );
	if( plus > 0 )
		ret += GetCheckCount( minus, plus - 1, nowPoint + 1, checked, dum );
	g_stateMap[s] = ret;
	//printf("check: (%d,%d) (%d,%d) (%d,%d) (%s,%s) => %d\n", minus, s.minus, plus, s.plus, nowPoint, s.nowPoint, checked ? "true" : "false", s.check ? "true" : "false", ret);
	return ret;
}
