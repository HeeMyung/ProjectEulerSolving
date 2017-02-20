#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>

#define MAX_PRIME 24

double primePreset[MAX_PRIME] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89};
std::map< std::set<int>, std::vector<std::set<int> > > subsetmap;
//std::map<NUMBER, int> solutionCountMap;

void setPrinter(const std::set<int>& set)
{
	for(std::set<int>::iterator setIter = set.begin(); setIter != set.end(); ++setIter)
	{
		printf("(%.0f)", primePreset[*setIter]);
	}
}

void subsetPrinter(std::vector< std::set<int> >& subsets)
{
	for(std::vector< std::set<int> >::iterator iter = subsets.begin(); iter != subsets.end(); ++iter)
	{
		const std::set<int>& elem = *iter;
		printf("subset:{");
		setPrinter(elem);
		printf("}\n");
	}
}

const std::vector< std::set<int> >& getSubsets(std::set<int> aset)
{
	std::map< std::set<int>, std::vector<std::set<int> > >::iterator iter = subsetmap.find(aset);
	if( iter != subsetmap.end() )
	{
		return subsetmap[aset];
	}
	if( aset.size() == 0 )
	{
		subsetmap[aset] = std::vector< std::set<int> >();
		return subsetmap[aset];
	}
	std::vector< std::set<int> > ret;
	if( aset.size() == 1 )
	{
		std::vector< std::set<int> > add;
		add.push_back(aset);
		subsetmap[aset] = add;
		return subsetmap[aset];
	}
	std::set<int> subset,leaf;
	std::set<int>::reverse_iterator iter2 = aset.rbegin();
	int endElem = *iter2++;
	leaf.insert(endElem);
	for(; iter2 != aset.rend(); iter2++)
	{
		subset.insert(*iter2);
	}
	const std::vector< std::set<int> >& subsets = getSubsets(subset);
	std::vector< std::set<int> > addsubsets;
	addsubsets = subsets;
	addsubsets.push_back(leaf);
	for(int i = 0; i < subsets.size(); ++i)
	{
		std::set<int> copy = subsets[i];
		copy.insert(endElem);
		addsubsets.push_back(copy);
	}
	subsetmap[aset] = addsubsets;
	return subsetmap[aset];
}

struct NUMBER
{
public:
	int elements[MAX_PRIME];
	double num;
	NUMBER()
	{
		num = 1;
		memset(elements, 0, sizeof(elements));
	}
	NUMBER(const NUMBER& n)
	{
		num = n.num;
		memcpy(elements, n.elements, sizeof(elements));
	}
	void print() const
	{
		printf("num:%.0f{", num);
		for(int i = 0; i < MAX_PRIME; ++i)
		{
			if( elements[i] > 0 )
				printf("(%.0f,%d)", primePreset[i], elements[i] );
		}
		printf("}\n");
	}
	NUMBER operator*(const int& nIndex) const
	{
		//printf("기존:");
		//print();
		//printf("입력:%d\n", nIndex);
		NUMBER ret;
		if( nIndex >= MAX_PRIME )
		{
			printf("Error: Not Indexed Number %d\n", nIndex);
			return ret;
		}
		ret.num = num * primePreset[nIndex];
		memcpy(ret.elements, elements, sizeof(elements));
		ret.elements[nIndex]++;
		//printf("출력:");
		//ret.print();
		return ret;
	}
	
	bool operator <(const NUMBER& n) const
	{
		return num > n.num;
	}
	int getSolutionCount()
	{
		int solutionCount = 1;
		for(int i = 0; i < MAX_PRIME; ++i)
		{
			solutionCount *= (elements[i]*2) + 1;
		}
		return solutionCount/2 + 1;
	}
};

int main()
{
	std::set<long long> checked;
	std::priority_queue<NUMBER> numbers;
	NUMBER a;
	numbers.push(a);

	int currentMax = 0;	
	long long founded;
	int nsteps = 0;
	while(!numbers.empty())
	{
		NUMBER n = numbers.top();
		int solutionCount = n.getSolutionCount();
		if( solutionCount > currentMax )
		{
			printf("기록 갱신 : %.0f, solutionCount:%d\n", n.num, solutionCount);
			n.print();
			currentMax = solutionCount;
		}
		for(int i = 0; i < MAX_PRIME ; ++i)
		{
			if( i > 0 )
			{
				if( n.elements[i-1] == 0 )
					break;
				else if( n.elements[i] >= n.elements[i-1] )
					continue;
			}
			NUMBER addn = n * i;
			if( checked.find(addn.num) == checked.end() )
			{
				checked.insert(addn.num);
				numbers.push(addn);
			}
		}
		if( solutionCount  >= 4000000 )
		{
			printf("찾았다! %.0f\n", n.num);
			founded = n.num;
			break;
		}
		nsteps++;
		//getchar();
		numbers.pop();
	}
	printf("총 스탭 수 : %d\n", nsteps);
}
