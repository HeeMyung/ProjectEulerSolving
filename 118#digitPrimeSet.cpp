#include <stdio.h>
#include "library/prime/prime.h"
#include "library/permutation/permutation.h"
#include "library/permutation/combination.h"
#include <set>
#include <vector>
#include <queue>

std::map< std::set<int>, long long > answerSet;
HeeM::Primes primeObject;
std::set< std::set< std::set<int > > > answeredSet;


long long registerAndReturn(std::set<int> inset, long long answer)
{
	answerSet[inset] = answer;
	
	printf("( ");
	for(std::set<int>::iterator setIter = inset.begin(); setIter != inset.end(); ++setIter)
	{
		printf("%d ", *setIter);
	}
	printf(") : %lld\n", answer);
	return answer;
}

std::set<int> SetSubt(std::set<int> a, std::set<int> b)
{
	for(std::set<int>::iterator subIter = b.begin(); subIter != b.end(); ++subIter)
	{
		a.erase(*subIter);
	}
	return a;
}

void printVec(std::vector<int> vec)
{
	/*
	printf("( ");
	for(std::vector<int>::iterator iter = vec.begin(); iter != vec.end(); ++iter)
	{
		printf("%d ", *iter);
	}
	printf(")\n");
	*/
}

long long GetCount(std::set< std::set<int> > prevSets, std::set<int> inset)
{
	if( inset.size() <= 0 )
		return 0;
	
	std::map< std::set<int>, long long >::iterator findIter = answerSet.find(inset);
	if( findIter != answerSet.end() )
		return findIter->second;
	if( inset.size() == 1 )
	{
		return registerAndReturn(inset, primeObject.IsPrime(*(inset.begin())) ? 1 : 0);
	}

	long long sum = 0;
	HeeM::Combination<int> c;
	for(std::set<int>::iterator iter = inset.begin(); iter != inset.end(); ++iter)
	{
		c.AddElement(*iter);
	}
	for(int i = 1; i <= inset.size(); ++i)
	{
		c.Start(i);
		do
		{
			std::vector<int> selection;
			c.GetSelection(selection);
			printVec(selection);
			HeeM::Permutation<int> p;
			std::set<int> genSubSet;
			for(std::vector<int>::iterator iter = selection.begin(); iter != selection.end(); ++iter)
			{
				p.AddElement(*iter);
				genSubSet.insert(*iter);
			}
			p.Start();
			do
			{
				std::vector<int> curstate;
				int num = 0;
				p.GetCurrentSelection(curstate);
				for(std::vector<int>::iterator iter = curstate.begin(); iter != curstate.end(); ++iter)
				{`
					num = (num*10) + *iter;
				}
				if( primeObject.IsPrime(num) )
				{
					sum += GetCount(SetSubt(inset, genSubSet));
				}
			}while(p.ProcessNextState());
			
		}while(c.ProcessNextSelection());
	}

	return registerAndReturn(inset, sum);
}

int main()
{
	primeObject.Init(7);

	std::set<int> initSet;
	for(int i = 1; i <= 9; ++i)
	{
		initSet.insert(i);
	}

	printf("Answer : %lld\n", GetCount(initSet));
	return 0;
}
