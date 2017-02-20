#include "bigint.h"
#include <stdio.h>
#include <stdlib.h>
#include <set>

bool checkback(BigInt& a)
{
	if( a.length() < 9 )
		return false;
	const std::vector<char>& internal = a.getInternal();
	std::set<char> backset;
	backset.clear();
	int size = internal.size();
	//printf("%s\n", (const char*)a);
	for(int i = 0; i < 9; ++i)
	{
		if( internal[i] == 0/* || internal[size-i-1] == 0 */)
			return false;
		if(/* frontset.count(internal[size-i-1]) > 0 || */backset.find(internal[i]) != backset.end() )
		{
			//printf("\n");
			return false;
		}
		backset.insert(internal[i]);
		//intf("%d ", internal[i]);
	}
	//printf("\n");
	return true;
}
bool checkfront(BigInt& a)
{
	if( a.length() < 9 )
		return false;
	const std::vector<char>& internal = a.getInternal();
	std::set<char> frontset;
	frontset.clear();
	int size = internal.size();
	//printf("%s\n", (const char*)a);
	for(int i = 0; i < 9; ++i)
	{
		if(/* internal[i] == 0 || */internal[size-i-1] == 0 )
			return false;
		if( frontset.count(internal[size-i-1]) > 0/* || backset.find(internal[i]) != backset.end() */)
		{
			//printf("\n");
			return false;
		}
		frontset.insert(internal[size-i-1]);
		//intf("%d ", internal[i]);
	}
	//printf("\n");
	return true;
}

int main()
{
	BigInt prev[2], cur[2], next[2];
	int k = 2;

	prev[0] = 1;
	prev[1] = 1;
	cur[0] = 1;
	cur[1] = 1;
	
	while(!checkfront(cur[0]) || !checkback(cur[1]))
	{
		//printf("%d\n", k);
		next[0] = prev[0] + cur[0];
		next[1] = prev[1] + cur[1];
		prev[0] = cur[0];
		prev[1] = cur[1];
		cur[0] = next[0];
		cur[1] = next[1];
		if( cur[1].length() > 9 )
		{
			cur[1] = cur[1].rcut(0,8);
			prev[1] = prev[1].rcut(0,8);
		}

		if( cur[0].length() > 20 )
		{
			int diff = cur[0].length() - prev[0].length();
			cur[0] = cur[0].cut(0,19);
			prev[0] = prev[0].cut(0,19-diff);
		}

		++k;
	} 
	printf("%d %s\n", k, (const char*) cur[0]);

}
