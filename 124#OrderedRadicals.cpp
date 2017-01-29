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

std::map<int, int> answerMap;

struct STATE
{
	CheckSet baseSet;
	int step;

	STATE(CheckSet b, int s) : baseSet(b), step(s) {}

	long long GetWeight() const
	{
		long long ret = 1;
		for(auto iter = baseSet.cbegin(); iter != baseSet.cend(); ++iter )
		{
			int index = *iter;
			ret *= (long long)(g_prime[index]);
		}
		ret *= (long long)g_prime[step];
		//HeeM::print_set(baseSet);
		//printf(" Weight:%d	", ret);
		return ret;
	}
	void Print()
	{
		printf("{ ");
		for(auto s : baseSet)
		{
			printf("%d ", s);
		}
		printf("%d ", step);
		printf("}");
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
	long long prod;
	SUBSTATE(){}
	SUBSTATE(size_t i, long long p) : index(i), prod(p) {}
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
	if( initial.prod > SORT_RANGE )
		return 0;
	queue.push(initial);

	int count = 0;
	long long lastNumber = 0;
	while(count < limit && !queue.empty())
	{
		SUBSTATE s = queue.top();
		queue.pop();
		if( s.prod > SORT_RANGE )
			break;
		//getchar();
		++count;
		++total;
		printf("curValue:%lld total count:%d\n", s.prod, total);
		answerMap[s.prod] = total+1;
		lastNumber = s.prod;
		for(int i = s.index; i < slot.size(); ++i)
		{
			queue.push(SUBSTATE(i, s.prod * slot[i]));
		}
	}
	if( count == limit )
	{
		printf("LastNumber:%lld\n", lastNumber);
	}
	return count;
}

int main()
{
	g_prime.Init(7);
	std::priority_queue<STATE, std::vector<STATE>, CompareSTATE> workSet;
	CheckSet ini;
	ini.clear();

	int count = TARGET - 1;

	workSet.push(STATE(ini, 0));
	while(!workSet.empty() && count > 0)
	{
		STATE s = workSet.top();
		//printf("now : ");
		s.Print();
		printf("\n");
		//printf(" Weight:%lld ", s.GetWeight());
		workSet.pop();
		//printf("push : ");
		STATE a1(s.baseSet, s.step + 1);
		//a1.Print();
		//printf(" Weight:%lld ", a1.GetWeight());
		workSet.push(a1);
		s.baseSet.insert(s.step);
		//////////////////////////////////////	
		int ccount = Try(s.baseSet, count);	
		count -= ccount;
		int weight = s.GetWeight();
		//printf(" weight:%d setcount:%d\n", weight, ccount);
		if( ccount == 0 )
			break;
		//////////////////////////////////////	
		STATE a2(s.baseSet, s.step + 1);
		//a2.Print();
		//printf(" Weight:%lld\n", a2.GetWeight());
		workSet.push(a2);
	}
	for(int i = 2; i <= 100000; ++i)
	{
		if( answerMap[i] == 0 )
		{
			printf("It would be someting problem here : %d\n", i);
			break;
		}
	}
}
