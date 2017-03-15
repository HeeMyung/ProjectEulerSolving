#include <chrono>
#include "prime.h"

HeeM::Primes g_primes;

int A(int n)
{
	if (n == 0 || n == 1)
		return 1;

	int count = 1;
	int base = 1;
	while (true)
	{
		auto m = base % n;
		if (m == 0)
			break;
		base = m * 10 + 1;
		count++;
	}

	int ret = count;
	return ret;
}

int main()
{
	g_primes.Init(6);

	int test = 3;
	auto start = std::chrono::system_clock::now();
	int target = 5;
	int hitCount = 0;
	long long sum = 0;
	while (hitCount < 25)
	{
		auto t = test;
		if (test % 10 == 3)
			test += 4;
		else
			test += 2;
		if (g_primes.IsPrime(t))
			continue;
		int a = A(t);
		if ((t - 1) % a == 0)
		{
			printf("Hit: %d\n", t);
			hitCount++;
			sum += t;
		}
	}
	printf("Answer: %d, time: %lld(ms)", sum, std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count());
}