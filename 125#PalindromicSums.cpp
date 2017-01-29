#include <stdio.h>
#include <vector>
#include <set>

bool IsPalindrome(long long n)
{
	std::vector<int> l;
	while(n)
	{
		l.push_back((int)n%10);
		n/=10;
	}
	auto iter = l.begin();
	auto rIter = l.rbegin();
	while(iter != l.end() && rIter != l.rend())
	{
		if( *iter != *rIter )
			return false;
		++iter;
		++rIter;
	}
	return true;
}
int main()
{
	std::vector<long long> sums;
	sums.resize(10001);
	sums[0] = 0;
	long long answer = 0;
	std::set<long long> answerSet;
	for(int i = 1; i <= 10000; ++i)
	{
		sums[i] = sums[i-1] + i*i;
		for(int j = 0; j <  i - 1; ++j)
		{
			long long check = sums[i] - sums[j];
			if( check > 100000000 )
				continue;
			if( IsPalindrome(check) && answerSet.find(check) == answerSet.end() )
			{
				answer += check;
				answerSet.insert(check);
				printf("찾았다! %lld\n", check);
			}
		}
	}
	printf("Answer : %lld\n", answer);
}
