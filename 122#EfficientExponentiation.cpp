#include <stdio.h>
#include <queue>
#include <map>
#include <set>

typedef std::set<int> container;

struct cmp_set
{
	bool operator()(const std::set<int>& a, const std::set<int>& b) const
	{
		return *a.crbegin() > *b.crbegin();
	}
};
std::priority_queue<container, std::vector<container>, cmp_set> g_watchQue;
std::map<int, int> leastWay;


void print_set(const container& t)
{
	printf("{ ");
	for(auto iter = t.cbegin(); iter != t.cend(); ++iter)
	{
		if( iter != t.begin() )
		{
			printf(", ");
		}
		printf("%d", *iter);
	}
	printf(" }\n");
}

int main()
{
	container start;
	start.insert(1);
	printf("HHH\n");
	print_set(start);
	printf("HHH2\n");
	g_watchQue.push(start);

	while(!g_watchQue.empty())
	{
		container t = g_watchQue.top();
		g_watchQue.pop();
		
		int last = *t.rbegin();
		print_set(t);
		if( leastWay[last] != 0 && t.size() > leastWay[last] )
			continue;
		else if( leastWay[last] == 0 || t.size() < leastWay[last] )
			leastWay[last] = (int)t.size();
		
		if( last >= 200 )
			continue;

		for(auto iter = t.cbegin(); iter != t.cend(); ++iter)
		{
			container cp = t;
			cp.insert(*iter + last);
			g_watchQue.push(cp);
		}
	}
	int answer = 0;
	for(int i = 1; i <= 200; ++i)
	{
		answer += leastWay[i] - 1;
	}
	printf("Answer: %d\n", answer);
}
