#ifndef __BIGINT_H_
#define __BIGING_H_

#include <vector>
#include <string>

class BigInt
{
public:
	BigInt();
	~BigInt();
	BigInt(const int&i);

	BigInt operator=(const int& i);
	const std::vector<char>& getInternal() const;
	std::string toString() const;
	operator const char*();
	int length() const;
	BigInt operator+(const BigInt& bi) const;
	BigInt operator+(const int& i) const;
	BigInt puresubt(const BigInt& bi) const;
	BigInt operator-(const BigInt& bi) const;
	BigInt operator*(const BigInt& bi) const;
	BigInt operator*(const int& i) const;
	BigInt operator/(const BigInt& bi) const; // IF NULL, Don't Insert the Rest
	void operator++(int);
	BigInt operator%(const BigInt& bi) const;
	int isBigger(const BigInt& a, const BigInt& b) const;
	bool operator>(const BigInt& bi) const;
	bool operator<(const BigInt& bi) const;
	bool operator==(const BigInt& bi) const;
	bool operator>=(const BigInt& bi) const;
	bool operator<=(const BigInt& bi) const;

	BigInt cut(int start, int end);
	BigInt rcut(int start, int end);
	
	void fillWith(int size, char value);
protected:
	template<class T>
	static BigInt resolve(T*, int size);
	std::vector<char> m_internal;
	std::string m_internal_string;
};

template<class T>
BigInt BigInt::resolve(T* arr, int size)
{
	while(arr[size-1] == 0 && size > 0) --size;
	if( size == 0 )
	{
		return BigInt(0);
	}

	BigInt ret;
	ret.m_internal.resize(size);
	int j; 
	for(j = 0; j < size ; ++j)
	{
		ret.m_internal[j] = (char)arr[j];
	}
	return ret;
}

#endif
