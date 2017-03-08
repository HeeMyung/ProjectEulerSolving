#include <stdio.h>
#include <complex>
#include "prime.h"

enum class IndexType
{
	Vertex,
	Edge,
};

inline long long GetGroupInitial(long long hexaGroup)
{
	return 3 * hexaGroup * (hexaGroup - 1) + 2;
}

inline long long GetGroupFinal(long long hexaGroup)
{
	return 3 * hexaGroup * (hexaGroup + 1) + 1;
}

IndexType GetIndexType(long long hexaGroup, long long groupIndex)
{
	long long groupInitial = GetGroupInitial(hexaGroup);
	if (groupIndex % hexaGroup == 0)
		return IndexType::Vertex;
	else
		return IndexType::Edge;
}

long long GetHexaTileNumber(long long hexaGroup, long long groupIndex)
{
	if (hexaGroup == 0)
		return 1;
	
	long long groupInitial = GetGroupInitial(hexaGroup);
	return groupInitial + groupIndex;
}

HeeM::Primes g_primes;

bool TestHexaDiff(long long hexaGroup, long long groupIndex)
{
	long long groupInitial = GetGroupInitial(hexaGroup);
	long long groupFinal = GetGroupFinal(hexaGroup);

	long long x = GetHexaTileNumber(hexaGroup, groupIndex);

	auto it = GetIndexType(hexaGroup, groupIndex);

	std::vector<long long> neighbors;
	auto PushNeighbor = [&neighbors](long long n)
	{
		neighbors.push_back(n);
	};

	auto prevIndex = GetHexaTileNumber(hexaGroup - 1, groupIndex * (hexaGroup - 1) / hexaGroup);
	auto nextIndex = GetHexaTileNumber(hexaGroup + 1, groupIndex * (hexaGroup + 1) / hexaGroup);

	switch (it)
	{
	case IndexType::Vertex:
		PushNeighbor(prevIndex);

		if (x == groupInitial)
		{
			PushNeighbor(groupFinal);
			PushNeighbor(nextIndex);
			PushNeighbor(GetGroupFinal(hexaGroup + 1));
		}
		else
		{
			PushNeighbor(nextIndex - 1);
		}
		PushNeighbor(nextIndex + 1);
		break;
	case IndexType::Edge:
		if (x != groupFinal)
			return false;
		PushNeighbor(groupInitial);
		PushNeighbor(GetGroupInitial(hexaGroup - 1));
		PushNeighbor(prevIndex);
		PushNeighbor(nextIndex);
		PushNeighbor(nextIndex + 1);
		break;
	default:
		return false;	// 에러임 여기 안옴
	}

	long long primeCount = 0;
	for (auto n : neighbors)
	{
		if (g_primes.IsPrime(std::abs(n - x)))
			++primeCount;
	}
	if (primeCount == 3)
	{
		printf("Hit: %lld\n", x);
		return true;
	}
	return false;
}

const long long findNth = 2000;

long long FindAnswer()
{
	long long matchCount = 1; // 1은 자동추가
	long long hexaGroup = 1;
	long long hitNumber = 0;
	while (true)
	{
		long long groupInitial = GetGroupInitial(hexaGroup);
		long long groupFinal = GetGroupFinal(hexaGroup);
		for (long long i = 0; i < 6; ++i)
		{
			if (TestHexaDiff(hexaGroup, i * hexaGroup))
				matchCount++;
			if (matchCount == findNth)
				return GetHexaTileNumber(hexaGroup, i * hexaGroup);
		}
		if (hexaGroup > 1)
		{
			if (TestHexaDiff(hexaGroup, hexaGroup * 6 - 1))
				matchCount++;
			if (matchCount == findNth)
				return GetHexaTileNumber(hexaGroup, hexaGroup * 6 - 1);
		}
		++hexaGroup;
	}
	return 0;
}


int main()
{
	g_primes.Init(8);
	printf("%lldth Matched Number is %lld\n", findNth, FindAnswer());
	return 0;
}
