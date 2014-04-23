#include <stdio.h>
#include "library/prime/prime.h"
#include "library/common/common.h"
#include <set>
#include <queue>

#define SORT_RANGE 100000
#define TARGET 10000

HeeM::Primes g_prime;
typedef std::set<int> CheckSet;
std::set<CheckSet> g_allSet;
int total = 0;

struct STATE
{
	CheckSet baseSet;
	int step;

	STATE(CheckSet b, int s) : baseSet(b), step(s) {}

	int GetWeight() const
	{
		int ret = 1;
		for(auto iter = baseSet.cbegin(); iter != baseSet.cend(); ++iter )
		{
			int index = *iter;
			ret *= (int)(g_prime[index]);
		}
		ret *= g_prime[step];
		//HeeM::print_set(baseSet);
		//printf(" Weight:%d	", ret);
		return ret;
	}
};

struct CompareSTATE
{
	bool operator()(const STATE& a, const STATE& b) const
	{
		bool ret = a.GetWeight() > b.GetWeight();
		//putchar('\n');
		return ret;
	}
};

struct SUBSTATE
{
	size_t index;
	int prod;
	SUBSTATE(){}
	SUBSTATE(size_t i, int p) : index(i), prod(p) {}
	bool operator <(const SUBSTATE& s) const
	{
		return prod > s.prod;
	}
};

int Try(CheckSet s, int limit)
{
	if( s.size() == 0 )
		return 0;
	std::vector<int> slot;
	for(auto i : s)
	{
		slot.push_back((int)g_prime[i]);
	}
	std::priority_queue<SUBSTATE> queue;
	SUBSTATE initial;
	initial.index = 0;
	initial.prod = 1;
	for(auto i : slot)
		initial.prod *= i;
	queue.push(initial);

	int count = 0;
	int lastNumber = 0;
	while(count < limit && !queue.empty())
	{
		SUBSTATE s = queue.top();
		queue.pop();
		if( s.prod > SORT_RANGE )
			break;
		//getchar();
		++count;
		++total;
		printf("curValue:%d total count:%d\n", s.prod, total);
		lastNumber = s.prod;
		queue.push(SUBSTATE(s.index, s.prod * slot[s.index]));
		if( s.index < slot.size() - 1 )
			queue.push(SUBSTATE(s.index + 1, s.prod * slot[s.index + 1]));
	}
	if( count == limit )
	{
		printf("LastNumber:%d\n", lastNumber);
	}
	return count;
}

int main()
{
	g_prime.Init(6);
	std::priority_queue<STATE, std::vector<STATE>, CompareSTATE> workSet;
	CheckSet ini;
	ini.clear();

	int count = TARGET - 1;

	workSet.push(STATE(ini, 0));
	while(!workSet.empty() && count > 0)
	{
		STATE s = workSet.top();
		workSet.pop();
		workSet.push(STATE(s.baseSet, s.step + 1));
		int weight = s.GetWeight();
		s.baseSet.insert(s.step);
		////////////////////////////////////
		int ccount = Try(s.baseSet, count);	
		count -= ccount;
		////////////////////////////////////
		//HeeM::print_set(s.baseSet);
		//printf(" weight:%d setcount:%d\n", weight, ccount);
		workSet.push(STATE(s.baseSet, s.step + 1));
	}
}
