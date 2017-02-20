#include <stdio.h>
#include <vector>
#include <set>
#include <map>
#include "iterator.h"

struct Cuboid
{
	struct Point
	{
		Point(int x, int y, int z)
		{
			pos.push_back(x);
			pos.push_back(y);
			pos.push_back(z);
		}
		bool operator <(const Point& rhs) const
		{
			return pos < rhs.pos;
		}
		std::vector<int> pos;
		bool operator ==(const Point& rhs) const
		{
			return pos == rhs.pos;
		}
		Point operator+(int add[3]) const
		{
			return Point(pos[0]+add[0], pos[1]+add[1], pos[2]+add[2]);
		}
	};

	Cuboid(int x, int y, int z)
	{
		for(int i = 0; i < x; ++i)
		{
			for(int j = 0; j < y; ++j)
			{
				for(int k = 0; k < z; ++k)
				{
					curLayer.insert(Point(i, j, k));
				}
			}
		}
	}
	void Expand()
	{
		std::set<Point> nextLayer;
		for(auto iter : curLayer)
		{
			int addVec[][3] = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};
			for(auto v : addVec)
			{
				Point np = iter + v;
				if( curLayer.find(np) != curLayer.end() || prevLayer.find(np) != prevLayer.end() )
					continue;
				nextLayer.insert(np);
			}
		}
		prevLayer = curLayer;
		curLayer = nextLayer;
	}
	int Count() const
	{
		return (int)curLayer.size();
	}
	std::set<Point> curLayer, prevLayer;
};

struct LogicalCuboid
{
	LogicalCuboid(int x, int y, int z, int _n = 1) : a0(2*(x*y + y*z + x*z)), d0(4*(x + y + z)), n(_n)
	{
		size[0] = x;
		size[1] = y;
		size[2] = z;
	}
	static std::vector<LogicalCuboid> Next(const LogicalCuboid& c)
	{
		std::vector<LogicalCuboid> ret;
		ret.push_back(LogicalCuboid(c.size[0], c.size[1], c.size[2], c.n+1));
		if( c.n != 1 )
			return ret;
		ret.push_back(LogicalCuboid(c.size[0], c.size[1], c.size[2]+1, 1));
		if( c.size[1] < c.size[2] )
			ret.push_back(LogicalCuboid(c.size[0], c.size[1]+1, c.size[2], 1));
		if( c.size[0] < c.size[1] )
			ret.push_back(LogicalCuboid(c.size[0]+1, c.size[1], c.size[2], 1));
		return ret;
	}
	int GetC() const
	{
		return (n - 1) * (4 * n - 8 + d0) + a0;
	}

	bool operator<(const LogicalCuboid rhs) const
	{
		int myC = GetC(), rC = rhs.GetC();
		return myC > rC ? true :
			myC < rC ? false :
			size[0] < rhs.size[0] ? true :
			size[0] > rhs.size[0] ? false :
			size[1] < rhs.size[1] ? true :
			size[1] > rhs.size[1] ? false :
			size[2] < rhs.size[2] ? true :
			size[2] > rhs.size[2] ? false :
			n > rhs.n;
	}

	int GetAddCount()
	{
		return 1;
		/*if( size[0] == size[1] == size[2] )
			return 1;
		else if( size[0] != size[1] && size[1] != size[2] && size[0] != size[2] )
			return 6;
		else
			return 3;*/
	}

	int size[3];
	int a0, d0, n;
};

int main()
{
	std::map<int, int> cCount;
	PriorityIterater<LogicalCuboid, &LogicalCuboid::Next> iter(LogicalCuboid(1, 1, 1, 1));
	int checkValue = 0;
	while(true)
	{
		LogicalCuboid n(0,0,0,0);
		if(!iter.GetNext(n))
			break;
		int cc = n.GetC();
		//printf("%d*%d*%d : %dth => %d\n", n.size[0], n.size[1], n.size[2], n.n, cc);
		//getchar();
		cCount[cc] += n.GetAddCount();
		if( checkValue != cc )
		{
			if( cCount[checkValue] == 1000 )
			{
				printf("C(%d) == %d\n", checkValue, cCount[checkValue]);
				break;
			}
			//printf("CURCC:%d, Count:%d\n", checkValue, cCount[checkValue]); 
			checkValue = cc;
		}
	}
}
