#include <chrono>

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
	int test = 1000001;
	auto start = std::chrono::system_clock::now();
	const int target = 1000000;
	while (true)
	{
		int a = A(test);
		printf("A(%d): %d\n", test, a);
		if (a > target)
			break;
		if (test % 10 == 3)
			test += 4;
		else
			test += 2;
	}
	printf("Answer: %d, time: %lld(ms)", test, std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count());
}