#include <stdio.h>
#include "library/prime/prime.h"
#include "library/permutation/permutation.h"
#include "library/permutation/combination.h"
#include <set>
#include <vector>
#include <queue>

int totalCount = 0;
std::vector<int> checkVec;
std::set<int> numberSet;
std::vector<int> debugVec;

std::vector<int> Parse(int number)
{
	std::vector<int> ret;
	while(number)
	{
		int n = number%10;
		ret.push_back(n);
		number /= 10;
	}
	return ret;
}

bool OkCheck(std::vector<int>& parsed)
{
	for(auto iter = parsed.begin(); iter != parsed.end(); ++iter)
	{
		if( numberSet.find(*iter) != numberSet.end() )
			return false;
	}
	return true;
}

void PrintCurset()
{
	printf("{ ");
	for(auto iter = debugVec.begin(); iter != debugVec.end(); ++iter)
	{
		if( iter != debugVec.begin() )
		{
			printf(", ");
		}
		printf("%d", *iter);
	}
	printf(" }\n");
}

void Check(unsigned int index)
{
	int number = checkVec[index];

	std::vector<int> parsed = Parse(number);

	if( !OkCheck(parsed) )
		return;

	debugVec.push_back(number);
	for(auto iter = parsed.begin(); iter != parsed.end(); ++iter)
	{
		numberSet.insert(*iter);
	}
//	printf("Current Set:");
//	PrintCurset();

	bool fullset = true;
	for(int i = 1; i <= 9; ++i)
	{
		if( numberSet.find(i) == numberSet.end() )
		{
			fullset = false;
			break;
		}
	}
	if( fullset )
	{
		++totalCount;
		printf("찾았다:");
		PrintCurset();
		for(auto iter = parsed.begin(); iter != parsed.end(); ++iter)
		{
			numberSet.erase(*iter);
		}
		debugVec.pop_back();
		return;
	}

	if( parsed.size() > 9 - numberSet.size() )
		// 더이상의 답은 존재할 수 없다.
	{
		for(auto iter = parsed.begin(); iter != parsed.end(); ++iter)
		{
			numberSet.erase(*iter);
		}
		debugVec.pop_back();
		return;
	}

	while(++index < checkVec.size())
	{
		Check(index);
	}
	for(auto iter = parsed.begin(); iter != parsed.end(); ++iter)
	{
		numberSet.erase(*iter);
	}
	debugVec.pop_back();
}

bool IsElementDigit(long long num)
{
	std::set<int> s;
	while(num > 0)
	{
		int n = num%10;
		if( n == 0 )
			return false;
		if( s.find(n) != s.end() )
			return false;
		s.insert(n);
		num /= 10;
	}
	return true;
}

int main()
{
	HeeM::Primes primeObject;
	primeObject.Init(8);

	for(auto iter = primeObject.GetPrimes().begin(); iter != primeObject.GetPrimes().end(); ++iter)
	{
		if( !IsElementDigit(*iter) )
			continue;
		checkVec.push_back((int)*iter);
	}

	numberSet.clear();
	debugVec.clear();
	printf("Start!\n");
	for(int i = 0; i < checkVec.size(); ++i)
	{
		Check(i);
	}
	printf("Answer : %d\n", totalCount);
	return 0;
}
