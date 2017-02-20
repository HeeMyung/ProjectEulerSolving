#ifndef __PRIME_H_
#define __PRIME_H_

#include <vector>
#include <map>

namespace HeeM
{
	class Primes
	{
		public:
		Primes(){}
		~Primes(){}
		void Init(int limit);	// limit is power of ten
		bool IsPrime(long long n);
		const std::vector<long long>& GetPrimes();
		long long operator[](int index);

		bool IsCoprime(long long a, long long b);
		long long Rad(long long n);

		private:
		std::vector<long long> primeList;
		std::vector<bool> primeField;
		long long mapLimit;
	};
}

#endif
