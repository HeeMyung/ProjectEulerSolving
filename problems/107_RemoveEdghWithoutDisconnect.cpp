#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>
#include <map>
#include <set>

struct LINK
{
	int v1, v2;
	int w;
	LINK(int _v1, int _v2, int _w)
	{
		v1 = _v1;
		v2 = _v2;
		w = _w;
	}
};

struct LINKCmp
{
	bool operator() (const LINK& a, const LINK& b)
	{
		if( a.w > b.w )
			return true;
		else if( a.w < b.w )
			return false;
		
		if( a.v1 > b.v1 )
			return true;
		else if( a.v1 < b.v1 )
			return false;

		if( a.v2 > b.v2 )
			return true;
		else if( a.v2 < b.v2 )
			return false;

		return false;
	}
};

int main()
{
	FILE* inp = fopen("network.txt","r");

	std::priority_queue<LINK, std::vector<LINK>, LINKCmp> links; 
	std::map<int, std::vector<int>*> groups;
	int firstSum = 0, totalLinks = 0;
	for(int i = 0; i < 40 ; i++)
	{
		char buffer[2000];
		fgets(buffer, sizeof(buffer), inp);
		char* tok = strtok(buffer, ",\n");
		for(int j = 0; j < i ; j++)
			
		{
			int weight = 0;
			if( strcmp(tok,"-") != 0 )
			{
				weight = atoi(tok);
				if( weight <= 0 )
				{
					printf("weight Str : [%s]\n", tok);
				}
				firstSum += weight;
				LINK l(i, j, weight);
				links.push(l);
				totalLinks++;
			}
			tok = strtok(NULL, ",\n");
		}
	}
	int removeSum = 0;
	int idCount = 0;
	int weightSum = 0;
	int removedLinkCount = 0;
	std::vector<LINK> aliveLinks;
	std::set<std::vector<int>*> vectorSet;
	while(!links.empty())
	{
		LINK t = links.top();
		printf("v1:%c, v2:%c, w:%d\n", 'a' + t.v1, 'a' + t.v2, t.w);
		std::map<int, std::vector<int>*>::iterator iter;
		iter = groups.find(t.v1);
		std::vector<int>* v1vector;
		if( iter != groups.end() )
		{
			v1vector = iter->second;
		}
		else
		{
			v1vector = new std::vector<int>();
			v1vector->push_back(t.v1);
			groups[t.v1] = v1vector;
			vectorSet.insert(v1vector);
		}
		iter = groups.find(t.v2);
		if( iter != groups.end() )
		{
			if( iter->second != v1vector )
			{
				vectorSet.erase(iter->second);
				std::vector<int> temp = *iter->second;
				{
					for(int k = 0; k < temp.size(); ++k)
					{
						groups[temp[k]] = v1vector;
					}
				}
				v1vector->insert(v1vector->end(), temp.begin(), temp.end());
				weightSum += t.w;
				aliveLinks.push_back(t);
			}
			else
			{
				removeSum += t.w;
				removedLinkCount++;
			}
		}
		else
		{
			v1vector->push_back(t.v2);
			groups[t.v2] = v1vector;
			weightSum += t.w;
			aliveLinks.push_back(t);
		}
		std::set<std::vector<int>*>::iterator iters = vectorSet.begin();
		printf("current groups\n");
		for(; iters != vectorSet.end(); ++iters)
		{
			std::vector<int>* pVec = *iters;
			for(int i = 0; i < pVec->size(); ++i)
			{
				printf("%c ", (*pVec)[i] + 'a');
			}
			printf("\n");
		}
		links.pop();
	}
	for(int i = 0; i < 40; ++i)
	{
		printf("i : %d, vector address : %x\n",i, groups[i]);
	}
	printf("firstSum2X : %d\n", firstSum);
	printf("Total Links : %d\n", totalLinks);
	printf("Removed Link Count : %d\n", removedLinkCount);
	firstSum/= 2;
	printf("First Sum : %d\n", firstSum);
	printf("Weight Sum : %d\n", weightSum);
	printf("saving : %d\n", firstSum - weightSum);
	printf("removeSum : %d\n", removeSum);
	for(size_t i = 0; i < aliveLinks.size(); ++i)
	{
		LINK& t = aliveLinks[i];
		printf("v1:%c, v2:%c, w:%d\n", 'a' + t.v1, 'a' + t.v2, t.w);
	}
}
