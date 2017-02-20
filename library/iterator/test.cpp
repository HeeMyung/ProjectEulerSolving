#include "stdio.h"
#include "iterater.h"

struct A
{
	A()
	{}
	A(int _a, int _b, int _index = 0) : a(_a), b(_b), index(_index)
	{}

	bool operator<(const A& rhs) const
	{
		return a*b > rhs.a * rhs.b ? true :
			a*b < rhs.a * rhs.b ? false :
			a > rhs.a ? true :
			a < rhs.a ? false :
			b > rhs.b;
	}

	static std::vector<A> Gen(const A& t)
	{
		std::vector<A> ret;
		if(t.index == 0)
		{
			ret.push_back(A(t.a+1, t.b, 0));
			ret.push_back(A(t.a, t.b+1, 1));
		}
		else
			ret.push_back(A(t.a, t.b+1, 1));
		return ret;
			
	}
	int a, b;
	int index;
};

int main()
{
	A start(1, 1);
	PriorityIterater<A, &A::Gen> iter(start);
	for(int c = 0; c < 20; ++c)
	{
		A n;
		if(!iter.GetNext(n))
			break;
		printf("%d, %d => %d\n", n.a, n.b, n.a * n.b);
	}
}
