#ifndef __PRIME_H_
#define __PRIME_H_

#include <vector>
#include <map>
#include <set>

namespace HeeM
{
class Primes
{
public:
	Primes() {}
	~Primes() {}
	void Init(int limit);	// limit is power of ten
	bool IsPrime(long long n);
	const std::vector<long long>& GetPrimes();
	long long operator[](int index);
	long long GetCommonDenominator(std::vector<long long> params);
	template<typename ...Args>
	long long GetCommonDenominator(Args&... args);

	bool IsCoprime(long long a, long long b);
	long long Rad(long long n);

	struct PrimeFactors
	{
		friend class Primes;
	private:
		PrimeFactors();
		
	public:
		bool HasCommonDivisor(const PrimeFactors& primeFactors) const;
		const std::set<long long> GetFactors() const;
		size_t GetPresence(long long factor);
		long long Rad() const;
		PrimeFactors operator*(long long n) const;
		
		long long rad;
		std::set<long long> factors;
		std::map<long long, size_t> presence;
	};

	PrimeFactors& GetPrimeFactors(long long n);

private:
	std::vector<long long> primeList;
	std::vector<bool> primeField;
	std::map<long long, PrimeFactors> primeFactors;
	long long mapLimit;
};

template<typename ...Args>
long long HeeM::Primes::GetCommonDenominator(Args&... args)
{
	std::vector<long long> params = { args... };
	return GetCommonDenominator(params);
}

}

#endif
