#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>

long long primePreset[10] = {2, 3, 5, 7, 11, 13, 17, 23, 29, 31};
std::map< std::set<int>, std::vector<std::set<int> > > subsetmap;
std::map<std::set<int>, int> solutionCountMap;

void setPrinter(const std::set<int>& set)
{
	for(std::set<int>::iterator setIter = set.begin(); setIter != set.end(); ++setIter)
	{
		printf("(%lld)", primePreset[*setIter]);
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
	std::set<int> elements;
	long long num;
	NUMBER()
	{
		num = 1;
		elements.clear();
	}
	NUMBER(const NUMBER& n)
	{
		num = n.num;
		elements = n.elements;
	}
	void print() const
	{
		printf("num:%lld{", num);
		for(std::set<int>::iterator iter = elements.begin(); iter != elements.end(); ++iter)
		{
			printf("(%lld)", primePreset[*iter] );
		}
		printf("}\n");
	}
	/*NUMBER operator*(const NUMBER& n) const
	{
		NUMBER ret;
		
		for(size_t i = 0; i < 10; ++i)
		{
			ret.elements[i] = elements[i] + n.elements[i];
		}
		ret.num = num * n.num;
		return ret;
	}
	*/
	NUMBER operator*(const int& nIndex) const
	{
		//printf("기존:");
		//print();
		//printf("입력:%d\n", nIndex);
		NUMBER ret;
		if( nIndex >= 10 )
		{
			printf("Error: Not Indexed Number %d\n", nIndex);
			return ret;
		}
		ret.num = num * primePreset[nIndex];
		ret.elements = elements;
		ret.elements.insert(nIndex);
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
		/*
		int ret = 0;
		std::vector< std::set<int> > subsets = getSubsets(elements);
		printf("elements:{");
		setPrinter(elements);
		printf("}\n");
		//subsetPrinter(subsets);
		for(std::vector< std::set<int> >::iterator iter = subsets.begin(); iter != subsets.end(); ++iter)
		{
			printf("subset{");
			setPrinter(*iter);
			printf("} %d\n", solutionCountMap[*iter]);
			ret += solutionCountMap[*iter];
		}
		return ret + 1;
		*/

		int count = 0;
		for(long long y = num+1; y <= 2*num; ++y)
		{
			if( num * y % ( y - num ) == 0 )
			{
				//printf("1/%lld + 1/%lld = 1/%lld\n", n*y/(y-n), y, n);
				count++;
			}
		}
		return count;
	}
};

bool correctCheck(long long n, int checkcount)
{
	int count = 0;
	for(long long y = n+1; y <= 2*n; ++y)
	{
		if( n * y % ( y - n ) == 0 )
		{
			printf("1/%lld + 1/%lld = 1/%lld\n", n*y/(y-n), y, n);
			count++;
		}
	}
	return count == checkcount;
}

int main()
{
	std::set<long long> checked;
	std::priority_queue<NUMBER> numbers;
	NUMBER a;
	numbers.push(a);
	

	/*
	std::set<int> testset;
	testset.insert(0);
	testset.insert(1);
	testset.insert(3);

	std::vector< std::set<int> > subsets = getSubsets(testset);
	*/

	
	long long founded;
	while(!numbers.empty())
	{
		NUMBER n = numbers.top();
		solutionCountMap[n.elements]++;
		int solutionCount = n.getSolutionCount();
		printf("현재 숫자 : %lld, DivisorCount:%d, 숫자 구성 {", n.num, solutionCount);
		for(int i = 0; i < 10; ++i)
		{
			if( i > 1 && n.elements.find(i-1) == n.elements.end() )
				break;
			NUMBER newn = n * i;
			if( checked.find(newn.num) == checked.end() )
			{
				checked.insert(newn.num);
				numbers.push(newn);
			}
		}
		printf("}\n");
		/*if( !correctCheck(n.num, solutionCount) )
		{
			printf("맞지 않다\n");
			//return 0;
		}*/
		if( solutionCount  >= 1000 )
		{
			printf("찾았다! %lld\n", n.num);
			founded = n.num;
			break;
		}
		checked.insert(n.num);
		//getchar();
		numbers.pop();
	}
}
